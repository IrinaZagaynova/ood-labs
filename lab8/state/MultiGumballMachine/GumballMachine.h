#pragma once
#include "IGumballMachine.h"
#include "SoldState.h"
#include "SoldOutState.h"
#include "NoQuarterState.h"
#include "HasQuarterState.h"
#include <string>
#include <boost/format.hpp>

namespace with_state
{
	class CGumballMachine : private IGumballMachine
	{
	public:
		CGumballMachine(unsigned numBalls)
			: m_soldState(*this)
			, m_soldOutState(*this)
			, m_noQuarterState(*this)
			, m_hasQuarterState(*this)
			, m_state(&m_soldOutState)
			, m_gumballsCount(numBalls)
		{
			if (m_gumballsCount > 0)
			{
				m_state = &m_noQuarterState;
			}
		}
		void EjectQuarter()
		{
			m_state->EjectQuarter();
		}
		void InsertQuarter()
		{
			m_state->InsertQuarter();
		}
		void TurnCrank()
		{
			m_state->TurnCrank();
			m_state->Dispense();
		}
		void Refill(unsigned gumballCount)
		{
			m_state->Refill(gumballCount);
		}
		std::string ToString()const
		{
			auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%, %3% quarter%4%
Machine is %5%
)");
			return (fmt % m_gumballsCount % (m_gumballsCount != 1 ? "s" : "") % m_quartersCount % (m_quartersCount != 1 ? "s" : "") % m_state->ToString()).str();
		}
	private:
		unsigned GetBallCount() const override
		{
			return m_gumballsCount;
		}
		unsigned GetQuartersCount() const override
		{
			return m_quartersCount;
		}
		void AddQuarter() override
		{
			m_quartersCount++;
		}
		void RemoveQuarter() override
		{
			if (m_quartersCount != 0)
			{
				m_quartersCount--;
			}
		}
		void RemoveAllQuarters() override
		{
			m_quartersCount =0;
		}
		virtual void ReleaseBall() override
		{
			if (m_gumballsCount != 0)
			{
				std::cout << "A gumball comes rolling out the slot...\n";
				--m_gumballsCount;
			}
		}
		void SetGumballCount(unsigned gumballsCount) override
		{
			m_gumballsCount = gumballsCount;
		}
		void SetSoldOutState() override
		{
			m_state = &m_soldOutState;
		}
		void SetNoQuarterState() override
		{
			m_state = &m_noQuarterState;
		}
		void SetSoldState() override
		{
			m_state = &m_soldState;
		}
		void SetHasQuarterState() override
		{
			m_state = &m_hasQuarterState;
		}
	private:
		unsigned m_gumballsCount = 0;
		unsigned m_quartersCount = 0;
		CSoldState m_soldState;
		CSoldOutState m_soldOutState;
		CNoQuarterState m_noQuarterState;
		CHasQuarterState m_hasQuarterState;
		IState* m_state;
	};

} //namespace with_state