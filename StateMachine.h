#pragma once

#ifndef _STATEMACHINE_H_
#define _STATEMACHINE_H_
#include "BaseState.h"
#include <list>
class StateMachine
{
public:
	StateMachine(void);
	~StateMachine(void);

	void PushState(BaseState* gameState);
	BaseState* PopState();
	BaseState* SwitchState(BaseState* gameState);

	void Update(float a_deltaTime);
	void Draw();

	static bool endGame;

private:
	std::list<BaseState*> stateStack;
};

#endif //_STATEMACHINE_H_