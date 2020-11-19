#pragma once
#include "IShape.h"

class CShape : public IShape
{
public:
	CShape()
		: m_outlineStyle(std::make_shared<COutlineStyle>())
		, m_fillStyle(std::make_shared<CFillStyle>())
	{
	}

	std::shared_ptr<IStyle> GetFillStyle()const override
	{
		return m_fillStyle;
	}

	std::shared_ptr<IOutlineStyle> GetLineStyle()const override
	{
		return m_outlineStyle;
	}

	std::shared_ptr<IGroup> GetGroup() override
	{
		return nullptr;
	}

private:
	std::shared_ptr<IStyle> m_fillStyle;
	std::shared_ptr<IOutlineStyle> m_outlineStyle;
};
