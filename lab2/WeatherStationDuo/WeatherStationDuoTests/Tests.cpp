#include "../WeatherStationDuo/WeatherData.h"
#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../WeatherStationDuo/WeatherInfo.h"
#include <string>

class CTestTwoStationsObserver : public IObserver<SWeatherInfo>
{
public:
	CTestTwoStationsObserver(std::string& str)
		: m_str(str)
	{
	}
private:
	void Update(SWeatherInfo const& data) override
	{
		if (data.type == StationType::In)
		{
			m_str.append("indoor");
		}
		else if (data.type == StationType::Out)
		{
			m_str.append("outside");
		}
	}

	std::string& m_str;
};

TEST_CASE("Observers must receive data from indoor station")
{
	CWeatherData wd1(StationType::In);
	std::string str;

	CTestTwoStationsObserver obs(str);

	wd1.RegisterObserver(obs, 1);
	wd1.SetMeasurements(1, 1, 1);

	CHECK(str == "indoor");
}

TEST_CASE("Observers must receive data from outside stations")
{
	CWeatherData wd2(StationType::Out);
	std::string str;

	CTestTwoStationsObserver obs(str);

	wd2.RegisterObserver(obs, 1);
	wd2.SetMeasurements(1, 1, 1);

	CHECK(str == "outside");
}