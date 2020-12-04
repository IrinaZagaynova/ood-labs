#pragma once
#include <iostream>
#include <boost/format.hpp>

namespace naive
{
	class CGumballMachine
	{
	public:
		enum class State
		{
			SoldOut,		// Æâà÷êà çàêîí÷èëàñü
			NoQuarter,		// Íåò ìîíåòêè
			HasQuarter,		// Åñòü ìîíåòêà
			Sold,			// Ìîíåòêà âûäàíà
		};

		CGumballMachine(unsigned gumballsÑount)
			: m_gumballsCount(gumballsÑount)
			, m_state(gumballsÑount > 0 ? State::NoQuarter : State::SoldOut)
		{
		}

		void InsertQuarter()
		{
			using namespace std;
			switch (m_state)
			{
			case State::SoldOut:
				cout << "You can't insert a quarter, the machine is sold out\n";
				break;
			case State::NoQuarter:
				cout << "You inserted a quarter\n";
				m_quartersCount++;
				m_state = State::HasQuarter;
				break;
			case State::HasQuarter:
				if (m_quartersCount < MAX_QUARTERS_COUNT)
				{
					m_quartersCount++;
					cout << "You inserted a quarter\n";
				}
				else
				{
					cout << "You can't insert more than 5 quarters\n";
				}
				break;
			case State::Sold:
				cout << "Please wait, we're already giving you a gumball\n";
				break;
			}
		}

		void EjectQuarter()
		{
			using namespace std;
			switch (m_state)
			{
			case State::HasQuarter:
				cout << m_quartersCount << " quarter" << (m_quartersCount != 1 ? "s" : "") << " returned\n";
				m_quartersCount = 0;
				m_state = State::NoQuarter;
				break;
			case State::NoQuarter:
				cout << "You haven't inserted a quarter\n";
				break;
			case State::Sold:
				cout << "Sorry you already turned the crank\n";
				break;
			case State::SoldOut:
				if (m_quartersCount > 0)
				{
					cout << m_quartersCount << " quarter" << (m_quartersCount != 1 ? "s" : "") << " returned\n";
					m_quartersCount = 0;
				}
				else
				{
					cout << "You can't eject, you haven't inserted a quarter yet\n";
				}
				break;
			}
		}

		void TurnCrank()
		{
			using namespace std;
			switch (m_state)
			{
			case State::SoldOut:
				cout << "You turned but there's no gumballs\n";
				break;
			case State::NoQuarter:
				cout << "You turned but there's no quarter\n";
				break;
			case State::HasQuarter:
				cout << "You turned...\n";		
				m_quartersCount--;
				m_state = State::Sold;
				Dispense();
				break;
			case State::Sold:
				cout << "Turning twice doesn't get you another gumball\n";
				break;
			}
		}

		std::string ToString()const
		{
			std::string state =
				(m_state == State::SoldOut) ? "sold out" :
				(m_state == State::NoQuarter) ? "waiting for quarter" :
				(m_state == State::HasQuarter) ? "waiting for turn of crank"
				: "delivering a gumball";
			auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016
Inventory: %1% gumball%2%, %3% quarter%4%
Machine is %5%
)");
			return (fmt % m_gumballsCount % (m_gumballsCount != 1 ? "s" : "") % m_quartersCount % (m_quartersCount != 1 ? "s" : "") % state).str();
		}

	private:
		void Dispense()
		{
			using namespace std;
			switch (m_state)
			{
			case State::Sold:
				cout << "A gumball comes rolling out the slot\n";
				--m_gumballsCount;
				if (m_gumballsCount == 0)
				{
					cout << "Oops, out of gumballs\n";
					m_state = State::SoldOut;
				}
				else if (m_quartersCount > 0)
				{
					m_state = State::HasQuarter;
				}
				else
				{
					m_state = State::NoQuarter;
				}
				break;
			case State::NoQuarter:
				cout << "You need to pay first\n";
				break;
			case State::SoldOut:
			case State::HasQuarter:
				cout << "No gumball dispensed\n";
				break;
			}
		}

		unsigned m_gumballsCount;	// Êîëè÷åñòâî øàðèêîâ
		unsigned m_quartersCount = 0;
		const unsigned MAX_QUARTERS_COUNT = 5;
		State m_state = State::SoldOut;
	};
}