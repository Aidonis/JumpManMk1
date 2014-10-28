#include "SplashScreen.h"
#include "MainMenuState.h"
#include "AIE.h"
#include "StateMachine.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

SplashScreen::SplashScreen()
{
	startTimer = 0;
}


SplashScreen::~SplashScreen()
{
}

void SplashScreen::Initialize()
{
	splashSprite = CreateSprite("./images/tempSplash.png", SCREEN_WIDTH, SCREEN_HEIGHT, true);
	MoveSprite(splashSprite, SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f);
}

void SplashScreen::Update(float a_deltaTime, StateMachine* a_pSM)
{
	startTimer += a_deltaTime;

	if (startTimer >= 5){
		a_pSM->SwitchState(new MainMenuState());
	}

}

void SplashScreen::Draw()
{
	DrawSprite(splashSprite);
}

void SplashScreen::Destroy()
{
	DestroySprite(splashSprite);
}