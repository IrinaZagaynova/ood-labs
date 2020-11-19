#pragma once
#include "ISlide.h"

class CSlide : public ISlide
{
public:
	CSlide(int width, int height, RGBAColor backgroundColor);

	int GetWidth()const override;
	int GetHeight()const override;

	size_t GetShapesCount()const override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index)const override;

	void InsertShape(const std::shared_ptr<IShape>& shape, size_t position = std::numeric_limits<size_t>::max()) override;
	void RemoveShapeAtIndex(size_t index) override;

	RGBAColor GetBackgroundColor()const override;
	void SetBackgroundColor(RGBAColor color) override;
	
	void Draw(ICanvas& canvas) const override;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
	int m_width;
	int m_height;
	RGBAColor m_backgroundColor;
};