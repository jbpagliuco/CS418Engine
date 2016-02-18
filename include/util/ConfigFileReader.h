#pragma once

#include "FileReader.h"

namespace CS418
{
	class ConfigFileReader : public FileReader
	{
	public:
		virtual ~ConfigFileReader();

		// Seeks until the next key-value line.
		// - key: (Out) A reference to a string that will contain the key.
		// - value: (Out) A reference to a string that will contain the key.
		virtual void ReadKeyAndValue(std::string &key, std::string &value);
	};
}