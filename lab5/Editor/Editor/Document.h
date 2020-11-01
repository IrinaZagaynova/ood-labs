#pragma once
#include "History.h"
#include "IDocument.h"
#include "CommandSink.h"
#include <vector>

class CDocument : public IDocument
{
public:
	// ��������� �������� ������ � ��������� ������� (������� ����������� ��������)
	// ���� �������� position �� ������, ������� ���������� � ����� ���������
	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text,
		optional<size_t> position = none) override;

	// ��������� ����������� � ��������� ������� (������� ����������� ��������)
	// �������� path ������ ���� � ������������ �����������
	// ��� ������� ����������� ������ ������������ � ���������� images 
	// ��� ������������� ��������������� ������
	std::shared_ptr<IImage> InsertImage(const Path& path, int width, int height,
		optional<size_t> position = none) override;

	// ���������� ���������� ��������� � ���������
	size_t GetItemsCount()const override;

	// ������ � ��������� �����������
	CConstDocumentItem GetItem(size_t index)const override;
	CDocumentItem GetItem(size_t index) override;

	// ������� ������� �� ���������
	void DeleteItem(size_t index) override;

	// ���������� ��������� ���������
	std::string GetTitle()const override;
	// �������� ��������� ���������
	void SetTitle(const std::string& title) override;

	// �������� � ����������� �������� Undo
	bool CanUndo()const override;
	// �������� ������� ��������������
	void Undo() override;

	// �������� � ����������� �������� Redo
	bool CanRedo()const override;
	// ��������� ���������� ������� ��������������
	void Redo() override;

	// ��������� �������� � ������� html. ����������� ����������� � ���������� images.
	// ���� � ������������ ����������� ������������ ���� � ������������ HTML �����
	void Save(const Path& path)const override;

private:
	std::string EncodeToHtml(const std::string& text) const;

	std::vector<CDocumentItem> m_items;
	std::string m_title;
	CHistory m_history;
};