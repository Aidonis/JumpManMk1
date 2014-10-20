#pragma once
#include "BaseState.h"
class WinnerState :
	public BaseState
{
public:
	WinnerState(void);
	~WinnerState(void);

	void Initialize();
	void Update(float a_deltaTime, StateMachine* a_pSM);
	void Draw();
	void Destroy();

private:
	unsigned int winnerSprite;
};

