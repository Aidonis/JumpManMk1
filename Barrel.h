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

	void SetIsOnGround(bool a_grounded);
	bool GetIsOnGround();

	void SetMoveExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme);
	float ySpeed;

private:
	float speed;

	float leftExtreme;
	float rightExtreme;

	//flags
	bool onLadder;
	bool onGround;
};

