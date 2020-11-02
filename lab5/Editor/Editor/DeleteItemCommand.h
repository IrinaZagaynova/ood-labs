#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"
#include <boost/optional.hpp>

using boost::optional;
using boost::none;

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