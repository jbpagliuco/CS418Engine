// POSITION

#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 _LightSpaceMatrix;
uniform mat4 _World;

void main()
{
	gl_Position = _LightSpaceMatrix * _World * vec4(position, 1.0f);
}