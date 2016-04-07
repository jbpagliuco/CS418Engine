// POSITION,NORMAL

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec3 vout_normal;
out vec3 vout_position;

uniform mat4 _WVP;
uniform mat4 _World;

void main()
{
	gl_Position = _WVP * vec4(position, 1.0f);
	vout_normal = mat3(transpose(inverse(_World))) * normal;
	vout_position = vec3(_World * vec4(position, 1.0f));
}