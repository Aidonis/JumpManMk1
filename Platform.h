#pragma once
class Platform
{
public:
	Platform();
	~Platform();

	void SetPosition(float a_x, float a_y);

	void SetWidth(float a_width);
	float GetWidth();

	void SetHeight(float a_height);
	float GetHeight();

	void SetX(float a_x);
	float GetX();

	void SetY(float a_y);
	float GetY();


private:
	unsigned int spriteID;
	float XPos;
	float YPos;
	float width;
	float height;

};

