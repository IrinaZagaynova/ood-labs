#include "Group.h"
#include "CompoundOutlineStyle.h"
#include "CompoundFillStyle.h"
#include <algorithm>

CGroup::CGroup()
{
    auto outlineStyleEnumerator = [&](std::function<void(IOutlineStyle&)> callback) {
        for (auto& shape : m_shapes)
        {
            callback(*shape->GetLineStyle());
        }
    };

    m_outlineStyle = std::make_shared<CCompoundOutlineStyle>(outlineStyleEnumerator);

    auto fillStyleEnumerator = [&](std::function<void(IStyle&)> callback) {
        for (auto& shape : m_shapes)
        {
            callback(*shape->GetFillStyle());
        }
    };

    m_fillStyle = std::make_shared<CCompoundFillStyle>(fillStyleEnumerator);
}

std::optional<RectD> CGroup::GetFrame() const
{
    if (m_shapes.empty())
    {
        return std::nullopt;
    }

    bool isInitialized = false;
    double minX, maxX, minY, maxY;

    for (auto& shape : m_shapes)
    {
        if (shape->GetFrame().has_value())
        {
            auto frame = *shape->GetFrame();

            if (!isInitialized)
            {
                minX = frame.left;
                maxY = frame.top;
                maxX = minX + frame.width;
                minY = maxY - frame.height;
                isInitialized = true;
            }
            else
            {
                minX = std::min(minX, frame.left);            
                maxY = std::max(maxY, frame.top);
                maxX = std::max(maxX, frame.left + frame.width);
                minY = std::min(minY, frame.top - frame.height);
            }
        }
    }

    if (isInitialized)
    {
        return RectD{ minX, maxY, maxX - minX, maxY - minY };
    }

    return std::nullopt;
}

void CGroup::SetFrame(const RectD& rect)
{   
    if (!GetFrame().has_value())
    {
        return;
    }

    auto groupFrame = *GetFrame();
    double minX, maxY, width, height;

    for (auto& shape : m_shapes)
    {
        if (shape->GetFrame().has_value())
        {
            auto shapeFrame = *shape->GetFrame();

            minX = rect.left - (groupFrame.left - shapeFrame.left) * rect.width / groupFrame.width;
            maxY = rect.top - (groupFrame.top - shapeFrame.top) * rect.height / groupFrame.height;
            width = shapeFrame.width * rect.width / groupFrame.width;
            height = shapeFrame.height * rect.height / groupFrame.height;

            shape->SetFrame({ minX, maxY, width, height });
        }
    }
}

std::shared_ptr<IOutlineStyle> CGroup::GetLineStyle() const
{
    return m_outlineStyle;
}

std::shared_ptr<IStyle> CGroup::GetFillStyle() const
{
    return m_fillStyle;
}

void CGroup::Draw(ICanvas& canvas) const
{
    for (auto& shape : m_shapes)
    {
        shape->Draw(canvas);
    }
}

std::shared_ptr<IGroup> CGroup::GetGroup()
{
	return shared_from_this();
}

size_t CGroup::GetShapesCount() const
{
    return m_shapes.size();
}

std::shared_ptr<IShape> CGroup::GetShapeAtIndex(size_t index) const
{
    if (index >= GetShapesCount())
    {
        throw std::out_of_range("There are no shapes with this index");
    }
    return m_shapes.at(index);
}

void CGroup::InsertShape(std::shared_ptr<IShape> shape, size_t index)
{
    if (index > GetShapesCount())
    {
        throw std::out_of_range("Position out of range");
    }
    m_shapes.insert(m_shapes.begin() + index, shape);
}

void CGroup::RemoveShapeAtIndex(size_t index)
{
    if (index >= GetShapesCount())
    {
        throw std::out_of_range("There are no shapes with this index");
    }
    m_shapes.erase(m_shapes.begin() + index);
}
