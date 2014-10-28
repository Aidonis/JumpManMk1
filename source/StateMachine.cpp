#include "StateMachine.h"

StateMachine::StateMachine(void)
{
}


StateMachine::~StateMachine(void)
{
}

void StateMachine::PushState(BaseState* a_gameState)
{
	stateStack.push_back(a_gameState);
	a_gameState->Initialize();
}

BaseState* StateMachine::PopState()
{
	BaseState* lastState = stateStack.back();
	stateStack.pop_back();
	lastState->Destroy();
	return lastState;
}

BaseState* StateMachine::SwitchState(BaseState* a_gameState)
{
	BaseState* lastState = stateStack.back();
	lastState->Destroy();

	stateStack.pop_back();
	stateStack.push_back(a_gameState);
	a_gameState->Initialize();

	return lastState;
}

void StateMachine::Update(float a_deltaTime)
{
	stateStack.back()->Update(a_deltaTime, this);
}

void StateMachine::Draw()
{
	if (!StateMachine::endGame){
		stateStack.back()->Draw();
	}
}

bool StateMachine::endGame = false;