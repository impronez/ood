#pragma once
#include "IStream.h"
#include <vector>

class CMemoryOutputStream : public IOutputDataStream
{
public:
	CMemoryOutputStream(std::vector<uint8_t>& memory)
		: m_stream(memory)
	{}

	void WriteByte(uint8_t data) override
	{
		if (!m_isOpen)
		{
			throw std::logic_error("Stream is closed");
		}

		try
		{
			m_stream.push_back(data);
		}
		catch (...)
		{
			throw std::ios_base::failure("Error. Can not write to memory");
		}
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		if (!m_isOpen)
		{
			throw std::logic_error("Stream is closed");
		}

		auto buffer = static_cast<const uint8_t*>(srcData);

		for (std::streamsize index = 0; index < size; index++)
		{
			WriteByte(*buffer);
			buffer++;
		}
	}

	void Close() override
	{
		m_isOpen = false;
	}

private:
	bool m_isOpen = true;
	std::vector<uint8_t>& m_stream;
};