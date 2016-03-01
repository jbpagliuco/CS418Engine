#include "util/Convert.h"

#include "util/ColorDefs.h"

namespace CS418
{
	bool StringToBoolean(const std::string &line)
	{
		return (line == "True");
	}
	F32 StringToFloat(const std::string &line)
	{
		F32 value;

		if (line == "PI")
			value = PI;
		else if (line == "2PI")
			value = PI_MUL2;
		else if (line == "PIDIV2")
			value = PI_DIV2;
		else if (line == "PIDIV3")
			value = PI_DIV3;
		else if (line == "PIDIV4")
			value = PI_DIV4;
		else if (line == "PIDIV6")
			value = PI_DIV6;
		else if (line == "3PIDIV2")
			value = PI_3DIV2;
		else
			value = stof(line);

		return value;
	}
	

	VECTOR2F StringToVector2f(const std::string &line)
	{
		VECTOR2F v;
		std::stringstream ss(line);

		std::string x, y;
		ss >> x >> y;

		v.x = StringToFloat(x.substr(1));
		v.y = StringToFloat(y.substr(0, y.length() - 1));

		return v;
	}
	VECTOR3F StringToVector3f(const std::string &line)
	{
		VECTOR3F v;
		std::stringstream ss(line);

		std::string x, y, z;
		ss >> x >> y >> z;

		v.x = StringToFloat(x.substr(1));
		v.y = StringToFloat(y);
		v.z = StringToFloat(z.substr(0, z.length() - 1));

		return v;
	}
	VECTOR4F StringToVector4f(const std::string &line)
	{
		VECTOR4F v;
		std::stringstream ss(line);

		std::string x, y, z, w;
		ss >> x >> y >> z >> w;

		v.x = StringToFloat(x.substr(1));
		v.y = StringToFloat(y);
		v.z = StringToFloat(z);
		v.w = StringToFloat(w.substr(0, w.length() - 1));

		return v;
	}

	VECTOR4F StringToColor(const std::string &line)
	{
		return Colors::StringToColor(line);
	}


	Viewport StringToViewport(const std::string &line, GraphicsManager * pGfxManager)
	{
		Viewport v;
		std::stringstream ss(line);
		std::string topLeftX, topLeftY, width, height, minDepth, maxDepth;

		ss >> topLeftX >> topLeftY >> width >> height >> minDepth >> maxDepth;

		v.TopLeftX = StringToFloat(topLeftX.substr(1));
		v.TopLeftY = StringToFloat(topLeftY);
		v.Width = StringToFloat(width);
		v.Height = StringToFloat(height);
		v.MinDepth = StringToFloat(minDepth);
		v.MaxDepth = StringToFloat(maxDepth.substr(0, maxDepth.length() - 1));

		if (v.Width == -1)
			v.Width = (F32)pGfxManager->GetWindowDimensions().X;
		if (v.Height == -1)
			v.Height = (F32)pGfxManager->GetWindowDimensions().Y;

		return v;
	}

	std::vector<std::string> SplitString(std::string s, const std::string &delim)
	{
		std::vector<std::string> v;

		size_t pos;
		while ((pos = s.find(delim)) != std::string::npos)
		{
			std::string arg = s.substr(0, pos);
			v.push_back(arg);
			s.erase(0, pos + delim.length());
		}
		v.push_back(s);

		return v;
	}
}