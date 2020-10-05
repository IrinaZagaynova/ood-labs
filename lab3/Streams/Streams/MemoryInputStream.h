#pragma once
#include "IInputDataStream.h"
#include <vector>

class �MemoryInputStream : public IInputDataStream
{
public:
	�MemoryInputStream(std::vector<uint8_t>& data);

	// ���������� ������� ���������� ����� ������ ������
	// ����������� ���������� std::ios_base::failuer � ������ ������
	bool IsEOF()const override;

	// ��������� ���� �� ������. 
	// ����������� ���������� std::ios_base::failure � ������ ������
	uint8_t ReadByte() override;

	// ��������� �� ������ ���� ������ �������� size ����, ��������� ��� � ������
	// �� ������ dstBuffer
	// ���������� ���������� ������� ����������� ����. ����������� ���������� � ������ ������
	std::streamsize ReadBlock(void* dstBuffer, std::streamsize size) override;

private:
	const std::vector<uint8_t>& m_data;
	std::streamsize m_position = 0;
};