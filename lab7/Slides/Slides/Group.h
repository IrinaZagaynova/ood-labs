#pragma once
#include "IGroup.h"
#include "OutlineStyle.h"
#include "FillStyle.h"
#include <vector>
#include <memory>

class CGroup : public IGroup, public std::enable_shared_from_this<IGroup>
{
public:
	CGroup();

	std::optional<RectD> GetFrame()const override; 
	void SetFrame(const RectD& rect) override;

	std::shared_ptr<IOutlineStyle> GetLineStyle()const override;
	std::shared_ptr<IStyle> GetFillStyle()const override;

	virtual void Draw(ICanvas& canvas)const override;

	std::shared_ptr<IGroup> GetGroup() override;

	size_t GetShapesCount()const override;
	std::shared_ptr<IShape> GetShapeAtIndex(size_t index)const override;

	void InsertShape(std::shared_ptr<IShape> shape, size_t index) override;
	void RemoveShapeAtIndex(size_t index) override;

private:
	std::vector<std::shared_ptr<IShape>> m_shapes;
	std::shared_ptr<IOutlineStyle> m_outlineStyle;
	std::shared_ptr<IStyle> m_fillStyle;
};