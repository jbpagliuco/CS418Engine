#version 330 core

struct Light
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 position;
	float range;
	vec3 direction;
	float intensity;
	vec3 att;
	int type;
	bool castsShadows;
};

struct SurfaceInfo
{
	vec3 pos;
    vec3 normal;
    vec4 diffuse;
    vec4 spec;
};

in VS_OUT {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
} fs_in;

out vec4 fout_color;

uniform Light _Light;
uniform vec3 _CameraPos;

uniform sampler2D DiffuseMap;
uniform sampler2D SpecularMap;
uniform vec2 Scale;

/*
float CalcShadowFactor(sampler2D shadowMap, vec4 fragPosLightSpace)
{
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	
	if (projCoords.x < -1.0f || projCoords.x > 1.0f ||
		projCoords.y < -1.0f || projCoords.y > 1.0f ||
		projCoords.z < 0.0f)
		return 0.0f; 
	
	projCoords = 0.5f * projCoords + 0.5f;
	
	float depth = projCoords.z;
	
	float s0 = texture(shadowMap, projCoords.xy).r;
	float s1 = texture(shadowMap, projCoords.xy + vec2(SMAP_DX, 0.0f)).r;
	float s2 = texture(shadowMap, projCoords.xy + vec2(0.0f, SMAP_DX)).r;
	float s3 = texture(shadowMap, projCoords.xy + vec2(SMAP_DX, SMAP_DX)).r;
	
	float result0 = float(depth <= (s0 + SMAP_EPSILON));
	float result1 = float(depth <= (s1 + SMAP_EPSILON));
	float result2 = float(depth <= (s2 + SMAP_EPSILON));
	float result3 = float(depth <= (s3 + SMAP_EPSILON));
	
	vec2 texelPos = SMAP_SIZE * projCoords.xy;
	vec2 t = fract(texelPos);
	
	float shadow = mix(mix(result0, result1, t.x),
					   mix(result2, result3, t.x), t.y);
	
	return shadow;
}
*/
	
vec3 CalcLightColor(Light light, SurfaceInfo v)
{
	vec3 color;
	vec3 lightVector;
	float d;
	
	if (light.type == 0)
	{
		lightVector = normalize(-light.direction);
	}
	else if (light.type == 1)
	{
		lightVector = light.position - v.pos;
		d = length(lightVector);
		if (d > light.range)
			return vec3(0.0f, 0.0f, 0.0f);
		lightVector /= d;
	}
	
	color += vec3(v.diffuse * light.ambient);
	
	float diffuseFactor = dot(lightVector, v.normal);
	if (diffuseFactor > 0.0f)
	{
		float specularPower = max(v.spec.a, 1.0f);
		vec3 eyeVector = normalize(_CameraPos - v.pos);
		vec3 R = reflect(-lightVector, v.normal);
		float specularFactor = pow(max(dot(R, eyeVector), 0.0f), specularPower);
		
		color += vec3(diffuseFactor * v.diffuse * light.diffuse);
		color += vec3(specularFactor * v.spec * light.specular);
	}
	
	if (light.type == 1)
		color = color / dot(light.att, vec3(1.0f, d, d*d));
	return light.intensity * color;
}

void main()
{
	// Get materials from texture maps.
	vec4 diffuse = texture(DiffuseMap, vec2(fs_in.TexCoords * Scale));
	vec4 spec = texture(SpecularMap, vec2(fs_in.TexCoords * Scale));
	
	// Map [0,1] --> [0,256]
	spec.a *= 256.0f;
	
	// Interpolating normal can make it not be of unit length so normalize it.
    vec3 normalW = normalize(fs_in.Normal);
    
	// Compute the lit color for this pixel.
    SurfaceInfo v;
	v.pos = fs_in.Position;
    v.normal = normalW;
    v.diffuse = diffuse;
    v.spec = spec;
	fout_color = vec4(CalcLightColor(_Light, v), diffuse.a);
}