#version 330 core

in vec2 vout_texCoord;

out vec4 color;

uniform sampler2D DiffuseMap;

void main()
{
	color = texture(DiffuseMap, vout_texCoord);
}