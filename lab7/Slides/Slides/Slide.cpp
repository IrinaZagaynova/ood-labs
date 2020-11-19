#include "Slide.h"

CSlide::CSlide(int width, int height, RGBAColor backgroundColor)
	: m_width(width)
	, m_height(height)
	, m_backgroundColor(backgroundColor)
{
}

int CSlide::GetWidth() const
{
	return m_width;
}

int CSlide::GetHeight() const
{
	return m_height;
}

size_t CSlide::GetShapesCount() const
{
	return m_shapes.size();
}

std::shared_ptr<IShape> CSlide::GetShapeAtIndex(size_t index) const
{
	if (index >= GetShapesCount())
	{
		throw std::out_of_range("There are no shapes with this index");
	}
	return m_shapes.at(index);
}

void CSlide::InsertShape(const std::shared_ptr<IShape>& shape, size_t position)
{
	if (position > GetShapesCount())
	{
		throw std::out_of_range("Position out of range");
	}
	m_shapes.insert(m_shapes.begin() + position, shape);
	
}

void CSlide::RemoveShapeAtIndex(size_t index)
{
	if (index >= GetShapesCount())
	{
		throw std::out_of_range("There are no shapes with this index");
	}
	m_shapes.erase(m_shapes.begin() + index);
}

RGBAColor CSlide::GetBackgroundColor() const
{
	return m_backgroundColor;
}

void CSlide::SetBackgroundColor(RGBAColor color)
{
	m_backgroundColor = color;
}

void CSlide::Draw(ICanvas& canvas) const
{
	for (auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}
