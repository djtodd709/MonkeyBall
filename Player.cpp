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
	currentPosition = new v3;
	currentPosition->x = 0.0f;
	currentPosition->y = 0.0f;
	currentPosition->z = 0.0f;
	velocity = new v3;
	velocity->x = 0.0f;
	velocity->y = 0.0f;
	velocity->z = 0.0f;
	startingPosition = new v3;
	startingPosition->x = 0.0f;
	startingPosition->y = 0.0f;
	startingPosition->z = 0.0f;
}

void Player::goToStage(Stage* s)
{
	startingPosition = s->playerStart;
	velocity->x = 0.0f;
	velocity->y = 0.0f;
	velocity->z = 0.0f;
}

void Player::onCollision(Collider* o)
{

}

void Player::onTick()
{
	if (isAirborne())
	{
		if (velocity->y < terminalVelocity && velocity->y > -terminalVelocity)
		{
			velocity->y -= gravity;
		}
		else
		{
			if (velocity->y > 0)
			{
				velocity->y = terminalVelocity;
			}
			else
			{
				velocity->y = -terminalVelocity;
			}
		}
	}
	*currentPosition = *currentPosition + *velocity;
	float cy = currentPosition->y;
	ballAngle += 5.0f;
	if (cy < -200.0f)
	{
		printf("FALL OUT!\n");
		gameStateRef->resetStage();
	}
}

bool Player::isAirborne()
{
	//TODO: THAR BE MATH HERE
	return true;
}

void Player::reset()
{
	velocity->x = 0.0f;
	velocity->y = 0.0f;
	velocity->z = 0.0f;
	*currentPosition = *startingPosition;
}

void Player::drawMesh(float repeats)
{
	glPushMatrix();
		glTranslatef(currentPosition->x, currentPosition->y, currentPosition->z);
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