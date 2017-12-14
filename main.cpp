#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

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
#include "Player.h"
#include "Camera.h"

#include "Mesh.h"
Mesh *aiaiHead;
Mesh *aiaiBody;
Mesh *aiaiArm;
Mesh *aiaiBall;
Mesh *stage;

#define X 0
#define Y 1
#define Z 2

//DEBUG
bool debugMode = true;

//STRING DUMP
char* aiaiHeadObjPath = (char*)"Assets/Models/Head.obj";
char* aiaiHeadUVPath = (char*)"Assets/Textures/HeadUV.ppm";
char* aiaiBodyObjPath = (char*)"Assets/Models/Body.obj";
char* aiaiBodyUVPath = (char*)"Assets/Textures/BodyUV.ppm";
char* aiaiArmObjPath = (char*)"Assets/Models/Arm.obj";
char* aiaiArmUVPath = (char*)"Assets/Textures/ArmUV.ppm";
char* aiaiBallObjPath = (char*)"Assets/Models/BallHalf.obj";
char* aiaiBallUVPath = (char*)""; //Ball has no UV right now

char* stageUVPath = (char*)"Assets/Textures/Stage.ppm";
char* stagePath0 = (char*)"Assets/Models/Stages/Stage0.obj";

GameState* game;
//Input values
int mx, my;
bool* mButtonsPressed;
bool* keysPressed;

//Light 0 properties
float l0pos[4] = {1.0f,10.0f,1.0f,1};
float l0dif[4] = {0.7f,0.7f,0.7f,1};
float l0amb[4] = {0.1f,0.1f,0.1f,1};
float l0spe[4] = {1,1,1,1};

//Material properties - stage
float s_dif[4] = {0.5f,1.0f,0.3f,1};
float s_amb[4] = {0.3f,0.7f,0.1f,1};
float s_spe[4] = {1.0f,1.0f,1.0f,1};

//Material properties - white
float m0_dif[4] = {1.0f,1.0f,1.0f,1};
float m0_amb[4] = {0.5f,0.5f,0.5f,1};
float m0_spe[4] = {1.0f,1.0f,1.0f,1};

//Material properties - white alpha
float m1_dif[4] = {1.0f,1.0f,1.0f,0.8f};
float m1_amb[4] = {0.5f,0.5f,0.5f,0.8f};
float m1_spe[4] = {1.0f,1.0f,1.0f,0.8f};

//Material properties - red alpha
float m2_dif[4] = {1.0f,0.2f,0.2f,0.7f};
float m2_amb[4] = {0.5f,0.1f,0.1f,0.7f};
float m2_spe[4] = {1.0f,1.0f,1.0f,0.7f};

float shiny = 10;


//position of camera and target. camPos is scaled to the size of the terrain
float camPos[] = {20.0f, 5.0f, 20.0f};	//where the camera is
float camTarget[] = {0,2.0f,0};

float m_temp[4] = {0,0,0,1};
float no_mat[4] = {0,0,0,1};

Camera* orbitCam;
Player* playerObj;

//Temp ground
float groundSize = 10;
float groundHeight = -5;


//initial settings for main window. Called (almost) at the begining of the program.
void init(void){
	glClearColor(0, 0, 0, 0);	//black background
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);

	//Enable lights and depth testing
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_TEXTURE_2D);

	//Implement backface culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//Apply light 0 settings
	glLightfv(GL_LIGHT0, GL_POSITION, l0pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0spe);

	//Apply material settings
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m0_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m0_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m0_spe);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

	//adjust view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 1000);

	orbitCam = new Camera();
	mButtonsPressed = new bool[3];
	keysPressed = new bool[15];
	game = new GameState();
	printf("hamn'");
	playerObj = new Player(aiaiBallObjPath);
	game->gameObjects.push_back(playerObj);
	game->cam = orbitCam;

	aiaiHead = new Mesh();
	aiaiHead->importObj(aiaiHeadObjPath,true,aiaiHeadUVPath);
	aiaiBody = new Mesh();
	aiaiBody->importObj(aiaiBodyObjPath,true,aiaiBodyUVPath);
	aiaiArm = new Mesh();
	aiaiArm->importObj(aiaiArmObjPath,true,aiaiArmUVPath);
	aiaiBall = new Mesh();
	aiaiBall->importObj(aiaiBallObjPath, false, aiaiBallUVPath);
	playerObj->head = aiaiHead;
	playerObj->body = aiaiBody;
	playerObj->arm = aiaiArm;
	playerObj->ball = aiaiBall;
	orbitCam->setTargetObject(playerObj->rootPos);

	stage = new Mesh();
	stage->importObj(stagePath0,true,stageUVPath);

}

/* display function - GLUT display callback function
 *		clears the screen, sets the camera position
 */
void display(void){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();	//Push base matrix that everything else will be pushed onto
		//Apply material settings
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, s_dif);
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, s_amb);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, s_spe);
		if (debugMode)
		{
			m_temp[0] = 1; m_temp[1] = 0; m_temp[2] = 0;
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, m_temp);
			glPointSize(3);
			glBegin(GL_POINTS);
				glVertex3f(orbitCam->camPos->x,orbitCam->camPos->y,orbitCam->camPos->z); //Crosshair
			glEnd();
			glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, no_mat);
		}
		glPushMatrix(); //Draw temp ground plane
			glTranslatef(0,groundHeight,0); //Move the ground plane down from the origin a bit

			stage->drawMesh(25);
		glPopMatrix();

		for (int i = 0; i < game->gameObjects.size(); i++)
		{
			game->gameObjects[i]->drawMesh(1);
		}

	glPopMatrix();
	//swap buffers
	glutSwapBuffers();
}

//TODO: Move the actual function calls into the game state update loop instead?
//function for keyboard commands
void keyboard(unsigned char key, int xIn, int yIn){
	int mod = glutGetModifiers();
	switch (key){
		case 'q':	//quit
		case 27:	//27 is the esc key
			exit(0);
			break;
                //Camera zoom
                case '.':
			orbitCam->camDist += 1;
			break;
                case ',':
			orbitCam->camDist -= 1;
			break;
	}
}

void special(int key, int xIn, int yIn)
{
	switch (key) {
		case GLUT_KEY_DOWN:
			playerObj->rootPos->x += 1;
			//orbitCam->camElev += 1;
			break;
		case GLUT_KEY_UP:
			playerObj->rootPos->x -= 1;
			//orbitCam->camElev -= 1;
			break;
		case GLUT_KEY_LEFT:
			playerObj->rootPos->y += 1;
			//orbitCam->camAzimuth += 1;
			break;
		case GLUT_KEY_RIGHT:
			playerObj->rootPos->y -= 1;
			//orbitCam->camAzimuth -= 1;
			break;
	}
}
//OpenGL mouse functions
void mouseClick(int btn, int state, int x, int y)
{
	if (btn == GLUT_LEFT_BUTTON)
	{
		if(state == GLUT_DOWN)
		{
			mButtonsPressed[0] = true;
		}
	}
	if (btn == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mButtonsPressed [1] = true;
		}
	}
	if (btn == GLUT_MIDDLE_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mButtonsPressed [2] = true;
		}
	}
}

void mouseMove(int x, int y)
{
	mx = x;
	my = y;
}

//Reshape function for main window.
void reshape(int w, int h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (float)((w+0.0f)/h), 1, 1000);	//adjust perspective to keep terrain in view
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);			//adjust viewport to new height and width
}

void gameUpdate(float dt)
{
	//Values at time of frame update
	game->tick(dt, mx, my, mButtonsPressed, keysPressed);

	//Flush input
	mButtonsPressed[0] = false;
	mButtonsPressed[1] = false;
	mButtonsPressed[2] = false;
}

//FPS controller
void FPSTimer(int value){
	glutTimerFunc(value, FPSTimer, 0);
	gameUpdate((float)value);
	glutPostRedisplay();
}

/* main function - program entry point */
int main(int argc, char** argv)
{
	srand(time(NULL));				//initialize randomization
	glutInit(&argc, argv);		//starts up GLUT
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	//MAIN WINDOW
	glutInitWindowSize(800, 400);	//setup window size and position
	glutInitWindowPosition(50, 50);
	int mainWindow = glutCreateWindow("Super Monkey Ball");	//creates the window

	glutDisplayFunc(display);					//registers "display" as the display callback function
	glutKeyboardFunc(keyboard);				//registers "keyboard" as the keyboard callback function
	glutSpecialFunc(special);
	//mouse callbacks
	glutMouseFunc(mouseClick);
	glutMotionFunc(mouseMove);
	glutPassiveMotionFunc(mouseMove);
	glutTimerFunc(17, FPSTimer, 0);		//registers "FPSTimer" as the timer callback function
	glutReshapeFunc(reshape);					//registers "reshape" as the reshape callback function

	init();						//initialize main window

	glutMainLoop();				//starts the event glutMainLoop
	return(0);					//return may not be necessary on all compilers
}
