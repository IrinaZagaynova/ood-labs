#pragma once
#include "IShapeFactory.h"
#include "PictureDraft.h"
#include <iostream>

class CDesigner
{
public:
	CDesigner(IShapeFactory& factory);
	CPictureDraft CreateDraft(std::istream& inputData);

private:
	IShapeFactory& m_factory;
};