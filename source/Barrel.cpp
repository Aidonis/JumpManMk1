#include "Barrel.h"
#include <iostream>

Barrel::Barrel()
{
	velocity = Vector2(0, 0);
	onLadder = false;
	onGround = false;
	ySpeed = 150.0f;
	xSpeed = 75.0f;
}


Barrel::~Barrel()
{
}

void Barrel::Draw(){
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}
void Barrel::Update(float a_deltaTime){
	Move(a_deltaTime);
}

void Barrel::Move(float a_deltaTime){
	yChange = ySpeed * velocity.y * a_deltaTime;
	y += yChange;

	x += xSpeed * velocity.x * a_deltaTime;

	if (x <= (leftExtreme + width * .5f)){
		x = (leftExtreme + width * .5f);
		velocity.x *= -1;
	}
	else if (x >= (rightExtreme - width * .5f)){
		x = (rightExtreme - width * .5f);
		velocity.x *= -1;
	}
}

void Barrel::SetSpeed(float a_speed){
	speed = a_speed;
}
float Barrel::GetSpeed(){
	return speed;
}

void Barrel::SetMoveExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme){
	leftExtreme = a_leftExtreme;
	rightExtreme = a_rightExtreme;
}

void Barrel::SetOnLadder(bool a_onLadder){
	onLadder = a_onLadder;
}
bool Barrel::GetOnLadder(){
	return false;
}

void Barrel::SetIsOnGround(bool a_grounded){
	onGround = a_grounded;
}
bool Barrel::GetIsOnGround(){
	return onGround;
}

bool Barrel::IsCollideTop(Entity* other){
	if (GetBottom() - yChange >= other->GetTop()){
		return true;
	}
	else{
		return false;
	}
}