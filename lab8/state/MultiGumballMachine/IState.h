#pragma once
#include <string>

namespace with_state
{
	struct IState
	{
		virtual void InsertQuarter() = 0;
		virtual void EjectQuarter() = 0;
		virtual void TurnCrank() = 0;
		virtual void Dispense() = 0;
		virtual void Refill(unsigned gumballsCount) = 0;
		virtual std::string ToString()const = 0;
		virtual ~IState() = default;
	};
}