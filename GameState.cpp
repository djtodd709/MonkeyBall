#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include "GameState.h"

GameState::GameState()
{
	//TODO: Change this to MAIN_MENU once Vlad does his thing
	//state = MAIN_MENU;
	state = IN_GAME;
}

void GameState::tick(float dt, int mx, int my, bool* mButtons, bool* keyButtons)
{
	//TODO: Implement game loop for each state
	if (state == MAIN_MENU)
	{
		//Display and get input w/ ui Elements
		//uiElements;
	}
	else if (state == IN_GAME)
	{
		//Display and get input w/ gameObjects, display UI.
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i]->onTick();
			for (int o = 0; o < gameObjects.size(); o++) //Iterate over every object in the scene to check if they collide
			{
				if (i != o) //Cancel if we would be checking a self-collision
				{
					checkCollision(gameObjects[i], gameObjects[o]);
				}
			}
		}

		/*
		for (int i = 0; i < uiElements.size(); i++)
		{
			uiElements[i]->onTick();
		}*/
	}
	else if (state == GAME_PAUSED)
	{
		//Display gameObjects, display and get input w/ UI.
		//gameObjects;
		//uiElements;
	}
	cam->update();

	prevX = mx;
	prevY = my;
	prevMButtons = mButtons;
	keysPressed = keyButtons;
}

void GameState::checkCollision(Entity* a, Entity* b)
{
	//TODO: IMPLEMENT COLLISION CHECKING
	//In case of collisions, on each entity call onCollision(Entity* o, v3 normal) with the other entity and collision surface normal
}

void GameState::setState(CurrentState newState)
{

}

void GameState::resetStage()
{
	//TODO: Switch to this once we have stage loading properly implemented
	/*
	Stage* currentStage = &stages[currentStageIndex];
	for (int i = 0; i < currentStage->stageObjects.size(); i++)
	{
		currentStage->stageObjects[i]->reset();
	}
	*/

	//HACK: resets ALL objects
	for (int i = 0; i < gameObjects.size(); i++)
	{
		gameObjects[i]->reset();
	}
}