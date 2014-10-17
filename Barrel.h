#pragma once

#include "Entity.h"
#include "AIE.h"
class Barrel :
	public Entity
{
public:
	Barrel();
	~Barrel();

	void Update(float a_deltaTime);
	void Draw();

	virtual bool isCollideTop(Entity* other);

	void SetSpeed(float speed);
	float GetSpeed();

	void SetOnLadder(bool a_onLadder);
	bool GetOnLadder();

	void SetAccel(float a_acceleration);
	float GetAccel();

	void SetVelocity(float a_velocity);
	float GetVelocity();

	void SetGravity(float a_gravity);
	float GetGravity();

private:
	float speed;
	float acceleration;
	float gravity;
	float velocity;
	float ySpeed;

	bool onLadder;

};
