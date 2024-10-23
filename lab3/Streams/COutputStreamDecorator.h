#pragma once
#include "IStream.h"
#include <fstream>
#include <vector>
#include <random>
#include <numeric>
#include "Series.h"

class COutputStreamDecorator : public IOutputDataStream
{
	// класс бесполезен
	// выяснить что делает
protected:
	COutputStreamDecorator(std::unique_ptr<IOutputDataStream>&& outputStream)
		: m_stream(std::move(outputStream))
	{}

	std::unique_ptr<IOutputDataStream> m_stream;
};

class CEncryptedOutputStream : public COutputStreamDecorator
{
public:
	CEncryptedOutputStream(std::unique_ptr<IOutputDataStream>&& stream, int key)
		: COutputStreamDecorator(std::move(stream))
		, m_encryptedTable(256)
	{
		FillEncryptedTable(key);
	}

	void WriteByte(uint8_t data) override
	{
		m_stream->WriteByte(EncryptedByte(data));
	}

	void WriteBlock(const void* srcData, std::streamsize size) override
	{
		auto buffer = static_cast<const uint8_t*>(srcData);

		for (auto i = 0; i < size; ++i)
		{
			WriteByte(*buffer);
			++buffer;
		}
	}

	void Close() override
	{
		m_stream->Close();
	}

private:
	void FillEncryptedTable(int key)
	{
		std::iota(m_encryptedTable.begin(), m_encryptedTable.end(), 0);
		std::shuffle(m_encryptedTable.begin(), m_encryptedTable.end(), std::mt19937(key));
	}

	uint8_t EncryptedByte(const uint8_t byte) const
	{
		return m_encryptedTable[byte];
	}

	std::vector<uint8_t> m_encryptedTable;
};

class CCompressedOutputStream : public COutputStreamDecorator
{
public:
	CCompressedOutputStream(std::unique_ptr<IOutputDataStream>&& stream)
		: COutputStreamDecorator(std::move(stream))
	{
		m_series = { 0, 0 };
	}

	void WriteByte(uint8_t data)
	{
		if (m_series.size == 0)
		{
			m_series.byte = data;
			++m_series.size;
			return;
		}

		if (m_series.byte == data)
		{
			if (m_series.size < std::numeric_limits<uint8_t>::max())
			{
				++m_series.size;
			}
			else
			{
				m_stream->WriteByte(m_series.size);
				m_stream->WriteByte(m_series.byte);
				m_series.byte = data;
				m_series.size = 1;
			}
			return;
		}

		m_stream->WriteByte(m_series.size);
		m_stream->WriteByte(m_series.byte);

		m_series.byte = data;
		m_series.size = 1;
	}

	void WriteBlock(const void* srcData, std::streamsize size)
	{
		auto buffer = static_cast<const uint8_t*>(srcData);

		for (std::streamsize index = 0; index < size; ++index)
		{
			WriteByte(*buffer);
			++buffer;
		}
	}

	void Close() override
	{
		if (!m_isClosed)
		{
			m_isClosed = true;
			// добавить обработку пустого файла
			m_stream->WriteByte(m_series.size);
			m_stream->WriteByte(m_series.byte);

			m_stream->Close();
		}
	}

	~CCompressedOutputStream()
	{
		Close();
	}

private:
	bool m_isClosed = false;

	std::ofstream m_outputFile;

	Series m_series;
};