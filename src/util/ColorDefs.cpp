#include "util\ColorDefs.h"

#include <sstream>

namespace CS418
{
	namespace Colors
	{
		VECTOR4F StringToColor(const std::string &color)
		{
			if (color.find(" ") == std::string::npos)
			{
				if (color == "DarkGrey")
					return DarkGrey;
				else if (color == "Grey")
					return Grey;
				else if (color == "LightGrey")
					return LightGrey;
				else if (color == "White")
					return White;
				else if (color == "Red")
					return Red;
				else if (color == "Maroon")
					return Maroon;
				else if (color == "Lime")
					return Lime;
				else if (color == "Blue")
					return Blue;
				else if (color == "Navy")
					return Navy;
				else if (color == "Purple")
					return Purple;
				else if (color == "Teal")
					return Teal;
				else if (color == "Olive")
					return Olive;
				else if (color == "Yellow")
					return Yellow;
				else if (color == "Aqua")
					return Aqua;
				else if (color == "Fuchsia")
					return Fuchsia;
				else if (color == "CornflowerBlue")
					return CornflowerBlue;
				else if (color == "BeachSand")
					return BeachSand;
				else if (color == "LightYellowGreen")
					return LightYellowGreen;
				else if (color == "DarkYellowGreen")
					return DarkYellowGreen;
				else if (color == "DarkBrown")
					return DarkBrown;
				else
					return Black;
			}
			else
			{
				std::istringstream ss(color);
				VECTOR4F v;
				ss >> v.x >> v.y >> v.z >> v.w;
				return v;
			}
		}
	}
}