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

bool IsCollide();
void DrawGrass();
void LoadGrass();

int main(int argc, char* argv[])
{
	Initialise(800, 600, false, "JumpMan");

	SetBackgroundColour(SColour(0, 0, 0, 255));

	//Initialize platform
	//grass.SetSize(70, 70);
	//grass.SetPosition(400, 0);
	//grass.SetSpriteID(CreateSprite("./images/tiles/grassHalf.png", grass.GetWidth(), grass.GetHeight(), true));
	//MoveSprite(grass.GetSpriteID(), grass.GetX(), grass.GetY());

	//Player 1
	player1.SetSize(60, 80);
	player1.SetPosition(400, 200);
	player1.SetGravity(150.f);
	player1.SetSpeed(150.f);
	player1.SetSpriteID(CreateSprite("./images/p1_front.png", player1.GetWidth(), player1.GetHeight(), true));
	player1.SetMoveKeys('A', 'D', 'W');
	player1.SetMoveExtremes(0, SCREEN_WIDTH);
	MoveSprite(player1.GetSpriteID(), player1.GetX(), player1.GetY());
	LoadGrass();

	//Game Loop
	do
	{

		float deltaT = GetDeltaTime();

		player1.Update(deltaT);
		
		if (IsCollide()){
			player1.SetY(player1.GetY() - player1.GetGravity() * deltaT);
		}

		DrawGrass();
		player1.Draw();
		ClearScreen();

	} while (!FrameworkUpdate());

	Shutdown();

	return 0;
}

bool IsCollide(){
	for (int i = 0; i < TOTAL_PLATFORMS; i++){
		//if (player1.GetLeft() < grass[i].GetRight() && player1.GetRight() > grass[i].GetLeft()){
			if (player1.GetBottom() < grass[i].GetTop()){
				//player1.SetY(grass.GetTop() + (player1.GetHeight() / 2));
				return false;
			//}
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