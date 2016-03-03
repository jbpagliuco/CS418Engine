// POSITION

#version 330 core

layout (location = 0) in vec3 position;

out vec3 vout_texCoord;

uniform mat4 WVP;

void main()
{
	gl_Position = (WVP * vec4(position, 1.0f)).xyww;
	
	vout_texCoord = position;
}