#pragma once
#include <GLFW/glfw3.h>
#include <map>
#include <string>

enum class Color
{
	Green,
	Red,
	Blue,
	Yellow,
	Pink,
	Black
};

const std::map<std::string, Color> COLORS_NAMES
{
	{"green", Color::Green},
	{"red", Color::Red},
	{"blue", Color::Blue},
	{"yellow",  Color::Yellow},
	{"pink", Color::Pink},
	{"black", Color::Black}
};