#pragma once
#include "IOutputDataStream.h"
#include <memory>
#include <iostream>

class COutputStreamDecorator : public IOutputDataStream
{
protected:
	COutputStreamDecorator(std::unique_ptr<IOutputDataStream>&& stream);
	virtual void WriteByte(uint8_t data) override;
	virtual void WriteBlock(const void* srcData, std::streamsize size) override;
	
protected:
	std::unique_ptr<IOutputDataStream> m_stream;
};