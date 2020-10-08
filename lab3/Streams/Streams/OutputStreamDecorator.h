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
	
protected:
	std::unique_ptr<IOutputDataStream> m_stream;
};