#pragma once
#include "IStream.h"
#include <string>
#include <fstream>

class CFileInputStream : public IInputDataStream
{
public:
	CFileInputStream(const std::string& inputFileName)
	{
		m_inputFile = std::ifstream(inputFileName, std::ios::in | std::ios::binary);

		if (!m_inputFile.is_open())
		{
			throw std::ios_base::failure("The file could not be opened for reading");
		}
	}

	bool IsEOF() const override
	{
		if (m_inputFile.bad())
		{
			throw std::ios_base::failure("Stream state error");
		}

		return m_inputFile.eof();
	}

	uint8_t ReadByte()
	{
		char byte;
		m_inputFile.read(&byte, sizeof(byte));

		if (m_inputFile.fail())
		{
			throw std::ios_base::failure("Reading byte error");
		}

		return static_cast<uint8_t>(byte);
	}

	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override
	{
		m_inputFile.read(static_cast<char*>(dstBuffer), size);

		if (m_inputFile.fail())
		{
			throw std::ios_base::failure("Reading error from file");
		}

		return m_inputFile.gcount();
	}

private:
	std::ifstream m_inputFile;
};