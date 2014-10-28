#pragma once

#include "BaseState.h"

class DeathState : public BaseState
{
public:
	DeathState(void);
	~DeathState(void);

	void Initialize();
	void Update(float a_deltaTime, StateMachine* a_pSM);
	void Draw();
	void Destroy();

private:
	unsigned int deathSprite;
};

