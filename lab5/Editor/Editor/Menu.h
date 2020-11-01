#pragma once
#include "ICommand.h"
#include <string>
#include <vector>
#include <functional>
#include <iostream>

class CMenu
{
public:
	typedef std::function<void(std::istream& args)> Command;

	CMenu(std::istream& istrm = std::cin, std::ostream& ostrm = std::cout);

	void AddItem(const std::string& shortcut, const std::string& description, const Command& command);

	void Run();

	void ShowInstructions()const;

	void Exit();

private:
	bool ExecuteCommand(const std::string& command);

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