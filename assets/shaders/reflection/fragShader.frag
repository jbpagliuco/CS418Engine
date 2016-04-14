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

in vec3 vout_position;
in vec3 vout_normal;

out vec4 fout_color;

uniform vec3 _CameraPos;
uniform int _NumLights;
uniform Light _Lights[4]; // Max of 4 lights

uniform samplerCube Environment;
uniform vec4 Diffuse;
uniform vec4 Specular;

vec3 CalcLightColor(Light light)
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
		lightVector = light.position - vout_position;
		d = length(lightVector);
		if (d > light.range)
			return vec3(0.0f, 0.0f, 0.0f);
	}
	
	lightVector /= d;
	color += vec3(Diffuse * light.ambient);
	
	float diffuseFactor = dot(lightVector, vout_normal);
	if (diffuseFactor > 0.0f)
	{
		float specularPower = max(Specular.a, 1.0f);
		vec3 eyeVector = normalize(_CameraPos - vout_position);
		vec3 R = reflect(-lightVector, vout_normal);
		float specularFactor = pow(max(dot(R, eyeVector), 0.0f), specularPower);
		
		color += vec3(diffuseFactor * Diffuse * light.diffuse);
		color += vec3(specularFactor * Specular * light.specular);
	}
	
	if (light.type == 1)
		color = color / dot(light.att, vec3(1.0f, d, d*d));
	return light.intensity * color;
}

vec3 CalcLights()
{
	vec3 color = vec3(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < _NumLights; i++)
		color += CalcLightColor(_Lights[i]);
		
	return color;
}

void main()
{
	vec3 I = normalize(vout_position - _CameraPos);
	vec3 R = reflect(I, normalize(vout_normal));
	fout_color = texture(Environment, R);
	
	fout_color += vec4(CalcLights(), 1.0f);
}






























