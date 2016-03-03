#version 330 core

in vec3 vout_texCoord;

out vec4 color;

uniform samplerCube _Skybox;

void main()
{
	color = texture(_Skybox, vout_texCoord);
}