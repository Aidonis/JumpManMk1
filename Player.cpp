#include "Player.h"


Player::Player()
{
}

void Player::SetSize(float a_width, float a_height){
	width = a_width;
	height = a_height;
}

void Player::SetMoveKeys(unsigned int a_moveLeft, unsigned int a_moveRight, unsigned int a_jumpKey){
	moveLeft = a_moveLeft;
	moveRight = a_moveRight;
	jump = a_jumpKey;
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

void Player::SetPosition(float a_x, float a_y){
	XPos = a_x;
	YPos = a_y;
}
void Player::SetWidth(float a_width){
	width = a_width;
}
float Player::GetWidth(){
	return width;
}
void Player::SetHeight(float a_height){
	height = a_height;
}
float Player::GetHeight(){
	return height;
}
void Player::SetX(float a_x){
	XPos = a_x;
}
float Player::GetX(){
	return XPos;
}
void Player::SetY(float a_y){
	YPos = a_y;
}
float Player::GetY(){
	return YPos;
}

void Player::SetGravity(float a_gravity){
	gravity = a_gravity;
}
float Player::GetGravity(){
	return gravity;
}

void Player::SetSpriteID(unsigned int a_spriteID){
	spriteID = a_spriteID;
}
unsigned int Player::GetSpriteID(){
	return spriteID;
}

float Player::GetTop(){
	return YPos + (height / 2);
}
float Player::GetBottom(){
	return YPos - (height / 2);
}
float Player::GetLeft(){
	return XPos - (width / 2);
}
float Player::GetRight(){
	return XPos + (width / 2);
}

Player::~Player()
{
}
