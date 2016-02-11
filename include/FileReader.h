#pragma once

#include <string>

#include <fstream>

namespace CS418
{
	class FileReader
	{
	public:
		~FileReader();

		// Initializes the file system.
		void Initialize();
		
		// Opens a file.
		// - file: the file path to open.
		void Open(const std::string &file);
		// Closes the opened file.
		void Close();

		// Returns the file extension of the opened file.
		std::string GetFileExtension();

		// Reads the next char.
		char ReadChar();
		// Reads the next line.
		std::string ReadLine();
		// Reads until the end of the file.
		// std::string ReadUntilEnd();
		// std::string ReadUntilChar(char c);
		// std::string ReadUntilString(const std::string &s);

		// Reads the entire file and returns the result as a string.
		std::string FileAsString();

		// Resets the reading position of the file back to the top.
		void Reset();

	private:
		std::string m_filename;
		std::fstream m_fstream;
	};
}