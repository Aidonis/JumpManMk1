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

	void SetSpeed(float speed);
	float GetSpeed();

	void SetOnLadder(bool a_onLadder);
	bool GetOnLadder();

private:
	float speed;

	bool onLadder;

};

