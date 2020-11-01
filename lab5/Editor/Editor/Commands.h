#pragma once
#include "AbstractCommand.h"
#include "Document.h"
#include "IParagraph.h"
#include <iostream>

class CInsertItemCommand : public CAbstractCommand
{
public:
	CInsertItemCommand(std::vector<CDocumentItem>& items, const CDocumentItem& item , optional<size_t> position)
		: m_items(items)
		, m_item(item)
		, m_position(position)
	{
	}

	void DoExecute() override
	{
		if (!m_position)
		{
			m_items.push_back(m_item);
		}
		else
		{
			if (m_position > m_items.size())
			{
				throw std::out_of_range("position number shouldn't exceed number of document items\n");
			}
			m_items.insert(m_items.begin() + *m_position, m_item);
		}
	}

	void DoUnexecute() override
	{
		if (!m_position)
		{
			m_items.pop_back();
		}
		else
		{
			m_items.erase(m_items.begin() + *m_position);
		}
	}

private:
	std::vector<CDocumentItem>& m_items;
	CDocumentItem m_item;
	optional<size_t> m_position;
};

class CDeleteItemCommand : public CAbstractCommand
{
public:
	CDeleteItemCommand(std::vector<CDocumentItem>& items, size_t index)
		: m_items(items)
		, m_index(index)
		, m_deletedItem(GetDocumentItem(index))
	{
	}

	void DoExecute() override
	{
		m_items.erase(m_items.begin() + *m_index);
	}

	void DoUnexecute() override
	{
		m_items.insert(m_items.begin() + *m_index, m_deletedItem);
	}

private:
	CDocumentItem GetDocumentItem(size_t index)
	{
		if (index >= m_items.size())
		{
			throw std::invalid_argument("position number shouldn't exceed number of document items\n");
		}
		return m_items[index];
	}

	std::vector<CDocumentItem>& m_items;
	CDocumentItem m_deletedItem;
	optional<size_t> m_index;
};

class CChangeStringCommand : public CAbstractCommand
{
public:
	CChangeStringCommand(std::string& target, std::string const& newValue)
		: m_target(target)
		, m_newValue(newValue)
	{
	}

protected:
	void DoExecute() override
	{
		m_newValue.swap(m_target);
	}
	void DoUnexecute() override
	{
		m_newValue.swap(m_target);
	}

private:
	std::string m_newValue;
	std::string& m_target;
};

class CResizeImageCommand : public CAbstractCommand
{
public:
	CResizeImageCommand(int& width, int& height, int newWidth, int newHeight)
		: m_width(width)
		, m_height(height)
		, m_newWidth(newWidth)
		, m_newHeight(newHeight)
	{
	}

protected:
	void DoExecute() override
	{
		std::swap(m_width, m_newWidth);
		std::swap(m_height, m_newHeight);
	}
	void DoUnexecute() override
	{
		std::swap(m_width, m_newWidth);
		std::swap(m_height, m_newHeight);
	}

private:
	int m_newWidth, m_newHeight;
	int& m_width, & m_height;
};
