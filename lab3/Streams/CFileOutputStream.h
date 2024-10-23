#pragma once
#include "IStream.h"
#include <fstream>

class CFileOutputStream : public IOutputDataStream
{
public:
	CFileOutputStream(const std::string& outputFileName)
	{
		m_outputFile = std::ofstream(outputFileName, std::ios::out | std::ios::binary);
		if (!m_outputFile.is_open())
		{
			throw std::ios_base::failure("The file could not be opened for writing");
		}
	}

	void WriteByte(uint8_t data)
	{
		if (!m_outputFile.is_open())
		{
			throw std::logic_error("The file could not be opened for writing");
		}

		m_outputFile.write(reinterpret_cast<char*>(&data), sizeof(data));
	}

	void WriteBlock(const void* srcData, std::streamsize size)
	{
		if (!m_outputFile.is_open())
		{
			throw std::logic_error("The file could not be opened for writing");
		}

		m_outputFile.write(static_cast<const char*>(srcData), size);
	}

	void Close()
	{
		if (m_outputFile.is_open())
		{
			m_outputFile.close();
		}
	}

	~CFileOutputStream()
	{
		Close();
	}
private:
	std::ofstream m_outputFile;
};