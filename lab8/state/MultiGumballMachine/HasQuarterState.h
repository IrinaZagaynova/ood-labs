#pragma once
#include "IState.h"
#include "IGumballMachine.h"
#include <iostream>

namespace with_state
{
	class CHasQuarterState : public IState
	{
	public:
		CHasQuarterState(IGumballMachine& gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			if (m_gumballMachine.GetQuartersCount() < MAX_QUARTERS_COUNT)
			{
				m_gumballMachine.AddQuarter();
				std::cout << "You inserted a quarter\n";
			}
			else
			{
				std::cout << "You can't insert more than 5 quarters\n";
			}
		}
		void EjectQuarter() override
		{
			std::cout << m_gumballMachine.GetQuartersCount() << " quarter" << (m_gumballMachine.GetQuartersCount() != 1 ? "s" : "") << " returned\n";
			m_gumballMachine.RemoveAllQuarters();
			m_gumballMachine.SetNoQuarterState();
		}
		void TurnCrank() override
		{
			std::cout << "You turned...\n";
			m_gumballMachine.RemoveQuarter();
			m_gumballMachine.SetSoldState();
		}
		void Dispense() override
		{
			std::cout << "No gumball dispensed\n";
		}
		void Refill(unsigned gumballsCount) override
		{
			m_gumballMachine.SetGumballCount(gumballsCount);
		}
		std::string ToString() const override
		{
			return "waiting for turn of crank";
		}
	private:
		const unsigned MAX_QUARTERS_COUNT = 5;
		IGumballMachine& m_gumballMachine;
	};
}