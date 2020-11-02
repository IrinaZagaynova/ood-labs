#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"
#include <boost/optional.hpp>

using boost::optional;
using boost::none;

class CInsertItemCommand : public CAbstractCommand
{
public:
	CInsertItemCommand(std::vector<CDocumentItem>& items, const CDocumentItem& item, optional<size_t> position)
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