#pragma once
#include "IStream.h"
#include <vector>

class CMemoryInputStream : public IInputDataStream
{
public:
	CMemoryInputStream(std::vector<uint8_t>& memory)
		: m_stream(memory)
	{}

	bool IsEOF() const override
	{
		return m_pos == m_stream.size();
	}

	uint8_t ReadByte() override
	{
		if (IsEOF())
		{
			throw std::ios_base::failure("Error. Can not read");
		}

		auto value = m_stream[m_pos];
		++m_pos;

		return value;
	}

	std::streamsize ReadBlock(void* dstData, std::streamsize dataSize) override
	{
		if (static_cast<size_t>(dataSize) > m_stream.size() - m_pos)
		{
			dataSize = m_stream.size() - m_pos;
		}

		auto buffer = static_cast<uint8_t*>(dstData);

		for (std::streamsize index = 0; index < dataSize; index++)
		{
			*buffer = m_stream[m_pos];
			++m_pos;
			++buffer;
		}

		return dataSize;
	}

private:
	std::vector<uint8_t>& m_stream;

	size_t m_pos = 0;
};