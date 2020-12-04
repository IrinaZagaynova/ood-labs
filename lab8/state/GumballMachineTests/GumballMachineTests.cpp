#include "stdafx.h"
#include "../state/GumballMachine.h"
#include <iostream>

struct RedirectCout
{
	RedirectCout(std::streambuf* new_buffer)
		: old(std::cout.rdbuf(new_buffer))
	{
	}

	~RedirectCout()
	{
		//restore cout's original streambuf		
		std::cout.rdbuf(old);
	}

private:
	std::streambuf* old;
};

std::string GetExpectedMachineStateStr(const std::string& expectedState, unsigned count)
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%
Machine is %3%
)");
	return (fmt % count % (count != 1 ? "s" : "") % expectedState).str();
}

struct GumballMachineFixture
{
	CGumballMachine gumballMachine;
	GumballMachineFixture()
		: gumballMachine(0)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(gumball_machine_in_sold_out_state, GumballMachineFixture)
	
BOOST_AUTO_TEST_CASE(InsertQuarter_shouldnt_change_machine_state)
{
	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.InsertQuarter();

	BOOST_CHECK_EQUAL(ss.str(), "You can't insert a quarter, the machine is sold out\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("sold out", 0));
}

BOOST_AUTO_TEST_CASE(EjectQuarter_shouldnt_change_machine_state)
{
	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.EjectQuarter();

	BOOST_CHECK_EQUAL(ss.str(), "You can't eject, you haven't inserted a quarter yet\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("sold out", 0));
}

BOOST_AUTO_TEST_CASE(TurnCrank_shouldnt_change_machine_state)
{
	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.TurnCrank();

	BOOST_CHECK_EQUAL(ss.str(), "You turned but there's no gumballs\nNo gumball dispensed\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("sold out", 0));
}

BOOST_AUTO_TEST_SUITE_END()

struct gumball_machine_in_no_quarter_state_
{
	CGumballMachine gumballMachine;
	gumball_machine_in_no_quarter_state_()
		: gumballMachine(2)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(gumball_machine_in_no_quarter_state, gumball_machine_in_no_quarter_state_)

BOOST_AUTO_TEST_CASE(InsertQuarter_should_insert_a_quater_and_set_has_quarter_state)
{
	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.InsertQuarter();

	BOOST_CHECK_EQUAL(ss.str(), "You inserted a quarter\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("waiting for turn of crank", 2));
}

BOOST_AUTO_TEST_CASE(EjectQuarter_shouldnt_change_machine_state)
{
	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.EjectQuarter();

	BOOST_CHECK_EQUAL(ss.str(), "You haven't inserted a quarter\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("waiting for quarter", 2));
}

BOOST_AUTO_TEST_CASE(TurnCrank_shouldnt_change_machine_state)
{
	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.TurnCrank();

	BOOST_CHECK_EQUAL(ss.str(), "You turned but there's no quarter\nYou need to pay first\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("waiting for quarter", 2));
}

BOOST_AUTO_TEST_SUITE_END()

struct gumball_machine_in_has_quarter_state_ : gumball_machine_in_no_quarter_state_
{
	gumball_machine_in_has_quarter_state_()
	{
		gumballMachine.InsertQuarter();
	}	
};

BOOST_FIXTURE_TEST_SUITE(gumball_machine_in_has_quarter_state, gumball_machine_in_has_quarter_state_)

BOOST_AUTO_TEST_CASE(InsertQuarter_shouldnt_change_machine_state)
{
	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.InsertQuarter();

	BOOST_CHECK_EQUAL(ss.str(), "You can't insert another quarter\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("waiting for turn of crank", 2));
}

BOOST_AUTO_TEST_CASE(EjectQuarter_should_return_quater_and_set_no_quarter_state)
{
	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.EjectQuarter();

	BOOST_CHECK_EQUAL(ss.str(), "Quarter returned\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("waiting for quarter", 2));
}

BOOST_AUTO_TEST_CASE(TurnCrank_should_return_gumball_and_set_no_quarter_state_if_there_are_not_0_gumballs)
{
	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.TurnCrank();

	BOOST_CHECK_EQUAL(ss.str(), "You turned...\nA gumball comes rolling out the slot...\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("waiting for quarter", 1));
}

BOOST_AUTO_TEST_CASE(TurnCrank_should_return_gumball_and_set_sold_out_state_if_there_are_0_gumballs)
{
	gumballMachine.TurnCrank();
	gumballMachine.InsertQuarter();

	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.TurnCrank();

	BOOST_CHECK_EQUAL(ss.str(), "You turned...\nA gumball comes rolling out the slot...\nOops, out of gumballs\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("sold out", 0));
}

BOOST_AUTO_TEST_SUITE_END()