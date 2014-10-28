#include "MainMenuState.h"
#include "AIE.h"
#include "GameState.h"
#include "StateMachine.h"
#include "Leaderboard.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;


MainMenuState::MainMenuState(void)
{
}


MainMenuState::~MainMenuState(void)
{
}

void MainMenuState::Initialize()
{
	menuSprite = CreateSprite("./images/tempMenu.png", SCREEN_WIDTH, SCREEN_HEIGHT, true);
	MoveSprite(menuSprite, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
}

void MainMenuState::Update(float a_deltaTime, StateMachine* a_pSM)
{
	//Enter
	if (IsKeyDown(257))
	{
		a_pSM->PushState(new GameState());
	}
	//F1
	if (IsKeyDown(290)){
		a_pSM->PushState(new Leaderboard());
	}
	//Q
	if (IsKeyDown('Q')){
		StateMachine::endGame = true;
		a_pSM->PopState();
	}
}

void MainMenuState::Draw()
{
	DrawSprite(menuSprite);
}

void MainMenuState::Destroy()
{
	DestroySprite(menuSprite);
}