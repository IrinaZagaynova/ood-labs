#pragma once
#include "IOutputDataStream.h"
#include <vector>

class CMemoryOutputStream : public IOutputDataStream
{
public:
	CMemoryOutputStream(std::vector<uint8_t>& data);

	// ���������� � ����� ������ ����
	// ����������� ���������� std::ios_base::failure � ������ ������
	void WriteByte(uint8_t data) override;

	// ���������� � ����� ���� ������ �������� size ����, 
	// ��������������� �� ������ srcData,
	// � ������ ������ ����������� ���������� std::ios_base::failure
	void WriteBlock(const void* srcData, std::streamsize size) override;

private:
	std::vector<uint8_t>& m_data;
	std::streamsize m_position = 0;
};