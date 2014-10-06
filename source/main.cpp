#pragma once

#include "AIE.h"
#include <iostream>
#include "Player.h"
#include "Platform.h"

Platform grass;
Player player1;

int main(int argc, char* argv[])
{
	Initialise(800, 600, false, "JumpMan");

	SetBackgroundColour(SColour(0, 0, 0, 255));

	//Initialize platform
	grass.SetSize(70, 70);
	grass.SetPosition(400, 0);
	grass.SetSpriteID(CreateSprite("./images/tiles/grassHalf.png", grass.GetWidth(), grass.GetHeight(), true));
	MoveSprite(grass.GetSpriteID(), grass.GetX(), grass.GetY());

	//Player 1
	player1.SetSize(66, 92);
	player1.SetPosition(400, 200);
	player1.SetGravity(150.f);
	player1.SetSpriteID(CreateSprite("./images/p1_front.png", player1.GetWidth(), player1.GetHeight(), true));
	player1.SetMoveKeys('A', 'D', 'W');
	MoveSprite(player1.GetSpriteID(), player1.GetX(), player1.GetY());

	//Game Loop
	do
	{

		float deltaT = GetDeltaTime();

		if (IsKeyDown(player1.GetLeftKey())){
			player1.SetX(player1.GetX() - 150.f * deltaT);
		}

		if (IsKeyDown(player1.GetRightKey())){
			player1.SetX(player1.GetX() + 150.f * deltaT);
		}


		MoveSprite(player1.GetSpriteID(), player1.GetX(), player1.GetY());
		DrawSprite(player1.GetSpriteID());
		DrawSprite(grass.GetSpriteID());
		ClearScreen();

	} while (!FrameworkUpdate());

	Shutdown();

	return 0;
}