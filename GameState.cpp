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
	player->SetPosition(400, 200);
	player->SetGravity(.5f);
	player->SetSpeed(50.f);
	player->SetSpriteID(CreateSprite("./images/p1_front.png", player->GetWidth(), player->GetHeight(), true));
	player->SetMoveKeys('A', 'D', 'W');
	player->SetMoveExtremes(0, SCREEN_WIDTH);
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

		//Increment position
		grassX += grass->GetWidth();

		//Add to array
		gameObjects.push_back(grass);
	}
}

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
			else{
				return false;
			}
		}
	}
}

void GameState::PlayerLogic(Player* a_player, float a_deltaTime)
{
	//How to jump
	for (auto object : gameObjects)
	{
		if (dynamic_cast<Platform*>(object) != 0)
		{
			Platform* grass = dynamic_cast<Platform*>(object);
			if (IsGrounded(a_player))
			{

				// y velocity
				a_player->SetVelocity(0.0f);
				a_player->SetY(grass->GetTop() + a_player->GetHeight() * 0.5f);

				float jumpAccel = 800.0f;

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


	//a_player->Update(a_deltaTime);
	//a_player->Draw();
}