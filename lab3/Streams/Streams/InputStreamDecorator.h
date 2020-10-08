#pragma once
#include "IInputDataStream.h"
#include <memory>

class CInputStreamDecorator : public IInputDataStream
{
protected:
	CInputStreamDecorator(std::unique_ptr<IInputDataStream>&& inputStream)
		: m_stream(move(inputStream))
	{
	}

protected:
	std::unique_ptr<IInputDataStream> m_stream;
};