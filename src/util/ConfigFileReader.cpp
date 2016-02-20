#include "util/ConfigFileReader.h"

namespace CS418
{
	ConfigFileReader::~ConfigFileReader()
	{

	}

	void ConfigFileReader::ReadKeyAndValue(std::string &key, std::string &value)
	{
		std::string line;
		while ((line = ReadLine()) == "" || line.find("##") == 0) { }

		key = line.substr(0, line.find(":"));
		value = line.substr(line.find(":") + 2);
	}
}