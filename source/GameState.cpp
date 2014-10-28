#include "GameState.h"
#include "DeathState.h"
#include "WinnerState.h"
#include "AIE.h"
#include "StateMachine.h"
#include "Highscores.h"
#include "Leaderboard.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

int BaseState::SCORE;

std::vector<Entity*> GameState::gameObjects;

GameState::GameState(void)
{
	BaseState::SCORE = 0;
}


GameState::~GameState(void)
{
}

void GameState::Initialize()
{
	//Load Game Objects
	gameObjects.erase(gameObjects.begin(), gameObjects.end());

	LoadLadders();
	LoadPlayer();
	LoadGrass();
	LoadBarrels();

	Highscores scores;
	scores.LoadScores();
	if (scores.IsEmpty()){
		highscore = 0;
	}
	else{
		scores.SortScores();
		highscore = *scores.GetScores().begin();
	}
}

void GameState::Update(float a_deltaTime, StateMachine* a_pSM)
{
	//Esc
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
				Leaderboard* leaderboard = new Leaderboard();
				leaderboard->SetPlayerScore(BaseState::SCORE);
				BaseState* lastState = a_pSM->SwitchState(leaderboard);
				delete lastState;
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

	//Draw Score
	sprintf(p1Score, "%05d", BaseState::SCORE);
	DrawString(p1Score, SCREEN_WIDTH * 0.15f, SCREEN_HEIGHT - 35);
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
	player->SetXSpeed(150.0f);
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
	float ladderY = 105;
	
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
	float barrelY = SCREEN_HEIGHT * 0.7f;
	int barrelVelocity = -1;
	float barrelSpeed = 20.f;

	unsigned int spriteID = CreateSprite("./images/dirtCaveRockLarge.png", 40, 40, true);

	for (int i = 0; i < 3; i++){
		if (i == 1){
			barrelX = SCREEN_WIDTH * 0.3f;
			barrelY = SCREEN_HEIGHT * 0.43f;
			barrelVelocity = -1;
		}
		else if (i == 2){
			barrelX = SCREEN_WIDTH * 0.6f;
			barrelY = SCREEN_HEIGHT * 0.12f;
		}
		else
		{
			barrelY = SCREEN_HEIGHT * 0.75f;
			barrelVelocity = 1;
		}
		Barrel* barrels = new Barrel();

		barrels->SetSize(40, 40);
		barrels->SetSpriteID(spriteID);

		barrels->SetSpeed(barrelSpeed);

		barrels->SetPosition(barrelX, barrelY);
		barrels->velocity.x = barrelVelocity;
		barrels->SetMoveExtremes(0, SCREEN_WIDTH);

		gameObjects.push_back(barrels);
	}
}


void GameState::PlayerLogic(Player* a_player, float a_deltaTime)
{
	a_player->velocity.y -= a_player->GetGravity();
	a_player->SetOnLadder(false);
	a_player->SetIsOnGround(false);

	for (auto object : gameObjects)
	{
		// If the current object is a ladder
		if (dynamic_cast<Ladders*>(object) != 0){

			Ladders* ladder = dynamic_cast<Ladders*>(object);

			//If colliding with any ladders
			if (a_player->IsCollided(ladder))
			{
				a_player->SetOnLadder(true);
			}
			else if (!a_player->GetOnLadder()){
				a_player->SetOnLadder(false);
			}
		}

		// If the current object is a platform
		if (dynamic_cast<Platform*>(object) != 0)
		{
			Platform* grass = dynamic_cast<Platform*>(object);

			//if the player is not colliding with any platforms
			if (a_player->IsCollided(grass) && !a_player->GetOnLadder())
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
		}

		// if it's a barrel
		else if (dynamic_cast<Barrel*>(object) != 0){
			Barrel* barrels = dynamic_cast<Barrel*>(object);
			if (a_player->scoreCheck(barrels)){
				a_player->AddScore(10);
				BaseState::SCORE = a_player->GetScore();
			}
			if (a_player->IsCollided(barrels)){
				//KILL THE PLAYER
				a_player->SetIsActive(false);
				//SWITCH TO DEATH STATE
			}
		}
	}

	if (a_player->GetOnLadder())
	{
		a_player->SetIsOnGround(false);
	}

	//Ladder Movement
	if (a_player->GetOnLadder()){
		a_player->velocity = Vector2(0, 0);
		if (IsKeyDown('W')){
			a_player->velocity.y = 1;
		}
		if (IsKeyDown('S')){
			a_player->velocity.y = -1;
		}
	}

	//Jumping
	if (a_player->GetIsOnGround() && !a_player->GetOnLadder()){
		a_player->velocity = Vector2(0, 0);

		//if the player is colliding with the platform and not on a ladder, press spacebar to jump
		if (IsKeyDown(32))
		{
			a_player->velocity.y = 5;
			a_player->SetIsOnGround(false);
		}
	}
}

void GameState::BarrelLogic(Barrel* a_barrel, float a_deltaTime){
	
	//Barrel default to not on ladder
	a_barrel->SetOnLadder(false);
	a_barrel->SetIsOnGround(false);

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
			else if (!a_barrel->GetIsOnGround())
			{
				a_barrel->ySpeed = 150;
				a_barrel->velocity.y = -.2;
			}
		}
	}
}