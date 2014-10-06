#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "AIE.h"

class Player
{
public:
	Player();
	~Player();

	void SetSize(float a_width, float a_height);
	void SetMoveKeys(unsigned int a_moveLeft, unsigned int a_moveRight, unsigned int a_jumpKey);
	void SetPosition(float a_x, float a_y);
	void SetMoveExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme);

	unsigned int GetLeftKey();
	unsigned int GetRightKey();
	unsigned int GetJumpKey();

	void SetSpeed(float speed);
	float GetSpeed();

	void SetWidth(float a_width);
	float GetWidth();

	void SetHeight(float a_height);
	float GetHeight();

	void SetX(float a_x);
	float GetX();

	void SetY(float a_y);
	float GetY();

	void SetYSpeed(float a_ySpeed);
	float GetYSpeed();

	void SetGravity(float a_gravity);
	float GetGravity();

	void SetSpriteID(unsigned int a_spriteID);
	unsigned int GetSpriteID();

	float GetTop();
	float GetBottom();
	float GetLeft();
	float GetRight();

	void Draw();
	void Update(float a_deltaTime);

private:
	unsigned int spriteID;
	float XPos;
	float YPos;

	float YSpeed;

	float gravity;
	float width;
	float height;
	float speed;

	unsigned int moveLeft;
	unsigned int moveRight;
	unsigned int jump;

	unsigned int leftExtreme;
	unsigned int rightExtreme;

	bool jumpCD;

};

#endif //_PLAYER_H_