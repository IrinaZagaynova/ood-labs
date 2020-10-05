#pragma once
#include "IOutputDataStream.h"
#include <fstream>

class CFileOutputStream : public IOutputDataStream
{
public:
	CFileOutputStream(const std::string& fileName);

	// ���������� � ����� ������ ����
	// ����������� ���������� std::ios_base::failure � ������ ������
	void WriteByte(uint8_t data) override;

	// ���������� � ����� ���� ������ �������� size ����, 
	// ��������������� �� ������ srcData,
	// � ������ ������ ����������� ���������� std::ios_base::failure
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	std::ofstream m_stream;
};