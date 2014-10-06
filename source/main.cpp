#include "AIE.h"
#include <iostream>

bool CheckCollision(float x1, float y1, float x2, float y2);

struct Platform1 {
	unsigned int spriteID;
	float XPos;
	float YPos;
	int width;
	int height;
	unsigned int moveUp;
	unsigned int moveDown;
	unsigned int topBorder;
	unsigned int bottomBorder;

	void SetSize(int a_width, int a_height){
		width = a_width;
		height = a_height;
	}

	void SetMoveKeys(unsigned int a_moveUp, unsigned int a_moveDown){
		moveUp = a_moveUp;
		moveDown = a_moveDown;
	}

	void SetPosition(float a_x, float a_y){
		XPos = a_x;
		YPos = a_y;
	}

	float GetTop(){
		return YPos + (height / 2);
	}
	float GetBottom(){
		return YPos - (height / 2);
	}
	float GetLeft(){
		return XPos - (width / 2);
	}
	float GetRight(){
		return XPos + (width / 2);
	}
};

struct Player1 {
	unsigned int spriteID;
	float xPos;
	float yPos;
	float gravity;
	int width;
	int height;
	unsigned int moveUp;
	unsigned int moveDown;
	unsigned int jump;
	unsigned int topBorder;
	unsigned int bottomBorder;

	void SetSize(int a_width, int a_height){
		width = a_width;
		height = a_height;
	}

	void SetMoveKeys(unsigned int a_moveUp, unsigned int a_moveDown, unsigned a_jump){
		moveUp = a_moveUp;
		moveDown = a_moveDown;
		jump = a_jump;
	}

	void SetPosition(float a_x, float a_y){
		xPos = a_x;
		yPos = a_y;
	}
};

Platform1 grass;
Player1 player1;

int main(int argc, char* argv[])
{
	Initialise(800, 600, false, "JumpMan");

	SetBackgroundColour(SColour(0, 0, 0, 255));

	//Initialize platform
	grass.SetSize(70, 70);
	grass.SetPosition(400, 0);
	grass.spriteID = CreateSprite("./images/tiles/grassHalf.png", grass.width, grass.height, true);
	MoveSprite(grass.spriteID, grass.XPos, grass.YPos);

	//Player 1
	player1.SetSize(66, 92);
	player1.SetPosition(400, 200);
	player1.gravity = 150.f;
	player1.spriteID = CreateSprite("./images/p1_front.png", player1.width, player1.height, true);
	player1.SetMoveKeys('A', 'D', 'W');
	MoveSprite(player1.spriteID, player1.xPos, player1.yPos);

	//Game Loop
	do
	{

		float deltaT = GetDeltaTime();

		if (IsKeyDown(player1.moveUp)){
			player1.xPos -= 50.f * deltaT;
		}

		if (IsKeyDown(player1.moveDown)){
			player1.xPos += 50.f * deltaT;
		}


		MoveSprite(player1.spriteID, player1.xPos, player1.yPos);
		DrawSprite(player1.spriteID);
		DrawSprite(grass.spriteID);
		ClearScreen();

	} while (!FrameworkUpdate());

	Shutdown();

	return 0;
}