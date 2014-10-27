#pragma once
#include "BaseState.h"
class SplashScreen :
	public BaseState
{
public:
	SplashScreen();
	~SplashScreen();

	void Initialize();
	void Update(float a_deltaTime, StateMachine* a_pSM);
	void Draw();
	void Destroy();

private:
	unsigned int splashSprite;
	float startTimer;
};

