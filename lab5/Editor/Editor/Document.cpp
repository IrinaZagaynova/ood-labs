#include "Document.h"
#include "Paragraph.h"
#include "Image.h"
#include "Commands.h"
#include <fstream>

std::shared_ptr<IParagraph> CDocument::InsertParagraph(const std::string& text, optional<size_t> position)
{
    auto historyAdapter = std::make_unique<CCommandSink>(m_history);
    std::shared_ptr<IParagraph> paragrephPtr = std::make_shared<CParagraph>(move(historyAdapter), text);
    CDocumentItem item(paragrephPtr);
    m_history.AddAndExecuteCommand(std::make_unique<CInsertItemCommand>(m_items, item, position));
    return paragrephPtr;
}

std::shared_ptr<IImage> CDocument::InsertImage(const Path& path, int width, int height, optional<size_t> position)
{
    auto historyAdapter = std::make_unique<CCommandSink>(m_history);
    std::shared_ptr<IImage> imagePtr = std::make_shared<CImage>(move(historyAdapter), path, width, height);
    CDocumentItem item(imagePtr);
    m_history.AddAndExecuteCommand(std::make_unique<CInsertItemCommand>(m_items, item, position));
    return imagePtr;
}

size_t CDocument::GetItemsCount() const
{
    return m_items.size();
}

CConstDocumentItem CDocument::GetItem(size_t index) const
{
    return m_items[index];
}

CDocumentItem CDocument::GetItem(size_t index)
{
    return m_items[index];
}

void CDocument::DeleteItem(size_t index)
{
    m_history.AddAndExecuteCommand(std::make_unique<CDeleteItemCommand>(m_items, index));
}

std::string CDocument::GetTitle() const
{
    return m_title;;
}

void CDocument::SetTitle(const std::string& title)
{
    m_history.AddAndExecuteCommand(std::make_unique<CChangeStringCommand>(m_title, title));
}

bool CDocument::CanUndo() const
{
    return m_history.CanUndo();
}

void CDocument::Undo()
{
    m_history.Undo();
}

bool CDocument::CanRedo() const
{
    return m_history.CanRedo();
}

void CDocument::Redo()
{
    m_history.Redo();
}

void CDocument::Save(const Path& path) const
{
    if (!std::filesystem::exists(path))
    {
        throw std::invalid_argument("invalid path\n");
    }

    Path imagesDirectory = path / "images";
    std::filesystem::create_directory(imagesDirectory);
    std::ofstream output(path / "index.html");

    output << "<html>\n";
    output << "<head>\n";
    output << "<title>" << m_title << "</title>\n";
    output << "</head>\n";
    output << "<body>\n";
    for (auto item : m_items)
    {
        if (item.GetParagraph())
        {
            output << "<p>\n" 
                << EncodeToHtml(item.GetParagraph()->GetText()) << "\n"
                << "</p>\n";
        }
        else
        {
            auto imagePtr = item.GetImage();
            Path imageHtmlPath = imagesDirectory / imagePtr->GetPath().filename();
            std::filesystem::copy_file(item.GetImage()->GetPath(), imageHtmlPath);
            output << "<img src=\"./images/" << imagePtr->GetPath().filename().string()
                << "\"width=\"" << imagePtr->GetWidth()
                << "\"height=\"" << imagePtr->GetHeight()
                << "\"/>\n";
        }
    }
    output << "</body>\n";
    output << "</html>\n";
}

std::string CDocument::EncodeToHtml(const std::string& text) const
{
    std::string encodedText;
    for (char ch : text)
    {
        switch (ch)
        {
        case '<':
            encodedText += "&lt";
            break;
        case '>':
            encodedText += "&gt";
            break;
        case '"':
            encodedText += "&quot";
            break;
        case '\'':
            encodedText += "&apos";
            break;
        case '&':
            encodedText += "&amp";
            break;
        default:
            encodedText += ch;
            break;
        }
    }

    return encodedText;
}