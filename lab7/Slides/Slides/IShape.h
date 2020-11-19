#pragma once
#include "CommonTypes.h"
#include "IStyle.h"
#include "OutlineStyle.h"
#include "FillStyle.h"
#include "IDrawable.h"
#include <memory>

class IGroup;

class IShape : public IDrawable
{
public:
	virtual std::optional<RectD> GetFrame()const = 0;
	virtual void SetFrame(const RectD& rect) = 0;

	virtual std::shared_ptr<IOutlineStyle> GetLineStyle()const = 0;
	virtual std::shared_ptr<IStyle> GetFillStyle()const = 0;

	virtual std::shared_ptr<IGroup> GetGroup() = 0;
	
	virtual ~IShape() {};
};
