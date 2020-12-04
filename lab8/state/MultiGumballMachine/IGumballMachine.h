#pragma once

namespace with_state
{
	struct IGumballMachine
	{
		virtual void ReleaseBall() = 0;
		virtual unsigned GetBallCount()const = 0;
		virtual unsigned GetQuartersCount()const = 0;

		virtual void AddQuarter() = 0;
		virtual void RemoveQuarter() = 0;
		virtual void RemoveAllQuarters() = 0;

		virtual void SetGumballCount(unsigned gumballsCount) = 0;

		virtual void SetSoldOutState() = 0;
		virtual void SetNoQuarterState() = 0;
		virtual void SetSoldState() = 0;
		virtual void SetHasQuarterState() = 0;

		virtual ~IGumballMachine() = default;
	};
}