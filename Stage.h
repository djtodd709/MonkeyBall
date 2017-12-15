#ifndef STAGE_H
#define STAGE_H

#include <vector>
#include "Entity.h"
#include "MathHelper.h"
using std::vector;

class Stage{
public:
	Stage();
	vector <Entity*> stageObjects;
	v3* playerStart;
	int maxTime;
	int timeLeft;
};
#endif