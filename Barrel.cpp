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
	ySpeed = velocity * .00016;
	y += ySpeed;
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