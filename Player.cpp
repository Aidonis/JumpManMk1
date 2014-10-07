#include "Player.h"


Player::Player()
{
	jumpCD = false;
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

void Player::SetMoveExtremes(unsigned int a_leftExtreme, unsigned int a_rightExtreme){
	leftExtreme = a_leftExtreme;
	rightExtreme = a_rightExtreme;
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
void Player::SetSpeed(float a_speed){
	speed = a_speed;
}
float Player::GetSpeed(){
	return speed;
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

void Player::Draw(){
	MoveSprite(spriteID, XPos, YPos);
	DrawSprite(spriteID);
}
void Player::Update(float a_deltaTime){
	if (IsKeyDown(moveLeft)){
		XPos -= a_deltaTime * speed;
		if (XPos < (leftExtreme + width * .5f)){
			XPos = (leftExtreme + width * .5f);
		}
	}
	if (IsKeyDown(moveRight)){
		XPos += a_deltaTime * speed;
		if (XPos > (rightExtreme - width * .5f)){
			XPos = (rightExtreme - width * .5f);
		}
	}
	if (YPos == 80.f){
		if (IsKeyDown(jump)){
			YPos += a_deltaTime * speed;
		}
	}
	YPos -= gravity * a_deltaTime;
}

Player::~Player()
{
}
