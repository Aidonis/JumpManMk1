#pragma once

#include "BaseState.h"
#include "Player.h"
#include "Platform.h"
#include <vector>
class GameState : public BaseState
{
public:
	GameState(void);
	~GameState(void);

	void Initialize();
	void Update(float a_deltaTime, StateMachine* a_pSM);
	void Draw();
	void Destroy();

private:

};

