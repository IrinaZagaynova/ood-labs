#pragma once

enum class StationType
{
	In,
	Out
};

struct SWeatherInfo
{
	double temperature = 0;
	double humidity = 0;
	double pressure = 0;
	StationType type;
};
