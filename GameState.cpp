#include "GameState.h"
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
	player->SetPosition(200, 120);
	player->SetGravity(.2f);
	player->SetSpeed(175.0f);
	player->SetAccel(700.0f);
	player->SetSpriteID(CreateSprite("./images/p1_front.png", player->GetWidth(), player->GetHeight(), true));
	player->SetMoveKeys('A', 'D', 'W');
	player->SetMoveExtremes(0, SCREEN_WIDTH);
	MoveSprite(player->GetSpriteID(), player->GetX(), player->GetY());

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

		//initialize position
		grass->SetPosition(grassX, grassY);

		//New row?
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
	float ladderX = SCREEN_WIDTH * 0.5f;
	float ladderY = 105;

	for (int i = 0; i < 4; i++){

		Ladders* ladder = new Ladders();

		ladder->SetSize(70, 70);
		ladder->SetSpriteID(CreateSprite("./images/tiles/ladder_mid.png", ladder->GetWidth(), ladder->GetHeight(), true));

		ladder->SetPosition(ladderX, ladderY);

		ladderY += 70;

		gameObjects.push_back(ladder);
	}
}

void GameState::LoadBarrels(){
	float barrelX = SCREEN_WIDTH * 0.2f;
	float barrelY = SCREEN_HEIGHT * 0.5f;

	Barrel* barrels = new Barrel();

	barrels->SetSize(70, 70);
	barrels->SetSpriteID(CreateSprite("./images/dirtCaveRockLarge.png", barrels->GetWidth(), barrels->GetHeight(), true));
	
	barrels->SetGravity(.2f);
	barrels->SetSpeed(175.0f);
	barrels->SetAccel(700.0f);

	barrels->SetPosition(barrelX, barrelY);
	MoveSprite(barrels->GetSpriteID(), barrels->GetX(), barrels->GetY());

	gameObjects.push_back(barrels);
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
				//If colliding with the top of the platform
				if (a_player->isCollideTop(grass) && !a_player->GetOnLadder())
				{
					a_player->SetVelocity(0.0f);
					a_player->SetY(grass->GetTop() + a_player->GetHeight() * 0.5f);

					if (IsKeyDown(32) && !a_player->GetOnLadder())
					{
						// kick the player up
						a_player->SetVelocity(a_player->GetVelocity() + a_player->GetAccel() - (a_player->GetGravity()));
					}

				}
				else if (a_player->GetOnLadder())
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
				if (IsKeyDown('W')){
					a_player->SetOnLadder(true);
					a_player->SetVelocity(0.0f);
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
		if (dynamic_cast<Ladders*>(object) != 0){
			Ladders* ladder = dynamic_cast<Ladders*>(object);
			if (a_barrel->isCollided(ladder)){
				a_barrel->SetOnLadder(true);
				a_barrel->SetVelocity(0.0f);
				a_barrel->SetY(a_barrel->GetY() - (75 * a_deltaTime));
			}
		}
		else{
			a_barrel->SetOnLadder(false);
		}

		if (dynamic_cast<Platform*>(object) != 0){
			Platform* grass = dynamic_cast<Platform*>(object);
			//if (a_barrel->isCollideTop(grass) && !a_barrel->GetOnLadder())
			//{
			//	a_barrel->SetVelocity(0.0f);
			//	a_barrel->SetY(grass->GetTop() + a_barrel->GetHeight() * 0.5f);

			//}
			/*else if (a_barrel->GetOnLadder())
			{
				a_barrel->SetVelocity(0.0f);
				a_barrel->SetY(grass->GetBottom() - a_barrel->GetHeight() * 0.5f);
			}*/
		}

		else
		{
			a_barrel->SetVelocity((a_barrel->GetVelocity() - (a_barrel->GetGravity())));
		}
	}
}