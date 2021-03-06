// POSITION,TEXCOORD

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoords;

out vec2 vout_texCoords;

void main()
{
	gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);
	vout_texCoords = vec2(texCoords.x, texCoords.y);
}