#pragma once
#include "Shape.h"
#include "stdafx.h"

class IShapeFactory
{
public:
	virtual ~IShapeFactory() = default;
	virtual std::unique_ptr<CShape> CreateShape(const std::string& description) = 0;
};