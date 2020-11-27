#include "stdafx.h"
#include "UniqueIdGenerator.h"

#include <winsock2.h>
#include <chrono>
#include <exception>

using namespace std;
using namespace std::chrono;

UniqueIdGenerator::UniqueIdGenerator()
{
}

UniqueIdGenerator::~UniqueIdGenerator()
{
}

void UniqueIdGenerator::Setup()
{
	// get node id from central server
	_node = DEFAULT_NODE_ID;
	_state = State::READY;

	if (_node < 0 || _node > MAX_NODE) 
	{
		//throw std::exception(boost::str(boost::format("node must be between %s and %s") % 0 % MAX_NODE).c_str());
	}

	::InitializeCriticalSection(&_cs);
}

void UniqueIdGenerator::Cleanup()
{
	::DeleteCriticalSection(&_cs);
}

int64_t UniqueIdGenerator::Next()
{
	if (_state != State::READY) 
	{
		throw exception("Generator not initialized.");
	}

	// Constraint : NTP로 서버들의 시간 동기화 필요
	auto ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
	int64_t currentTime = ms.count();
	int64_t counter;

	::EnterCriticalSection(&_cs);

	if (currentTime < _referenceTime) 
	{
		//throw exception(boost::str(boost::format("Last referenceTime %s is after reference time %s") % _referenceTime % currentTime).c_str());
	}
	else if (currentTime > _referenceTime)
	{
		_sequence = 0;
	}
	else 
	{
		if (_sequence < UniqueIdGenerator::MAX_SEQUENCE)
		{
			_sequence++;
		}
		else 
		{
			//throw exception(boost::str(boost::format("Sequence exhausted at %d") % _sequence).c_str());
		}
	}

	counter = _sequence;
	_referenceTime = currentTime;

	::LeaveCriticalSection(&_cs);

	return currentTime << NODE_SHIFT << SEQ_SHIFT | _node << SEQ_SHIFT | counter;
}