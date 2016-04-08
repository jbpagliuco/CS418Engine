#version 330 core

struct ParallelLight
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 direction;
	float intensity;
};

struct PointLight
{
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	vec3 position;
	float range;
	vec3 att;
	float intensity;
};

in vec3 vout_position;
in vec3 vout_normal;

out vec4 fout_color;

uniform vec3 _CameraPos;
uniform ParallelLight _ParallelLight;

uniform samplerCube Environment;
uniform vec4 Diffuse;
uniform vec4 Specular;

vec3 CalcParallelLight()
{
	vec3 color;
	vec3 lightVector = -_ParallelLight.direction;
	
	color += vec3(Diffuse * _ParallelLight.ambient);
	
	float diffuseFactor = dot(lightVector, vout_normal);
	if (diffuseFactor > 0.0f)
	{
		float specularPower = max(Specular.a, 1.0f);
		vec3 eyeVector = normalize(_CameraPos - vout_position);
		vec3 R = reflect(-lightVector, vout_normal);
		float specularFactor = pow(max(dot(R, eyeVector), 0.0f), specularPower);
		
		color += vec3(diffuseFactor * Diffuse * _ParallelLight.diffuse);
		color += vec3(specularFactor * Specular * _ParallelLight.specular);
	}
	
	return _ParallelLight.intensity * color;
}

/*
vec3 CalcPointLight()
{
	vec3 color = vec3(0.0f, 0.0f, 0.0f);
	vec3 lightVector = _PointLight.position - vout_position;
	
	float d = length(lightVector);
	if (d > _PointLight.range)
		return vec3(0.0f, 0.0f, 0.0f);
		
	lightVector /= d;
	color += vec3(Diffuse * _PointLight.ambient);

	float diffuseFactor = dot(lightVector, vout_normal);
	if (diffuseFactor > 0.0f)
	{
		float specularPower = max(Specular.a, 1.0f);
		vec3 eyeVector = normalize(_CameraPos - vout_position);
		vec3 R = reflect(-lightVector, vout_normal);
		float specularFactor = pow(max(dot(R, eyeVector), 0.0f), specularPower);
		
		color += vec3(diffuseFactor * Diffuse * _PointLight.diffuse);
		color += vec3(specularFactor * Specular * _PointLight.specular);
	}
	
	return _PointLight.intensity * (color / dot(_PointLight.att, vec3(1.0f, d, d*d)));
}
*/

void main()
{
	vec3 I = normalize(vout_position - _CameraPos);
	vec3 R = reflect(I, normalize(vout_normal));
	fout_color = texture(Environment, R);
	
	fout_color += vec4(CalcParallelLight(), 0.0f);
}






























