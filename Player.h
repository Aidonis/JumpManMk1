#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "AIE.h"
#include "Entity.h"

class Player : public Entity
{
public:
	Player();
	~Player();

	void SetMoveKeys(unsigned int a_moveLeft, unsigned int a_moveRight, unsigned int a_jumpKey);
	void SetMoveExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme);

	unsigned int GetLeftKey();
	unsigned int GetRightKey();
	unsigned int GetJumpKey();

	void SetXSpeed(float speed);
	float GetXSpeed();

	void SetGravity(float a_gravity);
	float GetGravity();

	void SetIsActive(float a_isActive);
	bool GetIsActive();

	virtual void Update(float a_deltaTime);
	virtual void Draw();

	bool scoreCheck(Entity* other);

	void SetOnLadder(bool a_onLadder);
	bool GetOnLadder();

	void SetIsWinner(bool a_winner);
	bool GetIsWinner();

	int GetScore();
	void AddScore(unsigned int a_scoreValue);
	char* GetScoreAsString();

	void SetIsOnGround(bool a_grounded);
	bool GetIsOnGround();

	virtual bool IsCollideTop(Entity* other);

private:

	float gravity;

	//flags
	bool onLadder;
	bool isActive;
	bool isWinner;
	bool onGround;


	unsigned int score;
	char scoreAsString[6];

	unsigned int moveLeft;
	unsigned int moveRight;
	unsigned int jump;

	unsigned int leftExtreme;
	unsigned int rightExtreme;

};

#endif //_PLAYER_H_