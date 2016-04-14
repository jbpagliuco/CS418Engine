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
};

struct SurfaceInfo
{
	vec3 pos;
    vec3 normal;
    vec4 diffuse;
    vec4 spec;
};

in vec3 vout_position;
in vec3 vout_normal;
in vec2 vout_texCoord;

out vec4 fout_color;

uniform vec3 _CameraPos;
uniform int _NumLights;
uniform Light _Lights[4]; // Max of 4 lights

uniform sampler2D DiffuseMap;
uniform sampler2D SpecularMap;
uniform vec2 Scale;

vec3 CalcLightColor(Light light, SurfaceInfo v)
{
	vec3 color;
	vec3 lightVector;
	float d;
	
	if (light.type == 0)
	{
		lightVector = -light.direction;
		d = length(lightVector);
	}
	else if (light.type == 1)
	{
		lightVector = light.position - v.pos;
		d = length(lightVector);
		if (d > light.range)
			return vec3(0.0f, 0.0f, 0.0f);
	}
	
	lightVector /= d;
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

vec3 CalcLights(SurfaceInfo v)
{
	vec3 color = vec3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < _NumLights; i++)
		color += CalcLightColor(_Lights[i], v);
		
	return color;
}

void main()
{
	// Get materials from texture maps.
	vec4 diffuse = texture(DiffuseMap, vec2(vout_texCoord.x * Scale.x, vout_texCoord.y * Scale.y));
	vec4 spec = texture(SpecularMap, vec2(vout_texCoord.x * Scale.x, vout_texCoord.y * Scale.y));
	
	// Map [0,1] --> [0,256]
	spec.a *= 256.0f;
	
	// Interpolating normal can make it not be of unit length so normalize it.
    vec3 normalW = normalize(vout_normal);
    
	// Compute the lit color for this pixel.
    SurfaceInfo v;
	v.pos = vout_position;
    v.normal = normalW;
    v.diffuse = diffuse;
    v.spec = spec;
	fout_color = vec4(CalcLights(v), diffuse.a);
}