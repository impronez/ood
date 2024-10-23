#include <iostream>
#include "CFileInputStream.h"
#include "CFileOutputStream.h"
#include "COutputStreamDecorator.h"
#include "CInputStreamDecorator.h"

struct Streams
{
    IInputDataStreamPtr input;
    IOutputDataStreamPtr output;
};

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
        {}
    }
    
    std::cout << "Finished!\n";
}

Streams GetStreamsFromArgs(int argc, char* argv[])
{
    if (argc < 3)
    {
        throw std::invalid_argument("Invalid count of arguments");
    }

    std::string inputFileName = argv[argc - 2];
    std::string outputFileName = argv[argc - 1];

    IInputDataStreamPtr inputPtr = std::make_unique<CFileInputStream>(inputFileName);
    IOutputDataStreamPtr outputPtr = std::make_unique<CFileOutputStream>(outputFileName);

    for (int i = 1; i <= argc - 2; ++i)
    {
        std::string arg = argv[i];
        if (arg == "--compress")
        {
            outputPtr = std::make_unique<CCompressedOutputStream>(std::move(outputPtr));
        }
        else if (arg == "--decompress")
        {
            inputPtr = std::make_unique<CDecompressedInputStream>(std::move(inputPtr));
        }
        else if (arg == "--encrypt")
        {
            ++i;
            int key = std::stoi(argv[i]);
            outputPtr = std::make_unique<CEncryptedOutputStream>(std::move(outputPtr), key);
        }
        else if (arg == "--decrypt")
        {
            ++i;
            int key = std::stoi(argv[i]);
            inputPtr = std::make_unique<CDecryptedInputStream>(std::move(inputPtr), key);
        }
        else
        {
            continue;
        }
    }

    return { std::move(inputPtr), std::move(outputPtr) };
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

int main(int argc, char* argv[])
{
    try
    {
        Streams streams = GetStreamsFromArgs(argc, argv);

        CopyFile(streams.input, streams.output);
    }
    catch (const std::exception& err)
    {
        std::cout << err.what() << std::endl;
    }
}
