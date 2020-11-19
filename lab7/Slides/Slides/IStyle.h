#pragma once
#include "CommonTypes.h"
#include <optional>

class IStyle
{
public:
	virtual std::optional<bool> IsEnabled()const = 0;
	virtual void Enable(bool enable) = 0;

	virtual std::optional<RGBAColor> GetColor()const = 0;
	virtual void SetColor(const RGBAColor color) = 0;

	virtual ~IStyle() {};
};