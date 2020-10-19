#pragma once
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>

inline std::vector<uint8_t> GenerateEncryptTable(size_t key)
{
	std::vector<uint8_t> table(256);
	std::iota(table.begin(), table.end(), 0);
	std::shuffle(table.begin(), table.end(), std::mt19937((unsigned int)key));
	return table;
}