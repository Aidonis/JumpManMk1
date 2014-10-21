#include "Platform.h"


Platform::Platform()
{
	SetSize(70, 70);
	SetSpriteID(CreateSprite("./images/tiles/grassHalfMid.png", width, height, true));
}

void Platform::Draw(){
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}

void Platform::Update(float a_deltaTime){

}

Platform::~Platform()
{
}
