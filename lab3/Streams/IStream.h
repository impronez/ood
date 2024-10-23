#pragma once

#include <iostream>
#include <cstdint>

class IInputDataStream
{
public:
    // Возвращает признак достижения конца данных потока
    // Выбрасывает исключение std::ios_base::failure в случае ошибки
    virtual bool IsEOF()const = 0;

    // Считывает байт из потока. 
    // Выбрасывает исключение std::ios_base::failure в случае ошибки
    virtual uint8_t ReadByte() = 0;

    // Считывает из потока блок данных размером size байт, записывая его в память
    // по адресу dstBuffer
    // Возвращает количество реально прочитанных байт. Выбрасывает исключение в случае ошибки
    virtual std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) = 0;

    virtual ~IInputDataStream() = default;
};

class IOutputDataStream
{
public:
    // Записывает в поток данных байт
    // Выбрасывает исключение std::ios_base::failure в случае ошибки
    virtual void WriteByte(uint8_t data) = 0;

    // Записывает в поток блок данных размером size байт, 
    // располагающийся по адресу srcData,
    // В случае ошибки выбрасывает исключение std::ios_base::failure
    virtual void WriteBlock(const void* srcData, std::streamsize size) = 0;

    // Закрывает поток. Последующие операции записи выбрасывают std::logic_error
    virtual void Close() = 0;

    virtual ~IOutputDataStream() = default;

};

typedef std::unique_ptr<IInputDataStream> IInputDataStreamPtr;
typedef std::unique_ptr<IOutputDataStream> IOutputDataStreamPtr;