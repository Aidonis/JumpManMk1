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
	Player* player = new Player();

	//Player 1
	player->SetSize(60, 80);
	player->SetPosition(200, 390);
	player->SetGravity(.1f);
	player->SetSpeed(150.0f);
	player->SetSpriteID(CreateSprite("./images/p1_front.png", player->GetWidth(), player->GetHeight(), true));
	player->SetMoveKeys('A', 'D', 'W');
	player->SetMoveExtremes(0, SCREEN_WIDTH);
	player->SetAccel(800.0f);
	MoveSprite(player->GetSpriteID(), player->GetX(), player->GetY());

	gameObjects.push_back(player);

	//Load platforms
	LoadGrass();

}
void GameState::Update(float a_deltaTime, StateMachine* a_pSM)
{
	if (IsKeyDown(KEY_ESC))
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

void GameState::LoadGrass()
{
	//Initial position
	float grassX = SCREEN_WIDTH * .01f;
	float grassY = 0;

	for (int i = 0; i < TOTAL_PLATFORMS; i++){

		Platform* grass = new Platform();

		//Initialize Sprite
		grass->SetSize(70,70);
		grass->SetSpriteID(CreateSprite("./images/tiles/grassHalfMid.png", grass->GetWidth(), grass->GetHeight(), true));

		//initialize position
		grass->SetPosition(grassX, grassY);

		//New row?
		if (grassX > SCREEN_WIDTH * .5f){
			grassX = SCREEN_WIDTH * .01f;
			grassY += 250;
		}

		//Increment position
		grassX += grass->GetWidth();

		//Add to array
		gameObjects.push_back(grass);
	}
}

//BUGFIX::here is a simple circle collision algorithm with lots of comments
/*
will return true if player pointer is within .5 the height from .5 the grass pointer, otherwise will return false;
*/
//bool GameState::isCollided(Player* player, Platform* grass)
//{
//	//the collision formula is (x2 - x1)^2 + (y2 - y1)^2 <= (r1 + r2)^2
//	//derived from distance formula -> sqrt((x2 - x1)^2 + (y2 - y1)^2)
//	float x1{ player->GetX() };
//	float y1{ player->GetY() };
//	float r1{ player->GetHeight() * 0.5f };
//
//	float x2{ grass->GetX() };
//	float y2{ grass->GetY() };
//	float r2{ grass->GetHeight() * 0.5f };
//
//	//return the result
//	return std::pow(x2 - x1, 2) + pow(y2 - y1, 2) <= pow(r1 + r2, 2);
//}

//Instead of dissecting this algorithm I started from scratch.  I use a circle collider algorithm with .5 height as the radius.
bool GameState::IsGrounded(Player* a_player){
	
	for (auto object : gameObjects)
	{
		if (dynamic_cast<Platform*>(object) != 0)
		{
			Platform* grass = dynamic_cast<Platform*>(object);
			if (a_player->GetBottom() <= grass->GetTop())
			{
				return true;
			}
		}
	}
	return false;
}

void GameState::PlayerLogic(Player* a_player, float a_deltaTime)
{
	//How to jump
	for (auto object : gameObjects)
	{
		if (dynamic_cast<Platform*>(object) != 0)
		{
			Platform* grass = dynamic_cast<Platform*>(object);
		//BUGFIX::use my function here instead of yours for collision
			//if (IsGrounded(a_player))

			if (a_player->isCollided(grass))
			{

			
				// y velocity
				a_player->SetVelocity(0.0f);
				
				if (a_player->GetBottom() - (a_player->GetVelocity() * a_deltaTime) > grass->GetTop()){
					a_player->SetY(grass->GetTop() + a_player->GetHeight() * 0.5f);
				}

				if (IsKeyDown('W'))
				{
					// kick the player up
					a_player->SetVelocity(a_player->GetVelocity() + a_player->GetAccel() - (a_player->GetGravity()));
				}
			}
			else{

				a_player->SetVelocity((a_player->GetVelocity() - (a_player->GetGravity())));
			}
		}
	}
}
