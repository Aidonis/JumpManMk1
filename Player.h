#pragma once

#ifndef _PLAYER_H_
#define _PLAYER_H_

class Player
{
public:
	Player();
	~Player();

	void SetMoveKeys(unsigned int a_moveLeft, unsigned int a_moveRight, unsigned int a_jumpKey);
	void SetPosition(float a_x, float a_y);

	void SetSpeed(float speed);
	void GetSpeed();

	void SetWidth(float a_width);
	void GetWidth();

	void SetHeight(float a_height);
	void GetHeight();

	void SetX(float a_x);
	void GetX();

	void SetY(float a_y);
	void GetY();

	void SetSpriteID(unsigned int a_spriteID);
	void GetSpriteID();

private:
	unsigned int spriteID;
	float XPos;
	float YPos;
	float gravity;
	float width;
	float height;
	float speed;
	unsigned int moveLeft;
	unsigned int moveRight;
	unsigned int jump;

};

#endif //_PLAYER_H_