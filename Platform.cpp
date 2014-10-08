#include "Platform.h"


Platform::Platform()
{
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
