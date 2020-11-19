#pragma once
#include "CommonTypes.h"
#include "ICanvas.h"
#include "Shape.h"
#include <memory>

class ISlide : public IDrawable
{
public:
	virtual int GetWidth()const = 0;
	virtual int GetHeight()const = 0;

	virtual size_t GetShapesCount()const = 0;
	virtual std::shared_ptr<IShape> GetShapeAtIndex(size_t index)const = 0;

	virtual void InsertShape(const std::shared_ptr<IShape>& shape, size_t position = std::numeric_limits<size_t>::max()) = 0;
	virtual void RemoveShapeAtIndex(size_t index) = 0;

	virtual RGBAColor GetBackgroundColor()const = 0;
	virtual void SetBackgroundColor(RGBAColor color) = 0;
};