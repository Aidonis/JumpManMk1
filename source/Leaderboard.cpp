#include "Leaderboard.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

Leaderboard::Leaderboard()
{
}


Leaderboard::~Leaderboard()
{
}


void Leaderboard::Initialize()
{
	scores.LoadScores();
	scores.SortScores();
}

void Leaderboard::Update(float a_timeStep, StateMachine* a_SMP)
{
	//256 = esc key
	if (IsKeyDown(256))
	{
		BaseState* lastState = a_SMP->PopState();
		delete lastState;
		return;
	}
}

void Leaderboard::Draw(){
	char score[20];
	int y = SCREEN_HEIGHT - 100;
	int count = 0;

	DrawString("HIGH_SCORE", SCREEN_WIDTH *0.3f, SCREEN_HEIGHT * 0.8f);

	const std::list<int> scoreList = scores.GetScores();
	for (std::list<int>::const_iterator it = scoreList.begin(); it != scoreList.end(); it++)
	{
		sprintf(score, "%05d", *it);

		DrawString(score, SCREEN_WIDTH >> 1, y);
		y -= 40;
		count++;
		if (count >= 5)
			break;
	}
}

void Leaderboard::Destroy(){
	scores.SaveScores();
}

void Leaderboard::SetPlayerScore(int a_score){
	scores.AddScore(a_score);
}