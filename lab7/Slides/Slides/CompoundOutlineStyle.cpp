#include "CompoundOutlineStyle.h"

CCompoundOutlineStyle::CCompoundOutlineStyle(OutlineStyleEnumerator enumerator)
    : m_enumerator(enumerator)
{
}

std::optional<bool> CCompoundOutlineStyle::IsEnabled() const
{
    std::optional<bool> isEnabled;
    bool isInitialized = false;

    auto callback = [&](IOutlineStyle& style) {
        if (!isInitialized)
        {
            isEnabled = style.IsEnabled();
            isInitialized = true;
        }
        else if (isEnabled != style.IsEnabled())
        {
            isEnabled = std::nullopt;
        }
    };

    m_enumerator(callback);

    return isEnabled;
}

void CCompoundOutlineStyle::Enable(bool enable)
{
    m_enumerator([&](IOutlineStyle& style) {
        style.Enable(enable);
    });
}

std::optional<RGBAColor> CCompoundOutlineStyle::GetColor() const
{
    std::optional<RGBAColor> color;
    bool isInitialized = false;

    auto callback = [&](IOutlineStyle& style) {
        if (!isInitialized)
        {
            color = style.GetColor();
            isInitialized = true;
        }
        else if (color != style.GetColor())
        {
            color = std::nullopt;
        }
    };

    m_enumerator(callback);

    return color;
}

void CCompoundOutlineStyle::SetColor(const RGBAColor color)
{
    m_enumerator([&](IOutlineStyle& style) {
        style.SetColor(color);
    });
}

std::optional<float> CCompoundOutlineStyle::GetLineWidth() const
{
    std::optional<float> width;
    bool isInitialized = false;

    auto callback = [&](IOutlineStyle& style) {
        if (!isInitialized)
        {
            width = style.GetLineWidth();
            isInitialized = true;
        }
        else if (width != style.GetLineWidth())
        {
            width = std::nullopt;
        }
    };

    m_enumerator(callback);

    return width;
}

void CCompoundOutlineStyle::SetLineWidth(float lineWidth)
{
    m_enumerator([&](IOutlineStyle& style) {
        style.SetLineWidth(lineWidth);
    });
}
