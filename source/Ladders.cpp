#include "Ladders.h"


Ladders::Ladders()
{
}

void Ladders::Draw(){
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}

void Ladders::Update(float a_deltaTime){

}

Ladders::~Ladders()
{
}
