#pragma once

#include "AIE.h"
#include <iostream>
#include "Player.h"
#include "Platform.h"

//Const
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;
const int TOTAL_PLATFORMS = 14;

Platform grass[TOTAL_PLATFORMS];
Player player1;

bool IsColliding();
void DrawGrass();
void LoadGrass();

int main(int argc, char* argv[])
{
	Initialise(800, 600, false, "JumpMan");

	SetBackgroundColour(SColour(0, 0, 0, 255));

	//Player 1
	player1.SetSize(60, 80);
	player1.SetPosition(400, 200);
	player1.SetGravity(5.f);
	player1.SetSpeed(500.f);
	player1.SetSpriteID(CreateSprite("./images/p1_front.png", player1.GetWidth(), player1.GetHeight(), true));
	player1.SetMoveKeys('A', 'D', 'W');
	player1.SetMoveExtremes(0, SCREEN_WIDTH);
	MoveSprite(player1.GetSpriteID(), player1.GetX(), player1.GetY());
	LoadGrass();

	//Game Loop
	do
	{
		ClearScreen();
		float deltaT = GetDeltaTime();

		

		// ground shit

		
		if (IsColliding()){
			// y velocity
			player1.SetVelocity(0.0f);
			player1.SetY(grass[0].GetTop() + player1.GetHeight() * 0.5f);

			float jumpAccel = 800;

			if (IsKeyDown('W'))
			{
				// kick the player up
				player1.SetVelocity(player1.GetVelocity() + jumpAccel - (player1.GetGravity()));
				//player1.SetY(player1.GetY() + player1.GetVelocity());
				//player1.SetY(player1.GetY() + 5);
			}
		}
		

		else{
			player1.SetVelocity((player1.GetVelocity() - (player1.GetGravity())));
		}
		
		

		DrawGrass();
		player1.Update(deltaT);
		player1.Draw();
		

		//std::cout << player1.GetVelocity() << std::endl;

	} while (!FrameworkUpdate());

	Shutdown();

	return 0;
}

bool IsColliding(){
	for (int i = 0; i < TOTAL_PLATFORMS; i++){
		if (player1.GetBottom() <= grass[i].GetTop())
		{
			//player1.SetY(grass[i].GetTop() + player1.GetHeight() * 0.5f);
			return true;
		}
		else{
			return false;
		}
	}
}

void LoadGrass(){

	//Initial position
	float grassX = SCREEN_WIDTH * .01f;
	float grassY = 0;

	for (int i = 0; i < TOTAL_PLATFORMS; i++){

		//Initialize Sprite
		grass[i].SetSize(player1.GetWidth(), player1.GetHeight());
		grass[i].SetSpriteID(CreateSprite("./images/tiles/grassHalfMid.png", grass[i].GetWidth(), grass[i].GetHeight(), true));

		if (grassX > SCREEN_WIDTH){
			grassX = 0;
			grassY -= .08f * SCREEN_HEIGHT;
		}

		//initialize position
		grass[i].SetPosition(grassX, grassY);

		//Increment position
		grassX += grass[i].GetWidth();
	}
}

void DrawGrass(){
	for (int i = 0; i < TOTAL_PLATFORMS; i++){
			grass[i].Draw();
	}
}