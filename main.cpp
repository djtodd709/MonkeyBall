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

#include "Mesh.h"
Mesh *myMesh;

#define X 0
#define Y 1
#define Z 2

//Light 0 properties
float l0pos[4] = {10.0f,15.0f,10.0f,1};
float l0dif[4] = {0.7f,0.7f,0.7f,1};
float l0amb[4] = {0.1f,0.1f,0.1f,1};
float l0spe[4] = {1,1,1,1};

//Material properties - kinda grassy
float m_dif[4] = {0.6f,0.9f,0.4f,1};
float m_amb[4] = {0,0.1f,0,1};
float m_spe[4] = {0.1f,0.1f,0.1f,1};
float shiny = 10;

//position of camera and target. camPos is scaled to the size of the terrain
float camPos[] = {0, 5.0f, 5.0f};	//where the camera is
float camTarget[] = {0,0,0};

//initial settings for main window. Called (almost) at the begining of the program.
void init(void){
	glClearColor(1, 1, 1, 0);	//black background
	glColor3f(1, 1, 1);

	glMatrixMode(GL_PROJECTION);

	//Enable lights and depth testing
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

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
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m_dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m_amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m_spe);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shiny);

	//adjust view
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluPerspective(45, 1, 1, 1000);

	//aiaiHead = new Mesh();
	//aiaiHead->importObj();

}

/* display function - GLUT display callback function
 *		clears the screen, sets the camera position
 */
void display(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(camPos[X], camPos[Y], camPos[Z], camTarget[X], camTarget[Y], camTarget[Z], 0,1,0);

	glPushMatrix();	//Push base matrix that everything else will be pushed onto
		//aiaiHead->drawMesh();
	glPopMatrix();
	//swap buffers
	glutSwapBuffers();
}

//function for keyboard commands
void keyboard(unsigned char key, int xIn, int yIn){
	int mod = glutGetModifiers();
	switch (key){
		case 'q':	//quit
		case 27:	//27 is the esc key
			exit(0);
			break;
	}
}

//Reshape function for main window.
void reshape(int w, int h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//gluPerspective(45, (float)((w+0.0f)/h), 1, 1000);	//adjust perspective to keep terrain in view
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, w, h);			//adjust viewport to new height and width
}

//FPS controller
void FPSTimer(int value){
	glutTimerFunc(17, FPSTimer, 0);
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
	glutTimerFunc(17, FPSTimer, 0);		//registers "FPSTimer" as the timer callback function
	glutReshapeFunc(reshape);					//registers "reshape" as the reshape callback function

	init();						//initialize main window

	glutMainLoop();				//starts the event glutMainLoop
	return(0);					//return may not be necessary on all compilers
}
