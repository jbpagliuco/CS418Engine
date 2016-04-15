#version 330 core

in vec2 vout_texCoords;

out vec4 fout_color;

//uniform sampler2D _ColorMap;
uniform sampler2D _DepthMap;

float LinearizeDepth(in vec2 uv)
{
    float zNear = 0.1;    // TODO: Replace by the zNear of your perspective projection
    float zFar  = 100.0; // TODO: Replace by the zFar  of your perspective projection
    float depth = texture(_DepthMap, uv).x;
    return (2.0 * zNear) / (zFar + zNear - depth * (zFar - zNear));
}

void main()
{
    float c = LinearizeDepth(vout_texCoords);
    fout_color = vec4(c, c, c, 1.0);
	fout_color = texture(_DepthMap, vout_texCoords);
}