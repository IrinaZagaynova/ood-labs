#include "CompoundFillStyle.h"

CCompoundFillStyle::CCompoundFillStyle(FillStyleEnumerator enumerator)
    : m_enumerator(enumerator)
{
}

std::optional<bool> CCompoundFillStyle::IsEnabled() const
{
    std::optional<bool> isEnabled;
    bool isInitialized = false;

    auto callback = [&](IStyle& style) {
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

void CCompoundFillStyle::Enable(bool enable)
{
    m_enumerator([&](IStyle& style) {
        style.Enable(enable);
    });
}

std::optional<RGBAColor> CCompoundFillStyle::GetColor() const
{
    std::optional<RGBAColor> color;
    bool isInitialized = false;

    auto callback = [&](IStyle& style) {
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

void CCompoundFillStyle::SetColor(const RGBAColor color)
{
    m_enumerator([&](IStyle& style) {
        style.SetColor(color);
    });
}
