#pragma once
#include "IInputDataStream.h"
#include <vector>

class СMemoryInputStream : public IInputDataStream
{
public:
	СMemoryInputStream(std::vector<uint8_t>& data);

	// Возвращает признак достижения конца данных потока
	// Выбрасывает исключение std::ios_base::failuer в случае ошибки
	bool IsEOF()const override;

	// Считывает байт из потока. 
	// Выбрасывает исключение std::ios_base::failure в случае ошибки
	uint8_t ReadByte() override;

	// Считывает из потока блок данных размером size байт, записывая его в память
	// по адресу dstBuffer
	// Возвращает количество реально прочитанных байт. Выбрасывает исключение в случае ошибки
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	const std::vector<uint8_t>& m_data;
	std::streamsize m_position = 0;
};