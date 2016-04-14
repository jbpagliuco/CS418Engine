#version 330 core

in vec3 vout_texCoord;

out vec4 color;

uniform samplerCube Skybox;

void main()
{
	color = texture(Skybox, vout_texCoord);
}