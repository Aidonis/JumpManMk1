#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "AIE.h"
#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	void SetMoveKeys(unsigned int a_moveLeft, unsigned int a_moveRight, unsigned int a_jumpKey);
	void SetMoveExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme);

	unsigned int GetLeftKey();
	unsigned int GetRightKey();
	unsigned int GetJumpKey();

	void SetSpeed(float speed);
	float GetSpeed();

	void SetAccel(float a_acceleration);
	float GetAccel();

	void SetVelocity(float a_velocity);
	float GetVelocity();

	void SetGravity(float a_gravity);
	float GetGravity();

	virtual void Update(float a_deltaTime);
	virtual void Draw();

	virtual bool isCollideTop(Entity* other);
	virtual bool isOnLadder(Entity* other);

private:
	float acceleration;
	float velocity;
	float gravity;
	float speed;
	float ySpeed;

	unsigned int moveLeft;
	unsigned int moveRight;
	unsigned int jump;

	unsigned int leftExtreme;
	unsigned int rightExtreme;

};

#endif //_PLAYER_H_