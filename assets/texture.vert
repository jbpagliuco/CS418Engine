// POSITION,TEXCOORD

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 2) in vec2 texCoord;

out vec3 out_color;
out vec2 out_texCoord;

uniform mat4 WVP;

void main()
{
	gl_Position = WVP * vec4(position, 1.0f);
	
	out_color = color;
	
	out_texCoord = vec2(texCoord.x, 1.0 - texCoord.y);
}