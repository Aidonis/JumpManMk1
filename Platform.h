#pragma once
#include "AIE.h"
class Platform
{
public:
	Platform();
	~Platform();

	void SetSize(float a_width, float a_height);
	void SetPosition(float a_x, float a_y);

	void SetWidth(float a_width);
	float GetWidth();

	void SetHeight(float a_height);
	float GetHeight();

	void SetX(float a_x);
	float GetX();

	void SetY(float a_y);
	float GetY();

	void SetSpriteID(unsigned int a_spriteID);
	unsigned int GetSpriteID();


	float GetTop();
	float GetBottom();
	float GetLeft();
	float GetRight();

	void Draw();
private:
	unsigned int spriteID;
	float XPos;
	float YPos;
	float width;
	float height;

};

