#include "../WeatherStation/WeatherData.h"
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include <vector>

class CTestSelfRemoveObserver : public IObserver<SWeatherInfo>
{
public:
	CTestSelfRemoveObserver(CObservable<SWeatherInfo>& data)
		: m_data(data)
	{
	}

	void Update(const SWeatherInfo& data) override
	{
		m_data.RemoveObserver(*this);
	}

private:
	CObservable<SWeatherInfo>& m_data;
};

class CTestPriorityObserver : public IObserver<SWeatherInfo>
{
public:
	CTestPriorityObserver(std::vector<size_t>& order, size_t number)
		: m_order(order), m_numper(number)
	{
	}

	void Update(SWeatherInfo const& data) override
	{
		m_order.push_back(m_numper);
	}
private:
	std::vector<size_t>& m_order;
	size_t m_numper;
};

TEST_CASE("The observer must be removed correctly")
{
	CWeatherData data;
	CTestSelfRemoveObserver obs(data);
	data.RegisterObserver(obs, 1);
	CHECK_NOTHROW(data.SetMeasurements(1, 1, 1));
}

TEST_CASE("Observers with higher priority should receive alerts earlier")
{
	std::vector<size_t> order;
	CWeatherData wd;
	CTestPriorityObserver obs1(order, 1);
	CTestPriorityObserver obs2(order, 2);
	CTestPriorityObserver obs3(order, 3);
	CTestPriorityObserver obs4(order, 4);
	CTestPriorityObserver obs5(order, 5);

	wd.RegisterObserver(obs1, 2);
	wd.RegisterObserver(obs2, 7);
	wd.RegisterObserver(obs3, 4);
	wd.RegisterObserver(obs4, 1);
	wd.RegisterObserver(obs5, 4);

	wd.SetMeasurements(1, 1, 1);

	std::vector<size_t> expected = { 2, 3, 5, 1, 4 };
	CHECK(order == expected);
}
