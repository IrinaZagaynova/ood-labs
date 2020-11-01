#pragma once
#include "IParagraph.h"
#include "IImage.h"
#include <memory>

class CConstDocumentItem
{
public:
	CConstDocumentItem(const std::shared_ptr<IParagraph>& paragraph)
		: m_paragraph(paragraph)
	{
	}

	CConstDocumentItem(const std::shared_ptr<IImage>& image)
		: m_image(image)
	{
	}
	// ���������� ��������� �� ����������� �����������, ���� nullptr,
	// ���� ������� �� �������� ������������
	std::shared_ptr<const IImage> GetImage()const
	{
		m_image;
	}
	// ���������� ��������� �� ����������� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<const IParagraph> GetParagraph()const
	{
		return m_paragraph;
	}
	virtual ~CConstDocumentItem() = default;
private:
	std::shared_ptr<const IParagraph> m_paragraph;
	std::shared_ptr<const IImage> m_image;
};