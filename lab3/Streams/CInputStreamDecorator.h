#pragma once
#include "IStream.h"
#include "Series.h"
#include <numeric>

class CInputStreamDecorator : public IInputDataStream
{
protected:
	CInputStreamDecorator(IInputDataStreamPtr&& inputStream)
		: m_stream(std::move(inputStream))
	{}

	std::unique_ptr<IInputDataStream> m_stream;
};

class CDecryptedInputStream : public CInputStreamDecorator
{
public:
	CDecryptedInputStream(IInputDataStreamPtr&& inputStream, int key)
		: CInputStreamDecorator(std::move(inputStream))
		, m_decryptedTable(256)
	{
		FillDecryptedTable(key);
	}

	uint8_t ReadByte() override
	{
		return DecryptedByte(m_stream->ReadByte());
	}

	std::streamsize ReadBlock(void* dstData, std::streamsize dataSize) override
	{
		auto size = m_stream->ReadBlock(dstData, dataSize);

		auto buffer = static_cast<uint8_t*>(dstData);

		for (auto index = 0; index < size; index++)
		{
			buffer[index] = DecryptedByte(buffer[index]);
		}

		return size;
	}

	bool IsEOF() const override
	{
		return m_stream->IsEOF();
	}

private:
	void FillDecryptedTable(int key)
	{
		std::vector<uint8_t> table(256);

		std::iota(table.begin(), table.end(), 0);
		std::shuffle(table.begin(), table.end(), std::mt19937(key));

		for (auto index = 0; index < 256; index++)
		{
			m_decryptedTable[table[index]] = static_cast<uint8_t>(index);
		}
	}

	uint8_t DecryptedByte(const uint8_t byte) const
	{
		return m_decryptedTable[byte];
	}

	std::vector<uint8_t> m_decryptedTable;
};


class CDecompressedInputStream : public CInputStreamDecorator
{
public:
	CDecompressedInputStream(std::unique_ptr<IInputDataStream>&& inputStream)
		: CInputStreamDecorator(std::move(inputStream))
	{}

	uint8_t ReadByte() override
	{
		if (m_series.size == 0)
		{
			m_series.size = static_cast<unsigned>(m_stream->ReadByte());
			m_series.byte = m_stream->ReadByte();
		}

		--m_series.size;
		return m_series.byte;
	}

	std::streamsize ReadBlock(void* dstData, std::streamsize dataSize) override
	{
		auto buffer = static_cast<uint8_t*>(dstData);

		for (std::streamsize index = 0; index < dataSize; index++)
		{
			try
			{
				*buffer = ReadByte();
			}
			catch (...)
			{
				//не покрыто тестами
				return index + 1;
			}

			buffer++;
		}

		return dataSize;
	}

	bool IsEOF() const override
	{
		return m_stream->IsEOF();
	}

private:
	Series m_series = { 0, 0 };
};