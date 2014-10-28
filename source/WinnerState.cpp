#include "WinnerState.h"
#include "AIE.h"
#include "GameState.h"
#include "StateMachine.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;


WinnerState::WinnerState(void)
{
}


WinnerState::~WinnerState(void)
{
}

void WinnerState::Initialize()
{
	winnerSprite = CreateSprite("./images/tempWinner.png", SCREEN_WIDTH, SCREEN_HEIGHT, true);
	MoveSprite(winnerSprite, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
}

void WinnerState::Update(float a_deltaTime, StateMachine* a_pSM)
{
	if (IsKeyDown(257))
	{
		a_pSM->SwitchState(new GameState());
	}
	if (IsKeyDown(256))
	{
		BaseState* lastState = a_pSM->PopState();
		delete lastState;
		return;
	}
}

void WinnerState::Draw()
{
	DrawSprite(winnerSprite);
}

void WinnerState::Destroy()
{
	DestroySprite(winnerSprite);
}