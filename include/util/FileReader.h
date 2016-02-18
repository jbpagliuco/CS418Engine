#pragma once

#include <string>

#include <fstream>

namespace CS418
{
	class FileReader
	{
	public:
		virtual ~FileReader();

		// Initializes the file system.
		virtual void Initialize();
		
		// Opens a file.
		// - file: the file path to open.
		virtual void Open(const std::string &file);
		// Closes the opened file.
		virtual void Close();

		// Returns the file extension of the opened file.
		std::string GetFileExtension()const;

		// Reads the next char.
		virtual char ReadChar();
		// Reads the next line.
		virtual std::string ReadLine();
		// Reads until the end of the file.
		// std::string ReadUntilEnd();
		// std::string ReadUntilChar(char c);
		// std::string ReadUntilString(const std::string &s);

		// Reads the entire file and returns the result as a string.
		virtual std::string FileAsString();

		// Resets the reading position of the file back to the top.
		virtual void Reset();

		// Returns true if the reader has reached the end of the file, false otherwise.
		bool EndOfFile()const;

	protected:
		std::string m_filename;
		std::fstream m_fstream;
	};
}