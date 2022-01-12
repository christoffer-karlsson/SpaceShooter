#pragma once

#include <random>

inline double RandomDouble(double From, double To)
{
	return From + (rand() / (RAND_MAX / (To - From)));
}

inline int RandomInt(int From, int To)
{
	return From + (rand() / (RAND_MAX / (To - From)));
}