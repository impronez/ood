#define CATCH_CONFIG_MAIN
#include "../../../../catch/catch.hpp"

#include "../CFileInputStream.h"
#include "../CFileOutputStream.h"
#include "../CMemoryInputStream.h"
#include "../CMemoryOutputStream.h"
#include "../CInputStreamDecorator.h"
#include "../COutputStreamDecorator.h"
#include <sstream>

void CopyFile(IInputDataStreamPtr& input, IOutputDataStreamPtr& output)
{
	while (!input->IsEOF())
	{
		uint8_t byte;
		try
		{
			byte = input->ReadByte();
			output->WriteByte(byte);
		}
		catch (...)
		{
		}
	}
}

bool AreFilesEqual(const std::string& file1, const std::string& file2)
{
	std::ifstream f1(file1, std::ios::in | std::ios::binary);
	std::ifstream f2(file2, std::ios::in | std::ios::binary);

	if (!f1.is_open() || !f2.is_open())
	{
		std::cerr << "Error opening files" << std::endl;
		return false;
	}

	char byte1, byte2;

	while (true)
	{
		f1.read(&byte1, sizeof(byte1));
		f2.read(&byte2, sizeof(byte2));

		if (f1.eof() && f2.eof())
		{
			return true;
		}

		if (byte1 != byte2)
		{
			return false;
		}
	}

	return f1.eof() && f2.eof();
}

TEST_CASE("Encrypt and decrypt")
{
	std::string inputFileName = "input.exe";
	std::string outputEncryptedFileName = "output1.exe";
	std::string outputDecryptedFileName = "output2.exe";
	int key = 1000;

	WHEN("File encrypt")
	{
		IInputDataStreamPtr input = std::make_unique<CFileInputStream>(inputFileName);

		IOutputDataStreamPtr outputEncrypt = std::make_unique<CFileOutputStream>(outputEncryptedFileName);
		outputEncrypt = std::make_unique<CEncryptedOutputStream>(std::move(outputEncrypt), key);

		CopyFile(input, outputEncrypt);

		outputEncrypt->Close();

		REQUIRE(!AreFilesEqual(inputFileName, outputEncryptedFileName));
	}
	THEN("File decrypt")
	{
		IInputDataStreamPtr inputEncrypt = std::make_unique<CFileInputStream>(outputEncryptedFileName);
		inputEncrypt = std::make_unique<CDecryptedInputStream>(std::move(inputEncrypt), key);

		IOutputDataStreamPtr outputDecrypt = std::make_unique<CFileOutputStream>(outputDecryptedFileName);

		CopyFile(inputEncrypt, outputDecrypt);

		outputDecrypt->Close();

		REQUIRE(AreFilesEqual(inputFileName, outputDecryptedFileName));
	}
}

TEST_CASE("File compress and decompress")
{
	std::string inputFileName = "input5.exe";
	std::string outputCompressedFileName = "output5.exe";
	std::string outputDecompressedFileName = "output6.exe";

	WHEN("File compress")
	{
		IInputDataStreamPtr input = std::make_unique<CFileInputStream>(inputFileName);

		IOutputDataStreamPtr output = std::make_unique<CFileOutputStream>(outputCompressedFileName);
		output = std::make_unique<CCompressedOutputStream>(std::move(output));

		CopyFile(input, output);

		REQUIRE(!AreFilesEqual(inputFileName, outputCompressedFileName));
	}
	THEN("File decompress")
	{
		IInputDataStreamPtr inputCompressed = std::make_unique<CFileInputStream>(outputCompressedFileName);
		IOutputDataStreamPtr outputDecompressed = std::make_unique<CFileOutputStream>(outputDecompressedFileName);
		inputCompressed = std::make_unique<CDecompressedInputStream>(std::move(inputCompressed));

		CopyFile(inputCompressed, outputDecompressed);

		outputDecompressed->Close();

		REQUIRE(AreFilesEqual(inputFileName, outputDecompressedFileName));
	}
}

TEST_CASE("Copy .exe file")
{
	std::string inputFileName = "input.exe";
	std::string outputFileName = "output1.exe";

	IInputDataStreamPtr input = std::make_unique<CFileInputStream>(inputFileName);
	IOutputDataStreamPtr output = std::make_unique<CFileOutputStream>(outputFileName);

	CopyFile(input, output);

	output->Close();

	REQUIRE(AreFilesEqual(inputFileName, outputFileName));
}

TEST_CASE("Check reading file")
{
	// File input: "TEST\r\n" for windows end of line - \r\n
	CFileInputStream input("input.txt");
	
	GIVEN("Reading by byte")
	{
		REQUIRE(input.ReadByte() == 'T');
		REQUIRE(input.ReadByte() == 'E');
		REQUIRE(input.ReadByte() == 'S');
		REQUIRE(input.ReadByte() == 'T');
		REQUIRE(input.ReadByte() == '\r');
		REQUIRE(input.ReadByte() == '\n');

		REQUIRE_THROWS_AS(input.ReadByte(), std::ios_base::failure);

		THEN("is EOF")
		{
			REQUIRE(input.IsEOF());
		}
	}

	GIVEN("Reading by block")
	{
		char buffer[6];
		REQUIRE(input.ReadBlock(buffer, 6) == 6);

		THEN("in buffer: 'TEST'")
		{
			REQUIRE(buffer[0] == 'T');
			REQUIRE(buffer[1] == 'E');
			REQUIRE(buffer[2] == 'S');
			REQUIRE(buffer[3] == 'T');
			REQUIRE(buffer[4] == '\r');
			REQUIRE(buffer[5] == '\n');
		}
	}
}

TEST_CASE("Check writing file")
{
	CFileInputStream input("input.txt");
	CFileOutputStream output("output.txt");

	GIVEN("Writing by byte")
	{
		while (!input.IsEOF())
		{
			try
			{
				output.WriteByte(input.ReadByte());
			}
			catch (...)
			{}
		}

		output.Close();

		CFileInputStream input2("output.txt");

		while (!input.IsEOF())
		{
			try
			{
				REQUIRE(input.ReadByte() == input2.ReadByte());
			}
			catch (...)
			{}
		}
	}

	GIVEN("Writing by block")
	{
		char buffer[6];

		input.ReadBlock(buffer, 6);

		output.WriteBlock(buffer, 6);
		output.Close();

		CFileInputStream input2("output.txt");

		char buffer2[6];
		input2.ReadBlock(buffer2, 6);

		REQUIRE(buffer2[0] == buffer[0]);
		REQUIRE(buffer2[1] == buffer[1]);
		REQUIRE(buffer2[2] == buffer[2]);
		REQUIRE(buffer2[3] == buffer[3]);
		REQUIRE(buffer2[4] == buffer[4]);
		REQUIRE(buffer2[5] == buffer[5]);
	}
}

TEST_CASE("Check reading memory")
{
	std::vector<uint8_t> TEXT_MEMORY = { 'a', 's', '1', '\n' };
	std::vector<uint8_t> EMPTY_MEMORY = {};

	CMemoryInputStream istream = CMemoryInputStream(TEXT_MEMORY);

	WHEN("starting read")
	{
		REQUIRE(istream.ReadByte() == 'a');
		REQUIRE(istream.ReadByte() == 's');
		REQUIRE(istream.ReadByte() == '1');
		REQUIRE(istream.ReadByte() == '\n');

		REQUIRE_THROWS_AS(istream.ReadByte(), std::ios_base::failure);

		THEN("is EOF")
		{
			REQUIRE(istream.IsEOF());
		}
	}

	WHEN("reading to buffer")
	{
		char buffer[4];
		REQUIRE(istream.ReadBlock(buffer, 4) == 4);

		THEN("in buffer: 1V#c")
		{
			REQUIRE(buffer[0] == 'a');
			REQUIRE(buffer[1] == 's');
			REQUIRE(buffer[2] == '1');
			REQUIRE(buffer[3] == '\n');
		}
	}
}

TEST_CASE("Check writing memory")
{
	std::vector<uint8_t> MEMORY_OUTPUT = {};

	CMemoryOutputStream istream = CMemoryOutputStream(MEMORY_OUTPUT);

	WHEN("starting writing")
	{
		REQUIRE_NOTHROW(istream.WriteByte('T'));
		REQUIRE_NOTHROW(istream.WriteByte('E'));
		REQUIRE_NOTHROW(istream.WriteByte('S'));
		REQUIRE_NOTHROW(istream.WriteByte('T'));

		THEN("data in file will be 'TEST'")
		{
			REQUIRE(MEMORY_OUTPUT[0]);
			REQUIRE(MEMORY_OUTPUT[1]);
			REQUIRE(MEMORY_OUTPUT[2]);
			REQUIRE(MEMORY_OUTPUT[3]);
		}
	}

	WHEN("writing buffer")
	{
		char buffer[4] = { 'T', 'E', 'S', 'T' };

		REQUIRE_NOTHROW(istream.WriteBlock(buffer, 4));

		THEN("data in file will be 'TEST'")
		{
			REQUIRE(MEMORY_OUTPUT[0] == 'T');
			REQUIRE(MEMORY_OUTPUT[1] == 'E');
			REQUIRE(MEMORY_OUTPUT[2] == 'S');
			REQUIRE(MEMORY_OUTPUT[3] == 'T');
		}
	}
}