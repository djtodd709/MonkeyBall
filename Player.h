#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"

//Base class for all game objects - each should include a model and  collision geometry.
class Player : public Entity{
public:
	Player(const char * pathToAssetFolder);
	v3* rootPos;
	Mesh* head;
	Mesh* body;
	Mesh* arm;
	Mesh* ball;
	virtual void onTick() override;
	virtual void drawMesh(float repeats) override;
private:
	float ballAngle = 0.0f;
	float terminalVelocity = 1.0f;
	bool isAirborne();
	v3* velocity;

	//Material properties - white
	float m0_dif[4] = { 1.0f, 1.0f, 1.0f, 1 };
	float m0_amb[4] = { 0.5f, 0.5f, 0.5f, 1 };
	float m0_spe[4] = { 1.0f, 1.0f, 1.0f, 1 };

	//Material properties - white alpha
	float m1_dif[4] = { 1.0f, 1.0f, 1.0f, 0.8f };
	float m1_amb[4] = { 0.5f, 0.5f, 0.5f, 0.8f };
	float m1_spe[4] = { 1.0f, 1.0f, 1.0f, 0.8f };

	//Material properties - red alpha
	float m2_dif[4] = { 1.0f, 0.2f, 0.2f, 0.7f };
	float m2_amb[4] = { 0.5f, 0.1f, 0.1f, 0.7f };
	float m2_spe[4] = { 1.0f, 1.0f, 1.0f, 0.7f };
};

#endif
