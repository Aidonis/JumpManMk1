#pragma once

#include "BaseState.h"

class MainMenuState : public BaseState
{
public:
	MainMenuState(void);
	~MainMenuState(void);

	void Initialize();
	void Update(float a_deltaTime, StateMachine* a_pSM);
	void Draw();
	void Destroy();

private:
	unsigned int menuSprite;
};

