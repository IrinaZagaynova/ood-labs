#include "Menu.h"
#include <sstream>

CMenu::CMenu(std::istream& istrm, std::ostream& ostrm)
	: m_istrm(istrm)
	, m_ostrm(ostrm)
{
}

void CMenu::AddItem(const std::string& shortcut, const std::string& description, const Command& command)
{
	m_items.emplace_back(shortcut , description, command);
}

void CMenu::Run()
{
	ShowInstructions();

	std::string command;
	while ((m_ostrm << ">")
		&& getline(m_istrm, command)
		&& ExecuteCommand(command))
	{
	}
}

void CMenu::ShowInstructions() const
{
	m_ostrm << "Commands list:\n";
	for (auto& item : m_items)
	{
		m_ostrm << "  " << item.shortcut << ": " << item.description << "\n";
	}
}

void CMenu::Exit()
{
	m_exit = true;
}

bool CMenu::ExecuteCommand(const std::string& command)
{
	std::istringstream iss(command);
	std::string name;
	iss >> name;

	m_exit = false;
	auto it = std::find_if(m_items.begin(), m_items.end(), [&](const Item& item) {
		return item.shortcut == name;
		});
	if (it != m_items.end())
	{
		it->command(iss);
	}
	else
	{
		m_ostrm << "Unknown command\n";
	}
	return !m_exit;
}
