#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"

//Base class for all game objects - each should include a model and  collision geometry.
class Player : public Entity{
public:
	Player(const char * pathToAssetFolder);
	v3* rootPos;
};

#endif
