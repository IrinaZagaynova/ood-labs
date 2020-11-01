#pragma once
#include "Menu.h"
#include "Document.h"
#include <iostream>
#include <sstream>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace std::placeholders;

class CEditor
{
public:
	CEditor(std::istream& istrm = std::cin, std::ostream& ostrm = std::cout);
	void Start();

private:
	// Указатель на метод класса CEditor, принимающий istream& и возвращающий void
	typedef void (CEditor::* MenuHandler)(istream& in);

	void AddMenuItem(const string& shortcut, const string& description, MenuHandler handler);
	void SetTitle(istream& in);
	void List(istream&);
	int StringToInt(const string& str);
	optional<size_t> GetItemPosition(const string& position);
	void InsertParagraph(istream& in);
	void InsertImage(istream& in);
	shared_ptr<IParagraph> GetParagraphByPosition(size_t positionNum);
	void ReplaceText(istream& in);
	shared_ptr<IImage> GetImageByPosition(size_t positionNum);
	void ResizeImage(istream& in);
	void DeleteItem(istream& in);
	void Save(istream& in);
	void Undo(istream&);
	void Redo(istream&);

	CMenu m_menu;
	std::istream& m_istrm;
	std::ostream& m_ostrm;
	unique_ptr<IDocument> m_document;
};