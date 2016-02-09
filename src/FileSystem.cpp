#include "FileSystem.h"

#include <assert.h>

namespace CS418
{
	FileSystem::~FileSystem()
	{
		m_fstream.close();
	}

	void FileSystem::Initialize()
	{

	}

	void FileSystem::Open(const std::string &file)
	{
		if (m_fstream.is_open())
			m_fstream.close();

		m_fstream.open(file.c_str(), std::ios::in | std::ios::out);
		assert(m_fstream.is_open());

		m_filename = file;
	}

	void FileSystem::Close()
	{
		m_fstream.close();
	}

	std::string FileSystem::GetFileExtension()
	{
		size_t index = m_filename.find_last_of('.');
		assert(index != std::string::npos); // Assert the file has a file extension at all.

		return m_filename.substr(index);
	}

	char FileSystem::ReadChar()
	{
		if (m_fstream.is_open())
		{
			return m_fstream.get();
		}
		
		return 0;
	}

	std::string FileSystem::ReadLine()
	{
		if (m_fstream.is_open())
		{
			std::string line;
			getline(m_fstream, line);

			return line;
		}

		return "";
	}

	std::string FileSystem::FileAsString()
	{
		Reset();

		if (m_fstream)
		{
			std::string contents;
			m_fstream.seekg(0, std::ios::end);
			contents.resize(m_fstream.tellg());
			m_fstream.seekg(0, std::ios::beg);
			m_fstream.read(&contents[0], contents.size());
			m_fstream.close();
			return(contents);
		}
		throw(errno);
	}

	void FileSystem::Reset()
	{
		if (m_fstream.is_open())
			m_fstream.seekg(std::ios::beg);
	}
}