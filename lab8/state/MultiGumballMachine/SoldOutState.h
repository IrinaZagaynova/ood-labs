#pragma once
#include "IState.h"
#include "IGumballMachine.h"
#include <iostream>

namespace with_state
{
	class CSoldOutState : public IState
	{
	public:
		CSoldOutState(IGumballMachine& gumballMachine)
			:m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			std::cout << "You can't insert a quarter, the machine is sold out\n";
		}
		void EjectQuarter() override
		{
			if (m_gumballMachine.GetQuartersCount() > 0)
			{
				std::cout << m_gumballMachine.GetQuartersCount() << " quarter" << (m_gumballMachine.GetQuartersCount() != 1 ? "s" : "") << " returned\n";
				m_gumballMachine.RemoveAllQuarters();
			}
			else
			{
				std::cout << "You can't eject, you haven't inserted a quarter yet\n";
			}
		}
		void TurnCrank() override
		{
			std::cout << "You turned but there's no gumballs\n";
		}
		void Dispense() override
		{
			std::cout << "No gumball dispensed\n";
		}
		void Refill(unsigned gumballsCount) override
		{
			m_gumballMachine.SetGumballCount(gumballsCount);
			if (m_gumballMachine.GetQuartersCount() > 0)
			{
				m_gumballMachine.SetHasQuarterState();
			}
			else
			{
				m_gumballMachine.SetNoQuarterState();
			}
		}
		std::string ToString() const override
		{
			return "sold out";
		}
	private:
		IGumballMachine& m_gumballMachine;
	};
}
