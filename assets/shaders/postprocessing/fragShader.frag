#version 330 core

in vec2 vout_texCoords;

out vec4 fout_color;

uniform sampler2D _ColorMap;
uniform sampler2D _DepthMap;

float LinearizeDepth(in vec4 depth)
{
    float zNear = 0.1;
    float zFar  = 100.0;
    return (2.0 * zNear) / (zFar + zNear - depth.x * (zFar - zNear));
}

float EdgeDetection(float hStep, float vStep, vec2 middle)
{
	float TL = length(texture(_ColorMap, middle + vec2(-hStep, vStep)));
	float TM = length(texture(_ColorMap, middle + vec2(0.0f, vStep)));
	float TR = length(texture(_ColorMap, middle + vec2(hStep, vStep)));
	float LL = length(texture(_ColorMap, middle + vec2(-hStep, 0.0f)));
	float RR = length(texture(_ColorMap, middle + vec2(hStep, 0.0f)));
	float BL = length(texture(_ColorMap, middle + vec2(-hStep, -vStep)));
	float BM = length(texture(_ColorMap, middle + vec2(0.0f, -vStep)));
	float BR = length(texture(_ColorMap, middle + vec2(hStep, -vStep)));
	
	float Gx = -TL + TR - (2 * LL) + (2 * RR) - BL + BR;
	float Gy = -TL - (2 * TM) - TR + BL + (2 * BM) + BR;
	float G = 1.0f - sqrt((Gx * Gx) + (Gy * Gy));
	
	float factor = 0.3f;
	return round(G - factor);
}

void main()
{
	float hStep = 1.0f / 1920.0f;
	float vStep = 1.0f / 1080.0f;
	hStep = vStep = 1.0f / 512.0f;
	float edge = EdgeDetection(hStep, vStep, vout_texCoords);
	
	fout_color = texture(_ColorMap, vout_texCoords) * vec4(edge, edge, edge, 1.0f);
	fout_color = vec4(edge, edge, edge, 1.0f);
}