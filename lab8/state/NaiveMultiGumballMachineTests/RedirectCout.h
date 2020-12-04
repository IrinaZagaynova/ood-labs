#pragma once
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