#ifndef _LEADERBOARD_H_
#define _LEADERBOARD_H_
#include "BaseState.h"
#include "Highscores.h"
#include "AIE.h"
#include "StateMachine.h"

class Leaderboard :
	public BaseState
{
public:
	Leaderboard();
	~Leaderboard();

	void Initialize();
	void Update(float a_deltaTime, StateMachine* a_pSM);
	void Draw();
	void Destroy();

	void SetPlayerScore(int a_score);

private:
	Highscores scores;
	char p1Score[20];
};

#endif //_LEADERBOARD_H_