#pragma once
#include "Menu.h"
#include "GumballMachine.h"
#include <iostream>
#include <sstream>
#include <memory>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace std::placeholders;
using namespace with_state;

class CMenuHandler
{
public:
	CMenuHandler(std::istream& istrm = std::cin, std::ostream& ostrm = std::cout)
		: m_istrm(istrm)
		, m_ostrm(ostrm)
		, m_menu(istrm, ostrm)
		, m_gumballMachine(make_unique<CGumballMachine>(0))
	{
		m_menu.AddItem("help", "Help", [this](istream&) { m_menu.ShowInstructions(); });
		m_menu.AddItem("exit", "Exit", [this](istream&) { m_menu.Exit(); });
		AddMenuItem("insertQuarter", "Insert quarter", &CMenuHandler::InsertQuarter);
		AddMenuItem("ejectQuarter", "Eject all quarters", &CMenuHandler::EjectQuarter);
		AddMenuItem("turnCrank", "Gives out gumball if the machine is filled with gumballs and a quarter is inserted", &CMenuHandler::TurnCrank);
		AddMenuItem("refill", "Refills the machine with gumballs. Args: <gumballs count>", &CMenuHandler::Refill);
		AddMenuItem("toString", "Displays machine info", &CMenuHandler::ToString);
	}

	void Start()
	{
		m_menu.Run();
	}

private:
	typedef void (CMenuHandler::* MenuHandler)(istream& in);

	void AddMenuItem(const string& shortcut, const string& description, MenuHandler handler)
	{
		m_menu.AddItem(shortcut, description, bind(handler, this, _1));
	}

	void InsertQuarter(istream& in)
	{
		m_gumballMachine->InsertQuarter();
	}

	void EjectQuarter(istream& in)
	{
		m_gumballMachine->EjectQuarter();
	}

	void TurnCrank(istream& in)
	{
		m_gumballMachine->TurnCrank();
	}

	void Refill(istream& in)
	{
		unsigned gumballsCount;
		in >> gumballsCount;
		m_gumballMachine->Refill(gumballsCount);
	}

	void ToString(istream& in)
	{
		m_ostrm << m_gumballMachine->ToString();
	}

	CMenu m_menu;
	std::istream& m_istrm;
	std::ostream& m_ostrm;
	unique_ptr<CGumballMachine> m_gumballMachine;
};