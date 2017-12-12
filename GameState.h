#ifndef __GAMESTATE_H__
#define __GAMESTATE_H__

#include <vector>
#include "Entity.h"

using std::vector;

enum CurrentState
{
	MAIN_MENU,
	IN_GAME,
	GAME_PAUSED
};

//Base class for all game objects - each should include a model and  collision geometry.
class GameState{
public:
	GameState();
	tick(float dt);
	setState(CurrentState newState);
private:
vector <Entity> gameObjects;
//TODO: Create a UIelement class: Should check against mouse input to see if we're hovering over the screen-space co-ords it occupies, and  execute logic on click
//vector <UIElement> uiElements;
CurrentState state;

//Maybe include a class to pass in input since previous tick for processing?
};

#endif