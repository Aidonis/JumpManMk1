#include "DeathState.h"
#include "AIE.h"
#include "GameState.h"
#include "StateMachine.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

DeathState::DeathState()
{
}


DeathState::~DeathState()
{
}

void DeathState::Initialize()
{
	deathSprite = CreateSprite("./images/tempDeath.png", SCREEN_WIDTH, SCREEN_HEIGHT, true);
	MoveSprite(deathSprite, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
}

void DeathState::Update(float a_deltaTime, StateMachine* a_pSM)
{
	if (IsKeyDown(257))
	{
		a_pSM->SwitchState(new GameState());
	}
	if (IsKeyDown(256)){
		BaseState* lastState = a_pSM->PopState();
		delete lastState;
		return;
	}
}

void DeathState::Draw()
{
	DrawSprite(deathSprite);
}

void DeathState::Destroy()
{
	DestroySprite(deathSprite);
}