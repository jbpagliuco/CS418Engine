#version 330 core

in vec3 vout_position;
in vec3 vout_normal;

out vec4 color;

uniform vec3 _CameraPos;
uniform samplerCube Environment;

void main()
{
	vec3 I = normalize(vout_position - _CameraPos);
	vec3 R = reflect(I, normalize(vout_normal));
	color = texture(Environment, R);
}