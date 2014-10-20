#include "GameState.h"
#include "DeathState.h"
#include "AIE.h"
#include "StateMachine.h"


extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

GameState::GameState(void)
{
}


GameState::~GameState(void)
{
}

void GameState::Initialize()
{
	//Load Game Objects
	LoadGrass();
	LoadLadders();
	LoadPlayer();
	LoadBarrels();

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
			PlayerLogic(dynamic_cast<Player*>(object), a_deltaTime);
			if (!dynamic_cast<Player*>(object)->GetIsActive()){
				a_pSM->SwitchState(new DeathState());
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
	player->SetPosition(100, 120);
	player->SetGravity(.2f);
	player->SetSpeed(200.0f);
	player->SetAccel(850.0f);
	player->SetSpriteID(CreateSprite("./images/p1_front.png", player->GetWidth(), player->GetHeight(), true));
	player->SetMoveKeys('A', 'D', 'W');
	player->SetMoveExtremes(0, SCREEN_WIDTH);

	gameObjects.push_back(player);
}

void GameState::LoadGrass()
{
	//Initial position
	float grassX = 35.f;
	float grassY = 35;
	unsigned int spriteID = CreateSprite("./images/tiles/grassHalfMid.png", 70, 70, true);


	for (int i = 0; i < TOTAL_PLATFORMS; i++){

		Platform* grass = new Platform();

		//Initialize Sprite
		grass->SetSize(70,70);
		grass->SetSpriteID(spriteID);

		//initialize position winning platform
		if (i > 28){
			grassX = SCREEN_WIDTH * 0.7f;
			grassY = SCREEN_HEIGHT * 0.8f;

		}
		grass->SetPosition(grassX, grassY);

		//New row
		if (grassX > SCREEN_WIDTH){
			grassX = -35;
			grassY += 250;
		}

		//Increment position
		grassX += grass->GetWidth();

		//Add to array
		gameObjects.push_back(grass);
	}
}

void GameState::LoadLadders()
{
	//Initial Ladder
	float ladderX = SCREEN_WIDTH * 0.8f;
	float ladderY = 145;
	
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
	float barrelSpeed = 50.f;

	unsigned int spriteID = CreateSprite("./images/dirtCaveRockLarge.png", 70, 70, true);

	for (int i = 0; i < 3; i++){
		if (i == 1){
			barrelY = SCREEN_HEIGHT * 0.5f;
			barrelX = SCREEN_WIDTH * 0.8f;
			barrelSpeed *= -1;
		}
		else if (i == 2){
			barrelX = SCREEN_WIDTH * 0.4f;
			barrelY = SCREEN_HEIGHT * 0.2f;
			barrelSpeed *= -1;
		}
		else
		{
			barrelY = SCREEN_HEIGHT * 0.8f;
		}
		Barrel* barrels = new Barrel();

		barrels->SetSize(70, 70);
		barrels->SetSpriteID(spriteID);

		barrels->SetGravity(.2f);
		barrels->SetSpeed(barrelSpeed);
		barrels->SetAccel(700.0f);

		barrels->SetPosition(barrelX, barrelY);
		barrels->SetMoveExtremes(0, SCREEN_WIDTH);
		MoveSprite(barrels->GetSpriteID(), barrels->GetX(), barrels->GetY());

		gameObjects.push_back(barrels);
	}
}

//bool GameState::IsGrounded(Player* a_player){
//	
//	for (auto object : gameObjects)
//	{
//		if (dynamic_cast<Platform*>(object) != 0)
//		{
//			Platform* grass = dynamic_cast<Platform*>(object);
//			if (a_player->GetBottom() <= grass->GetTop())
//			{
//				return true;
//			}
//		}
//	}
//	return false;
//}

void GameState::PlayerLogic(Player* a_player, float a_deltaTime)
{
	//How to jump
	for (auto object : gameObjects)
	{
		//If colliding with any platforms
		if (dynamic_cast<Platform*>(object) != 0)
		{
			Platform* grass = dynamic_cast<Platform*>(object);
	
			if (a_player->isCollided(grass))
			{
				//If the player is colliding with the top of the grass and not on a ladder
				//Set fall velocity to 0 and set player position above the platform
				if (a_player->isCollideTop(grass) && !a_player->GetOnLadder())
				{
					a_player->SetVelocity(0.0f);
					a_player->SetY(grass->GetTop() + a_player->GetHeight() * 0.5f);

					//if the player is colliding with the platform and not on a ladder, press spacebar to jump
					if (IsKeyDown(32) && !a_player->GetOnLadder())
					{
						//Set velocity to itself + acceleration - some gravity
						a_player->SetVelocity(a_player->GetVelocity() + a_player->GetAccel() - (a_player->GetGravity()));
					}

				}
				if (a_player->GetOnLadder())
				{
					a_player->SetVelocity(0.0f);
					a_player->SetY(grass->GetBottom() - a_player->GetHeight() * 0.5f);
				}
			}

			else
			{
				a_player->SetVelocity((a_player->GetVelocity() - (a_player->GetGravity())));
			}
		}
		//If Player is Colliding with a Ladder
		if (dynamic_cast<Ladders*>(object) != 0){

			Ladders* ladder = dynamic_cast<Ladders*>(object);

			if (a_player->isCollided(ladder)){
				a_player->SetVelocity(0.0f);
				if (IsKeyDown('W')){
					a_player->SetOnLadder(true);
					a_player->SetY(a_player->GetY() + (75 * a_deltaTime));
				}
				if (IsKeyDown('S')){
					a_player->SetOnLadder(true);
					a_player->SetY(a_player->GetY() - (75 * a_deltaTime));
				}
			}
		}
		else{
			a_player->SetOnLadder(false);
		}
	}
}

void GameState::BarrelLogic(Barrel* a_barrel, float a_deltaTime){
	for (auto object : gameObjects)
	{
		//If colliding with any platforms
		if (dynamic_cast<Platform*>(object) != 0)
		{
			Platform* grass = dynamic_cast<Platform*>(object);

			if (a_barrel->isCollided(grass))
			{
				//If colliding with the top of the platform and barrel is not on a ladder
				if (a_barrel->isCollideTop(grass))
				{
					//Set Y Velocity to 0 and Y position on top of platform
					a_barrel->SetVelocity(0.0f);
					a_barrel->SetY(grass->GetTop() + a_barrel->GetHeight() * 0.5f);
					a_barrel->SetX(a_barrel->GetX() + (a_barrel->GetSpeed() * a_deltaTime));
				}
			}

			else
			{
				a_barrel->SetVelocity((a_barrel->GetVelocity() - (a_barrel->GetGravity())));
			}
		}
		//If Player is Colliding with a Ladder
		if (dynamic_cast<Ladders*>(object) != 0){

			Ladders* ladder = dynamic_cast<Ladders*>(object);

			if (a_barrel->isCollided(ladder)){
					a_barrel->SetOnLadder(true);
			//		a_barrel->SetY(a_barrel->GetY() - (a_barrel->GetSpeed() * a_deltaTime));
			}
		}
		else{
			a_barrel->SetOnLadder(false);
		}

		if (dynamic_cast<Player*>(object) != 0){
			Player* player = dynamic_cast<Player*>(object);

			if (a_barrel->isCollided(player)){
				//KILL THE PLAYER
				player->SetIsActive(false);
				//SWITCH TO DEATH STATE
			}

		}
	}
}