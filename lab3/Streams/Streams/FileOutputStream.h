#pragma once
#include "IOutputDataStream.h"
#include <fstream>

class CFileOutputStream : public IOutputDataStream
{
public:
	CFileOutputStream(const std::string& fileName);

	// Записывает в поток данных байт
	// Выбрасывает исключение std::ios_base::failure в случае ошибки
	void WriteByte(uint8_t data) override;

	// Записывает в поток блок данных размером size байт, 
	// располагающийся по адресу srcData,
	// В случае ошибки выбрасывает исключение std::ios_base::failure
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	std::ofstream m_stream;
};