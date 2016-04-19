// POSITION,TEXCOORD,NORMAL

#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoord;

out VS_OUT {
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
} vs_out;

uniform mat4 _WVP;
uniform mat4 _World;

void main()
{
	gl_Position = _WVP * vec4(position, 1.0f);
	
	vs_out.Position = vec3(_World * vec4(position, 1.0f));
	vs_out.Normal = transpose(inverse(mat3(_World))) * normal;
	vs_out.TexCoords = vec2(texCoord.x, 1.0f - texCoord.y);
}