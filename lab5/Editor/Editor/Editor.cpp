#include "Editor.h"

CEditor::CEditor(std::istream& istrm, std::ostream& ostrm)
	: m_istrm(istrm)
	, m_ostrm(ostrm)
	, m_menu(istrm, ostrm)
	, m_document(make_unique<CDocument>())
{
	m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
	m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
	AddMenuItem("setTitle", "Changes title. Args: <new title>", &CEditor::SetTitle);
	AddMenuItem("list", "Show document", &CEditor::List);
	AddMenuItem("insertParagraph", "Insert Paragraph", &CEditor::InsertParagraph);
	AddMenuItem("insertImage", "Insert Image", &CEditor::InsertImage);
	AddMenuItem("replaceText", "Replace Text", &CEditor::ReplaceText);
	AddMenuItem("resizeImage", "Resize Image", &CEditor::ResizeImage);
	AddMenuItem("deleteItem", "Delete Item", &CEditor::DeleteItem);
	AddMenuItem("save", "Save", &CEditor::Save);
	AddMenuItem("undo", "Undo command", &CEditor::Undo);
	AddMenuItem("redo", "Redo undone command", &CEditor::Redo);
}

void CEditor::Start()
{
	m_menu.Run();
}

void CEditor::AddMenuItem(const string& shortcut, const string& description, MenuHandler handler)
{
	m_menu.AddItem(shortcut, description, bind(handler, this, _1));
}

void CEditor::SetTitle(istream& in)
{
	string head;
	string tail;

	if (in >> head)
	{
		getline(in, tail);
	}
	string title = head + tail;

	m_document->SetTitle(title);
}

void CEditor::List(istream&)
{
	if (m_document->GetTitle() != "")
	{
		m_ostrm << "Title: " << m_document->GetTitle() << "\n";
	}

	for (size_t i = 0; i < m_document->GetItemsCount(); i++)
	{
		if (auto paragpaph = m_document->GetItem(i).GetParagraph())
		{
			m_ostrm << i << ". Paragraph: " << paragpaph->GetText() << endl;
		}
		else if (auto image = m_document->GetItem(i).GetImage())
		{
			m_ostrm << i << ". Image: " << image->GetWidth() << " " << image->GetHeight() << " " << image->GetPath() << endl;
		}
	}
}

int CEditor::StringToInt(const string& str)
{
	try
	{
		return boost::lexical_cast<int>(str);
	}
	catch (const boost::bad_lexical_cast&)
	{
		throw invalid_argument("invalid position\n");
	}
}

optional<size_t> CEditor::GetItemPosition(const string& position)
{
	if (position == "end")
	{
		return none;
	}
	else
	{
		int positionNum = StringToInt(position);
		if (positionNum < 0)
		{
			throw invalid_argument("item position can't be negative\n");
		}

		return optional<size_t>(positionNum);
	}
}

std::string GetText(istream& in)
{
	std::string text, line;
	while (std::getline(in, line))
	{
		text.append(line);
	}
	return text;
}

void CEditor::InsertParagraph(istream& in)
{
	std::string position;
	in >> position;
	std::string text = GetText(in);

	try
	{
		m_document->InsertParagraph(text, GetItemPosition(position));
	}
	catch (const std::exception& e)
	{
		m_ostrm << e.what();
	}
}

void CEditor::InsertImage(istream& in)
{
	string position;
	Path path;
	int width, height;

	try
	{
		in >> position >> width >> height >> path;
		m_document->InsertImage(path, width, height, GetItemPosition(position));
	}
	catch (const std::exception& e)
	{
		m_ostrm << e.what();
	}
}

shared_ptr<IParagraph> CEditor::GetParagraphByPosition(size_t positionNum)
{
	if (m_document->GetItemsCount() <= positionNum)
	{
		throw std::invalid_argument("invalid position\n");
	}

	auto paragraphPtr = m_document->GetItem(positionNum).GetParagraph();
	if (!paragraphPtr)
	{
		throw std::invalid_argument("there is no paragraph in this position\n");
	}
	
	return paragraphPtr;
}

void CEditor::ReplaceText(istream& in)
{
	try
	{
		string position;
		in >> position;
		int positionNum = StringToInt(position);
		string text = GetText(in);
		auto paragraphPtr = GetParagraphByPosition(positionNum);
		paragraphPtr->SetText(text);
	}
	catch (const exception& e)
	{
		m_ostrm << e.what();
	}
}

shared_ptr<IImage> CEditor::GetImageByPosition(size_t positionNum)
{
	if (m_document->GetItemsCount() <= positionNum)
	{
		throw std::invalid_argument("invalid position\n");
	}

	auto imagePtr = m_document->GetItem(positionNum).GetImage();
	if (!imagePtr)
	{
		throw std::invalid_argument("there is no image in this position\n");
	}

	return imagePtr;
}

void CEditor::ResizeImage(istream& in)
{
	try
	{
		string position;
		in >> position;
		int positionNum = StringToInt(position);
		int width, height;
		in >> width >> height;
		auto imagePtr = GetImageByPosition(positionNum);
		imagePtr->Resize(width, height);
	}
	catch (const exception& e)
	{
		m_ostrm << e.what();
	}
}

void CEditor::DeleteItem(istream& in)
{
	string position;
	in >> position;
	try
	{
		int positionNum = StringToInt(position);
		m_document->DeleteItem(size_t(positionNum));
	}
	catch (const std::exception& e)
	{
		m_ostrm << e.what();
	}
}

void CEditor::Save(istream& in)
{
	string path;
	in >> path;
	try
	{
		m_document->Save(path);
	}
	catch (const exception& e)
	{
		m_ostrm << e.what();
	}
}

void CEditor::Undo(istream&)
{
	if (m_document->CanUndo())
	{
		m_document->Undo();
	}
	else
	{
		m_ostrm << "Can't undo" << endl;
	}
}

void CEditor::Redo(istream&)
{
	if (m_document->CanRedo())
	{
		m_document->Redo();
	}
	else
	{
		m_ostrm << "Can't redo" << endl;
	}
}
