#pragma once
#include "IOutputDataStream.h"
#include <memory>
#include <iostream>

class COutputStreamDecorator : public IOutputDataStream
{
protected:
	COutputStreamDecorator(std::unique_ptr<IOutputDataStream>&& stream)
		: m_stream(move(stream))
	{
	}
	virtual void WriteByte(uint8_t data) = 0;
	virtual void WriteBlock(const void* srcData, std::streamsize size) = 0;
	
protected:
	std::unique_ptr<IOutputDataStream> m_stream;
};