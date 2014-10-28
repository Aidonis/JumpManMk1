#pragma once

#include "AIE.h"
#include <iostream>
#include "Player.h"
#include "Platform.h"
#include <vector>
#include "StateMachine.h"
#include "MainMenuState.h"
#include "GameState.h"
#include "SplashScreen.h"

//Const
extern const int SCREEN_WIDTH = 600;
extern const int SCREEN_HEIGHT = 800;

int main(int argc, char* argv[])
{
	Initialise(SCREEN_WIDTH, SCREEN_HEIGHT, false, "JumpMan");

	SetBackgroundColour(SColour(0, 0, 0, 255));

	StateMachine state;
	state.PushState(new MainMenuState());
	

	//Game Loop
	do
	{
		ClearScreen();

		float deltaT = GetDeltaTime();

		state.Update(deltaT);
		state.Draw();
		

	} while (!FrameworkUpdate() && !StateMachine::endGame);

	Shutdown();

	return 0;
}