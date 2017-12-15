#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "Entity.h"
#include "GameState.h"

//Base class for all game objects - each should include a model and  collision geometry.
class Player : public Entity{
public:
	Player(const char * pathToAssetFolder);
	void goToStage(Stage* s);
	Mesh* head;
	Mesh* body;
	Mesh* arm;
	Mesh* ball;
	virtual void onCollision(Entity* o, v3 normal) override;
	virtual void reset() override;
	virtual void onTick() override;
	virtual void drawMesh(float repeats) override;
	GameState* gameStateRef;
private:
	float ballAngle = 0.0f;
	float terminalVelocity = 1.0f;
	float gravity = 0.02f;
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
