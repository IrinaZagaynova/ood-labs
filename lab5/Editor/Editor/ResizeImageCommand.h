#pragma once
#include "AbstractCommand.h"
#include <algorithm>

class CResizeImageCommand : public CAbstractCommand
{
public:
	CResizeImageCommand(int& width, int& height, int newWidth, int newHeight)
		: m_width(width)
		, m_height(height)
		, m_newWidth(newWidth)
		, m_newHeight(newHeight)
	{
	}

protected:
	void DoExecute() override
	{
		std::swap(m_width, m_newWidth);
		std::swap(m_height, m_newHeight);
	}
	void DoUnexecute() override
	{
		std::swap(m_width, m_newWidth);
		std::swap(m_height, m_newHeight);
	}

private:
	int m_newWidth, m_newHeight;
	int& m_width, & m_height;
};