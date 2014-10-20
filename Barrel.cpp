#include "Barrel.h"


Barrel::Barrel()
{
	SetVelocity(0.0f);
	onLadder = false;
}


Barrel::~Barrel()
{
}

void Barrel::Draw(){
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}
void Barrel::Update(float a_deltaTime){
	// change in vertical
	ySpeed = velocity * a_deltaTime;
	y += ySpeed;

	if (x < (leftExtreme + width * .5f)){
		x = (leftExtreme + width * .5f);
		speed *= -1;
	}
	if (x > (rightExtreme - width * .5f)){
		x = (rightExtreme - width * .5f);
		speed *= -1;
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

void Barrel::SetAccel(float a_acceleration){
	acceleration = a_acceleration;
}
float Barrel::GetAccel(){
	return acceleration;
}

void Barrel::SetVelocity(float a_velocity){
	velocity = a_velocity;
}
float Barrel::GetVelocity(){
	return velocity;
}

void Barrel::SetGravity(float a_gravity){
	gravity = a_gravity;
}
float Barrel::GetGravity(){
	return gravity;
}

bool Barrel::isCollideTop(Entity* other){
	if (GetBottom() - ySpeed >= other->GetTop()){
		return true;
	}
	else{
		return false;
	}
}