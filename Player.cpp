#include "Player.h"


Player::Player()
{
	SetVelocity(0.f);
}

void Player::SetMoveKeys(unsigned int a_moveLeft, unsigned int a_moveRight, unsigned int a_jumpKey){
	moveLeft = a_moveLeft;
	moveRight = a_moveRight;
	jump = a_jumpKey;
}

void Player::SetMoveExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme){
	leftExtreme = a_leftExtreme;
	rightExtreme = a_rightExtreme;
}

void Player::SetVelocity(float a_velocity){
	velocity = a_velocity;
}

float Player::GetVelocity(){
	return velocity;
}

unsigned int Player::GetLeftKey(){
	return moveLeft;
}

unsigned int Player::GetRightKey(){
	return moveRight;
}

unsigned int Player::GetJumpKey(){
	return jump;
}

void Player::SetGravity(float a_gravity){
	gravity = a_gravity;
}

float Player::GetGravity(){
	return gravity;
}

void Player::SetSpeed(float a_speed){
	speed = a_speed;
}

float Player::GetSpeed(){
	return speed;
}



void Player::Draw(){
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}
void Player::Update(float a_deltaTime){

	// change in vertical
	y += velocity * a_deltaTime;

	// change in horizontal
	if (IsKeyDown(moveLeft)){
		x -= a_deltaTime * speed;
		if (x < (leftExtreme + width * .5f)){
			x = (leftExtreme + width * .5f);
		}
	}
	if (IsKeyDown(moveRight)){
		x += a_deltaTime * speed;
		if (x > (rightExtreme - width * .5f)){
			x = (rightExtreme - width * .5f);
		}
	}
	
}

Player::~Player()
{
}
