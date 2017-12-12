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
	state = CurrentState.MAIN_MENU;
}

GameState::tick(float dt)
{
	//TODO: Implement game loop for each state
	if (state == CurrentState.MAIN_MENU)
	{
		//Display and get input w/ ui Elements
		//uiElements;
	}
	else if (state == CurrentState.IN_GAME)
	{
		//Display and get input w/ gameObjects, display UI.
		//gameObjects;
		//uiElements;
	}
	else if (state == CurrentState.GAME_PAUSED)
	{
		//Display gameObjects, display and get input w/ UI.
		//gameObjects;
		//uiElements;
	}
}

GameState::setState(CurrentState newState)
{

}