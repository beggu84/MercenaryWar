#pragma once

#include <Global.h>

#include <winsock2.h>

class UniqueIdGenerator
{
private:
	const int NODE_SHIFT = 10;
	const int SEQ_SHIFT = 12;

	const short MAX_NODE = 1024;
	const short MAX_SEQUENCE = 4096;

	const int DEFAULT_NODE_ID = 1;

	enum State { NOT_INIT, READY };

private:
	CRITICAL_SECTION _cs;

	short _sequence{ 0 };
	int64_t _referenceTime{ 0LL };
	int _node{ 0 };
	State _state{ State::NOT_INIT };

public:
	UniqueIdGenerator();
	~UniqueIdGenerator();

	void Setup();
	void Cleanup();

	int64_t Next();
};