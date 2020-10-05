#include "CompressOutputStream.h"

CCompressOutputStream::CCompressOutputStream(std::unique_ptr<IOutputDataStream>&& stream)
	: COutputStreamDecorator(move(stream))
{
}

CCompressOutputStream::~CCompressOutputStream()
{
	if (m_counter != 0)
	{
		try 	
		{
			FlushChunk();
		}
		catch (const std::exception&) 
		{
		}
	}
}

void CCompressOutputStream::FlushChunk()
{
	m_stream->WriteByte(m_counter);
	m_stream->WriteByte(m_value);
	m_counter = 0;
}

void CCompressOutputStream::WriteByte(uint8_t data)
{
	if (m_counter == 0)
	{
		m_value = data;
		m_counter++;
	}
	else if ((m_value == data) && (m_counter < 255))
	{
		m_counter++;
	}
	else
	{
		FlushChunk(); 
		m_value = data;
		m_counter++;
	}
}

void CCompressOutputStream::WriteBlock(const void* srcData, std::streamsize size)
{
	auto data = static_cast<const uint8_t*>(srcData);
	for (std::streamsize i = 0; i < size; i++)
	{
		WriteByte(*data++);
	}
}