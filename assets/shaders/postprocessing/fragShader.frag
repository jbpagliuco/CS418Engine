#version 330 core

in vec2 vout_texCoords;

out vec4 fout_color;

uniform sampler2D _ColorMap;
uniform sampler2D _DepthMap;

float LinearizeDepth(in vec2 uv)
{
    float zNear = 0.1;
    float zFar  = 100.0;
    float depth = texture(_DepthMap, uv).x;
    return (2.0 * zNear) / (zFar + zNear - depth * (zFar - zNear));
}

void main()
{
	fout_color = texture(_ColorMap, vout_texCoords);
}