#pragma once

#include "BaseState.h"
#include "Player.h"
#include "Platform.h"
#include "Ladders.h"
#include "Barrel.h"
#include <vector>

const int TOTAL_PLATFORMS = 30;

class GameState : public BaseState
{
public:
	GameState(void);
	~GameState(void);

	void Initialize();
	void Update(float a_deltaTime, StateMachine* a_pSM);
	void Draw();
	void Destroy();

private:
	void PlayerLogic(Player* a_player, float a_deltaTime);
	void BarrelLogic(Barrel* a_barrel, float a_deltaTime);
	void LoadGrass();
	void LoadLadders();
	void LoadPlayer();
	void LoadBarrels();

	int highscore;
	
	char p1Score[20];

private:
	static std::vector<Entity*> gameObjects;
};

