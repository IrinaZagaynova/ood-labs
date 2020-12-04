#pragma once
#include "IState.h"
#include "IGumballMachine.h"
#include <iostream>

namespace with_state
{
	class CNoQuarterState : public IState
	{
	public:
		CNoQuarterState(IGumballMachine& gumballMachine)
			: m_gumballMachine(gumballMachine)
		{}

		void InsertQuarter() override
		{
			std::cout << "You inserted a quarter\n";
			m_gumballMachine.AddQuarter();
			m_gumballMachine.SetHasQuarterState();
		}
		void EjectQuarter() override
		{
			std::cout << "You haven't inserted a quarter\n";
		}
		void TurnCrank() override
		{
			std::cout << "You turned but there's no quarter\n";
		}
		void Dispense() override
		{
			std::cout << "You need to pay first\n";
		}
		void Refill(unsigned gumballsCount) override
		{
			m_gumballMachine.SetGumballCount(gumballsCount);
		}
		std::string ToString() const override
		{
			return "waiting for quarter";
		}
	private:
		IGumballMachine& m_gumballMachine;
	};
}