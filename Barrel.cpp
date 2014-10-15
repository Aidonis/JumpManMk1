#include "Barrel.h"


Barrel::Barrel()
{
}


Barrel::~Barrel()
{
}

void Barrel::Draw(){
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}
void Barrel::Update(float a_deltaTime){

}

void Barrel::SetSpeed(float a_speed){
	speed = a_speed;
}
float Barrel::GetSpeed(){
	return speed;
}

void Barrel::SetOnLadder(bool a_onLadder){
	onLadder = a_onLadder;
}
bool Barrel::GetOnLadder(){
	return false;
}