#include "RandomHelper.h"

#include <cassert>
#include <chrono>
#include <random>

using namespace std;

int RandomHelper::RandomRange(int minValue, int maxValue)
{
	if (maxValue == 0)
	{
		assert(false);
		return 0;
	}

	auto current = chrono::system_clock::now();
	auto duration = current.time_since_epoch();
	auto millis = chrono::duration_cast<chrono::milliseconds>(duration).count();
	mt19937_64 genMT(millis);

	int range = maxValue - minValue;
	double ratio = (double)((int)(genMT() % 100)) / 100.0;
	return minValue + (int)((double)range * ratio);
}