#pragma once

#include "AIE.h"
#include <iostream>
#include "Player.h"
#include "Platform.h"
#include <vector>

//Const
extern const int SCREEN_WIDTH = 600;
extern const int SCREEN_HEIGHT = 800;
const int TOTAL_PLATFORMS = 16;

void GamePlayUpdate(float a_deltaTime);
void PlayerLogic(Player* a_player, float a_deltaTime);

//Platform grass[TOTAL_PLATFORMS];
std::vector<Entity*> gameObjects;

Player* player = new Player();

bool IsColliding();
void DrawGrass();
void LoadGrass();

int main(int argc, char* argv[])
{
	Initialise(SCREEN_WIDTH, SCREEN_HEIGHT, false, "JumpMan");

	SetBackgroundColour(SColour(0, 0, 0, 255));

	//Player 1
	player->SetSize(60, 80);
	player->SetPosition(400, 200);
	player->SetGravity(5.f);
	player->SetSpeed(500.f);
	player->SetSpriteID(CreateSprite("./images/p1_front.png", player->GetWidth(), player->GetHeight(), true));
	player->SetMoveKeys('A', 'D', 'W');
	player->SetMoveExtremes(0, SCREEN_WIDTH);
	MoveSprite(player->GetSpriteID(), player->GetX(), player->GetY());
	LoadGrass();

	gameObjects.push_back(player);

	//Game Loop
	do
	{
		ClearScreen();
		float deltaT = GetDeltaTime();
		
		GamePlayUpdate(deltaT);

	} while (!FrameworkUpdate());

	Shutdown();

	return 0;
}

void GamePlayUpdate(float a_deltaTime){



}

bool IsColliding(){
	for (auto grass : gameObjects)
	{
		if (dynamic_cast<Platform*>(grass) != 0)
		{
			Platform* grass = dynamic_cast<Platform*>(grass);
			for (int i = 0; i < TOTAL_PLATFORMS; i++){
				if (player->GetBottom() <= grass->GetTop())
				{
					return true;
				}
				else{
					return false;
				}
			}
		}
	}
	
}

void LoadGrass(){

	//Initial position
	float grassX = SCREEN_WIDTH * .01f;
	float grassY = 0;

	for (int i = 0; i < TOTAL_PLATFORMS; i++){

		Platform* grass = new Platform();

		//Initialize Sprite
		grass->SetSize(player->GetWidth(), player->GetHeight());
		grass->SetSpriteID(CreateSprite("./images/tiles/grassHalfMid.png", grass->GetWidth(), grass->GetHeight(), true));

		if (grassX > SCREEN_WIDTH){
			grassX = 0;
			grassY -= .08f * SCREEN_HEIGHT;
		}

		//initialize position
		grass->SetPosition(grassX, grassY);

		//Increment position
		grassX += grass->GetWidth();

		//Add to array
		gameObjects.push_back(grass);
	}
}

void PlayerLogic(Player* a_player, float a_deltaTime)
{
	//How to jump
	if (IsColliding())
	{
		for (auto grass : gameObjects)
		{
			if (dynamic_cast<Platform*>(grass) != 0)
			{
				Platform* grass = dynamic_cast<Platform*>(grass);
				// y velocity
				a_player->SetVelocity(0.0f);
				a_player->SetY(grass->GetTop() + a_player->GetHeight() * 0.5f);

				float jumpAccel = 700;

				if (IsKeyDown('W'))
				{
					// kick the player up
					a_player->SetVelocity(a_player->GetVelocity() + jumpAccel - (a_player->GetGravity()));
				}
			}


			else{
				a_player->SetVelocity((a_player->GetVelocity() - (a_player->GetGravity())));
			}
		}
	}
	a_player->Update(a_deltaTime);
	a_player->Draw();
}

//void DrawGrass(){
//	for (int i = 0; i < TOTAL_PLATFORMS; i++){
//			grass[i].Draw();
//	}
//}