#include "GameState.h"
#include "DeathState.h"
#include "WinnerState.h"
#include "AIE.h"
#include "StateMachine.h"
#include <iostream>

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
std::vector<Entity*> GameState::gameObjects;

GameState::GameState(void)
{
}


GameState::~GameState(void)
{
}

void GameState::Initialize()
{
	//Load Game Objects
	gameObjects.erase(gameObjects.begin(), gameObjects.end());
	LoadGrass();
	LoadLadders();
	LoadBarrels();
	LoadPlayer();
	
}

void GameState::Update(float a_deltaTime, StateMachine* a_pSM)
{
	if (IsKeyDown(256))
	{
		BaseState* lastState = a_pSM->PopState();
		delete lastState;
		return;
	}

	for (auto object : gameObjects)
	{
		if (dynamic_cast<Player*>(object) != 0)
		{
			Player* player = dynamic_cast<Player*>(object);

			PlayerLogic(player, a_deltaTime);
			if (!player->GetIsActive()){

				a_pSM->SwitchState(new DeathState());
			}
			if (player->GetIsWinner()){
				a_pSM->SwitchState(new WinnerState);
			}
		}
		if (dynamic_cast<Barrel*>(object) != 0)
		{
			BarrelLogic(dynamic_cast<Barrel*>(object), a_deltaTime);
		}

	

		object->Update(a_deltaTime);
		object->Draw();
	}
}
void GameState::Draw()
{
	for (auto object : gameObjects)
	{
		object->Draw();
	}

	//Print Score Stuff
	DrawString("Score < 1 >", SCREEN_WIDTH * 0.1f, SCREEN_HEIGHT - 2);

}
void GameState::Destroy()
{
	for (auto object : gameObjects)
	{
		DestroySprite(object->GetSpriteID());
	}
}

void GameState::LoadPlayer(){
	Player* player = new Player();

	//Player 1
	player->SetSize(30, 40);
	player->SetPosition(150, 220);
	player->SetGravity(.04f);
	player->SetXSpeed(250.0f);
	player->SetSpriteID(CreateSprite("./images/p1_front.png", player->GetWidth(), player->GetHeight(), true));
	player->SetMoveKeys('A', 'D', 'W');
	player->SetMoveExtremes(0, SCREEN_WIDTH);

	gameObjects.push_back(player);
}

void GameState::LoadGrass()
{
	//Initial position
	float grassX = -35.f;
	float grassY = 35;
	unsigned int spriteID = CreateSprite("./images/tiles/grassHalfMid.png", 70, 70, true);

	for (int i = 0; i < TOTAL_PLATFORMS; i++){

		Platform* grass = new Platform();

		//initialize position winning platform
		if (i > 28){
			grassX = SCREEN_WIDTH * 0.7f;
			grassY = SCREEN_HEIGHT * 0.8f;

		}

		//New row
		if (grassX > SCREEN_WIDTH){
			grassX = -35;
			grassY += 250;
		}

		//Increment position
		grassX += grass->GetWidth();
		grass->SetPosition(grassX, grassY);

		//Add to array
		gameObjects.push_back(grass);
	}
}

void GameState::LoadLadders()
{
	//Initial Ladder
	float ladderX = SCREEN_WIDTH * 0.8f;
	float ladderY = 155;
	
	for (int j = 0; j < 2; j++){
		for (int i = 0; i < 4; i++){
			if (j == 1){
				Ladders* ladder = new Ladders();

				ladder->SetSize(40, 70);
				ladder->SetSpriteID(CreateSprite("./images/tiles/ladder_mid.png", ladder->GetWidth(), ladder->GetHeight(), true));

				//Set new start position
				ladderX = SCREEN_WIDTH * 0.2f;
				ladder->SetPosition(ladderX, ladderY);


				//Increment position
				ladderY += 70;

				gameObjects.push_back(ladder);
			}
			else if (j == 0){
				Ladders* ladder = new Ladders();

				ladder->SetSize(40, 70);
				ladder->SetSpriteID(CreateSprite("./images/tiles/ladder_mid.png", ladder->GetWidth(), ladder->GetHeight(), true));

				ladder->SetPosition(ladderX, ladderY);

				ladderY += 70;

				gameObjects.push_back(ladder);
			}
		}
	}
}

void GameState::LoadBarrels(){
	float barrelX = SCREEN_WIDTH * 0.2f;
	float barrelY = SCREEN_HEIGHT * 0.8f;
	float barrelSpeed = 10.f;

	unsigned int spriteID = CreateSprite("./images/dirtCaveRockLarge.png", 50, 50, true);

	for (int i = 0; i < 3; i++){
		if (i == 1){
			barrelY = SCREEN_HEIGHT * 0.5f;
			barrelX = SCREEN_WIDTH * 0.8f;
		}
		else if (i == 2){
			barrelX = SCREEN_WIDTH * 0.4f;
			barrelY = SCREEN_HEIGHT * 0.2f;
		}
		else
		{
			barrelY = SCREEN_HEIGHT * 0.8f;
		}
		Barrel* barrels = new Barrel();

		barrels->SetSize(50, 50);
		barrels->SetSpriteID(spriteID);

		barrels->SetSpeed(barrelSpeed);

		barrels->SetPosition(barrelX, barrelY);
		barrels->SetMoveExtremes(0, SCREEN_WIDTH);

		gameObjects.push_back(barrels);
	}
}


void GameState::PlayerLogic(Player* a_player, float a_deltaTime)
{
	a_player->SetOnLadder(false);
	a_player->SetIsOnGround(false);
	a_player->velocity.y -= a_player->GetGravity();

	for (auto object : gameObjects)
	{
		// If the current object is a ladder
		if (dynamic_cast<Ladders*>(object) != 0){

			Ladders* ladder = dynamic_cast<Ladders*>(object);

			//If colliding with any platforms
			if (a_player->IsCollided(ladder))
			{
				a_player->SetOnLadder(true);
			}
			if (a_player->GetOnLadder()){
				a_player->velocity = Vector2(0, 0);
				if (IsKeyDown('W')){
					a_player->velocity.y = 1;
				}
				if (IsKeyDown('S')){
					a_player->velocity.y = -1;
				}
			}
		}

		// If the current object is a platform
		else if (dynamic_cast<Platform*>(object) != 0)
		{
			

			Platform* grass = dynamic_cast<Platform*>(object);
	
			//if (a_player->IsCollided(grass))
			if (a_player->IsCollided(grass))
			{
				if (a_player->IsCollideTop(grass)){
					a_player->SetIsOnGround(true);
					//Set the player on top of the platform
					a_player->SetY(grass->GetTop() + a_player->GetHeight() * 0.5f);

					//If the player is above the final platform he wins
					if (a_player->GetY() >= SCREEN_HEIGHT * 0.8f && a_player->GetX() >= SCREEN_WIDTH * 0.8f - 35.0f && a_player->GetX() <= SCREEN_WIDTH * 0.8f + 35.0f){
						a_player->SetIsWinner(true);
					}
				}

			}
			if (a_player->GetIsOnGround() && !a_player->GetOnLadder()){
				a_player->velocity = Vector2(0, 0);

				//if the player is colliding with the platform and not on a ladder, press spacebar to jump
				if (IsKeyDown(32))
				{
					a_player->velocity.y = 5;
					a_player->SetIsOnGround(false);
				}
			}
			//If not on the ground and not on a ladder
			else if (!a_player->GetIsOnGround() && !a_player->GetOnLadder()){
			//	a_player->velocity.y -= a_player->GetGravity();
			}
		}


		// if it's a barrel
		else if (dynamic_cast<Barrel*>(object) != 0){
			Barrel* barrels = dynamic_cast<Barrel*>(object);
			if (a_player->scoreCheck(barrels)){
				a_player->AddScore(10);
			}
			if (a_player->IsCollided(barrels)){
				//KILL THE PLAYER
				a_player->SetIsActive(false);
				//SWITCH TO DEATH STATE
			}
		}
	}


	//Draw Score
	DrawString(a_player->GetScoreAsString(), SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT - 35);
}

void GameState::BarrelLogic(Barrel* a_barrel, float a_deltaTime){
	
	//Barrel default to not on ladder
	a_barrel->SetOnLadder(false);
	a_barrel->SetIsOnGround(false);
	//Barrel default state is falling

	for (auto object : gameObjects)
	{
		
		//If Barrel is Colliding with a Ladder
		
		//If colliding with any platforms
		if (dynamic_cast<Platform*>(object) != 0)
		{
			Platform* grass = dynamic_cast<Platform*>(object);

			if (a_barrel->IsCollided(grass))
			{
				//If colliding with the top of the platform and barrel is not on a ladder
				if (a_barrel->IsCollideTop(grass))
				{
					a_barrel->SetIsOnGround(true);
					a_barrel->SetY(grass->GetTop() + a_barrel->GetHeight() * 0.5f);
				}
			}
			if (a_barrel->GetIsOnGround()){
				//left right move
				a_barrel->velocity.x = 1;
			}
			else if (!a_barrel->GetIsOnGround())
			{
				a_barrel->ySpeed = 150;
				a_barrel->velocity.y = -1;
				
			}
		}
	}
}