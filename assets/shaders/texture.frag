#version 330 core

in vec3 in_color;
in vec2 in_texCoord;

out vec4 color;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
	color = mix(texture(texture1, in_texCoord), texture(texture2, in_texCoord), 0.2);
}