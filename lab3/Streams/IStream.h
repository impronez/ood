#pragma once

#include <iostream>
#include <cstdint>

class IInputDataStream
{
public:
    // ���������� ������� ���������� ����� ������ ������
    // ����������� ���������� std::ios_base::failure � ������ ������
    virtual bool IsEOF()const = 0;

    // ��������� ���� �� ������. 
    // ����������� ���������� std::ios_base::failure � ������ ������
    virtual uint8_t ReadByte() = 0;

    // ��������� �� ������ ���� ������ �������� size ����, ��������� ��� � ������
    // �� ������ dstBuffer
    // ���������� ���������� ������� ����������� ����. ����������� ���������� � ������ ������
    virtual std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) = 0;

    virtual ~IInputDataStream() = default;
};

class IOutputDataStream
{
public:
    // ���������� � ����� ������ ����
    // ����������� ���������� std::ios_base::failure � ������ ������
    virtual void WriteByte(uint8_t data) = 0;

    // ���������� � ����� ���� ������ �������� size ����, 
    // ��������������� �� ������ srcData,
    // � ������ ������ ����������� ���������� std::ios_base::failure
    virtual void WriteBlock(const void* srcData, std::streamsize size) = 0;

    // ��������� �����. ����������� �������� ������ ����������� std::logic_error
    virtual void Close() = 0;

    virtual ~IOutputDataStream() = default;

};

typedef std::unique_ptr<IInputDataStream> IInputDataStreamPtr;
typedef std::unique_ptr<IOutputDataStream> IOutputDataStreamPtr;