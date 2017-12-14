#ifdef __APPLE__
#  include <OpenGL/gl.h>
#  include <OpenGL/glu.h>
#  include <GLUT/glut.h>
#else
#  include <GL/gl.h>
#  include <GL/glu.h>
#  include <GL/freeglut.h>
#endif

#include <cstdio>
#include "Player.h"

Player::Player(const char * pathToAssetFolder) : Entity(pathToAssetFolder)
{
	rootPos = new v3;
	rootPos->x = 0;
	rootPos->y = 0;
	rootPos->z = 0;
}

void Player::onTick()
{
	ballAngle += 5.0f;
}

void Player::drawMesh(float repeats)
{
	glPushMatrix();
		glTranslatef(rootPos->x, rootPos->y, rootPos->z);
		glPushMatrix();
			//Apply material settings
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m0_dif);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m0_amb);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m0_spe);

			head->drawMesh(1);
			glTranslatef(0, -1.7f, 0);
			body->drawMesh(1);
			glTranslatef(0, 0.9f, 0);
			glPushMatrix();
				glTranslatef(1.3f, 0, 0);
				glRotatef(40, 0, 0, 1);
				arm->drawMesh(1);
			glPopMatrix();
			glPushMatrix();
				glTranslatef(-1.3f, 0, 0);
				glRotatef(180, 0, 1, 0);
				glRotatef(40, 0, 0, 1);
				arm->drawMesh(1);
			glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			glScalef(6, 6, 6);
			glRotatef(ballAngle, 1, 0, 0);
			//Apply material settings
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m2_dif);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m2_amb);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m2_spe);
			ball->drawMesh(1);
			glRotatef(180, 1, 0, 0);
			//Apply material settings
			glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m1_dif);
			glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m1_amb);
			glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m1_spe);
			ball->drawMesh(1);
		glPopMatrix();
	glPopMatrix();
}