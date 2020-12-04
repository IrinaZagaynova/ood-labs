#pragma once
#include <string>
#include <vector>
#include <functional>
#include <iostream>
#include <sstream>

class CMenu
{
public:
	typedef std::function<void(std::istream& args)> Command;

	CMenu(std::istream& istrm = std::cin, std::ostream& ostrm = std::cout)
		: m_istrm(istrm)
		, m_ostrm(ostrm)
	{
	}

	void AddItem(const std::string& shortcut, const std::string& description, const Command& command)
	{
		m_items.emplace_back(shortcut, description, command);
	}

	void Run()
	{
		ShowInstructions();

		std::string command;
		while ((m_ostrm << ">")
			&& getline(m_istrm, command)
			&& ExecuteCommand(command))
		{
		}
	}

	void ShowInstructions()const
	{

		m_ostrm << "Commands list:\n";
		for (auto& item : m_items)
		{
			m_ostrm << "  " << item.shortcut << ": " << item.description << "\n";
		}
	}

	void Exit()
	{
		m_exit = true;
	}

private:
	bool ExecuteCommand(const std::string& command)
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

	struct Item
	{
		Item(const std::string& shortcut, const std::string& description, const Command& command)
			: shortcut(shortcut)
			, description(description)
			, command(command)
		{}

		std::string shortcut;
		std::string description;
		Command command;
	};

	std::istream& m_istrm;
	std::ostream& m_ostrm;
	std::vector<Item> m_items;
	bool m_exit = false;
};