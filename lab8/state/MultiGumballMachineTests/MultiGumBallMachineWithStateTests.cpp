#include "stdafx.h"
#include "../MultiGumballMachine/GumballMachine.h"
#include "RedirectCout.h"

std::string GetExpectedMachineStateStr(const std::string& expectedState, unsigned gumballsCount, unsigned quartersCount)
{
	auto fmt = boost::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: %1% gumball%2%, %3% quarter%4%
Machine is %5%
)");;
	return (fmt % gumballsCount % (gumballsCount != 1 ? "s" : "") % quartersCount % (quartersCount != 1 ? "s" : "") % expectedState).str();
}

struct GumballMachineFixture
{
	with_state::CGumballMachine gumballMachine;
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
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("sold out", 0, 0));
}

BOOST_AUTO_TEST_CASE(EjectQuarter_shouldnt_change_machine_state)
{
	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.EjectQuarter();

	BOOST_CHECK_EQUAL(ss.str(), "You can't eject, you haven't inserted a quarter yet\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("sold out", 0, 0));
}

BOOST_AUTO_TEST_CASE(TurnCrank_shouldnt_change_machine_state)
{
	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.TurnCrank();

	BOOST_CHECK_EQUAL(ss.str(), "You turned but there's no gumballs\nNo gumball dispensed\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("sold out", 0, 0));
}

BOOST_AUTO_TEST_CASE(Refill_should_set_no_quarter_state_and_change_qumballs_count)
{
	gumballMachine.Refill(10);
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("waiting for quarter", 10, 0));
}

BOOST_AUTO_TEST_SUITE_END()

struct gumball_machine_in_no_quarter_state_
{
	with_state::CGumballMachine gumballMachine;
	gumball_machine_in_no_quarter_state_()
		: gumballMachine(3)
	{
	}
};

BOOST_FIXTURE_TEST_SUITE(gumball_machine_in_no_quarter_state, gumball_machine_in_no_quarter_state_)

BOOST_AUTO_TEST_CASE(InsertQuarter_should_insert_a_quater)
{
	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.InsertQuarter();

	BOOST_CHECK_EQUAL(ss.str(), "You inserted a quarter\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("waiting for turn of crank", 3, 1));
}

BOOST_AUTO_TEST_CASE(EjectQuarter_shouldnt_change_machine_state)
{
	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.EjectQuarter();

	BOOST_CHECK_EQUAL(ss.str(), "You haven't inserted a quarter\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("waiting for quarter", 3, 0));
}

BOOST_AUTO_TEST_CASE(TurnCrank_shouldnt_change_machine_state)
{
	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.TurnCrank();

	BOOST_CHECK_EQUAL(ss.str(), "You turned but there's no quarter\nYou need to pay first\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("waiting for quarter", 3, 0));
}

BOOST_AUTO_TEST_CASE(Refill_should_change_qumballs_count)
{
	gumballMachine.Refill(10);
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("waiting for quarter", 10, 0));
}

BOOST_AUTO_TEST_SUITE_END()

struct when_gumball_machine_has_3_quarters_ : gumball_machine_in_no_quarter_state_
{
	when_gumball_machine_has_3_quarters_()
	{
		gumballMachine.InsertQuarter();
		gumballMachine.InsertQuarter();
		gumballMachine.InsertQuarter();
	}
};

BOOST_FIXTURE_TEST_SUITE(when_gumball_machine_has_3_quarters, when_gumball_machine_has_3_quarters_)

BOOST_AUTO_TEST_CASE(InsertQuarter_should_insert_quarter_if_there_are_less_than_5_quarters)
{
	gumballMachine.InsertQuarter();

	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.InsertQuarter();

	BOOST_CHECK_EQUAL(ss.str(), "You inserted a quarter\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("waiting for turn of crank", 3, 5));
}

BOOST_AUTO_TEST_CASE(EjectQuarter_should_return_all_quaters)
{
	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.EjectQuarter();

	BOOST_CHECK_EQUAL(ss.str(), "3 quarters returned\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("waiting for quarter", 3, 0));
}

BOOST_AUTO_TEST_CASE(TurnCrank_should_return_gumball)
{
	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.TurnCrank();

	BOOST_CHECK_EQUAL(ss.str(), "You turned...\nA gumball comes rolling out the slot...\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("waiting for turn of crank", 2, 2));
}

BOOST_AUTO_TEST_CASE(TurnCrank_should_return_gumball_and_set_sold_out_state_if_there_are_0_gumballs)
{
	gumballMachine.TurnCrank();
	gumballMachine.TurnCrank();

	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.TurnCrank();

	BOOST_CHECK_EQUAL(ss.str(), "You turned...\nA gumball comes rolling out the slot...\nOops, out of gumballs\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("sold out", 0, 0));
}

BOOST_AUTO_TEST_CASE(Refill_should_change_qumballs_count)
{
	gumballMachine.Refill(10);
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("waiting for turn of crank", 10, 3));
}

BOOST_AUTO_TEST_SUITE_END()

struct when_gumball_machine_has_5_quarters_ : gumball_machine_in_no_quarter_state_
{
	when_gumball_machine_has_5_quarters_()
	{
		gumballMachine.InsertQuarter();
		gumballMachine.InsertQuarter();
		gumballMachine.InsertQuarter();
		gumballMachine.InsertQuarter();
		gumballMachine.InsertQuarter();
	}
};

BOOST_FIXTURE_TEST_SUITE(when_gumball_machine_has_5_quarters, when_gumball_machine_has_5_quarters_)

BOOST_AUTO_TEST_CASE(cant_insert_more_than_5_quarters)
{
	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.InsertQuarter();

	BOOST_CHECK_EQUAL(ss.str(), "You can't insert more than 5 quarters\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("waiting for turn of crank", 3, 5));
}

BOOST_AUTO_TEST_CASE(can_return_the_remaining_quarters_after_all_the_gumballs_have_been_issued)
{
	gumballMachine.TurnCrank();
	gumballMachine.TurnCrank();
	gumballMachine.TurnCrank();

	std::ostringstream ss;
	RedirectCout buff(ss.rdbuf());

	gumballMachine.EjectQuarter();

	BOOST_CHECK_EQUAL(ss.str(), "2 quarters returned\n");
	BOOST_CHECK_EQUAL(gumballMachine.ToString(), GetExpectedMachineStateStr("sold out", 0, 0));
}

BOOST_AUTO_TEST_SUITE_END()