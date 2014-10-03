#include "AIE.h"
#include <iostream>

bool CheckCollision(float x1, float y1, float x2, float y2, float distance);

struct Platform {
	unsigned int spriteID;
	float xPos;
	float yPos;
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
		xPos = a_x;
		yPos = a_y;
	}
};

struct Player {
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

Platform grass;
Player player1;

int main(int argc, char* argv[])
{
	Initialise(800, 600, false, "JumpMan");

	SetBackgroundColour(SColour(0, 0, 0, 255));

	//Initialize platform
	grass.SetSize(70, 70);
	grass.SetPosition(400, 0);
	grass.spriteID = CreateSprite("./images/tiles/grassHalf.png", grass.width, grass.height, true);
	MoveSprite(grass.spriteID, grass.xPos, grass.yPos);

	//Player 1
	player1.SetSize(66, 92);
	player1.SetPosition(400, 200);
	player1.gravity = 50.f;
	player1.spriteID = CreateSprite("./images/p1_front.png", player1.width, player1.height, true);
	player1.SetMoveKeys('A', 'D', 'W');
	MoveSprite(player1.spriteID, player1.xPos, player1.yPos);

	//Game Loop
	do
	{

		float deltaT = GetDeltaTime();

		if (IsKeyDown(player1.moveUp)){
			player1.xPos -= 5.f;
		}

		if (IsKeyDown(player1.moveDown)){
			player1.xPos += 5.f;
		}

		if (player1.yPos - (player1.height / 2) == grass.yPos + (grass.height / 2)){
			if (IsKeyDown(player1.jump)){
				player1.yPos += 65.f * deltaT;
			}
		}

		if (!CheckCollision(grass.xPos, grass.yPos, player1.xPos, player1.yPos, 92)){
			player1.yPos -= player1.gravity * deltaT;

		}
		else{
			player1.yPos = grass.yPos + (grass.height / 2) + (player1.height / 2);
		}
		MoveSprite(player1.spriteID, player1.xPos, player1.yPos);
		DrawSprite(player1.spriteID);
		DrawSprite(grass.spriteID);
		ClearScreen();

	} while (!FrameworkUpdate());

	Shutdown();

	return 0;
}

bool CheckCollision(float x1, float y1, float x2, float y2, float distance){
	float d = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
	if (d < distance)
		return true;
	else

		return false;
}