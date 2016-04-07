// POSITION,COLOR

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 color;

out vec4 vout_color;

uniform mat4 WVP;

void main()
{
	gl_Position = WVP * vec4(position, 1.0f);
	
	vout_color = color;
}