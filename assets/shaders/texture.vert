// POSITION,TEXCOORD

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 texCoord;

out vec2 vout_texCoord;

uniform mat4 WVP;

void main()
{
	gl_Position = WVP * vec4(position, 1.0f);
	
	vout_texCoord = vec2(texCoord.x, 1.0f - texCoord.y);
}