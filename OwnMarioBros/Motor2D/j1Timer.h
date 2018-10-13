#ifndef _j1TIMER_H_
#define _j1TIMER_H_

#include "p2Defs.h"

class j1Timer
{
public:

	// Constructor
	j1Timer();

	void Start();
	uint Read() const;
	float ReadSec() const;

private:
	uint	started_at;
};

#endif //_j1TIMERR_H_