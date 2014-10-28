#include "Player.h"
#include <string>

Player::Player()
{
	//SetVelocity(0.f);
	onLadder = false;
	isActive = true;
	isWinner = false;
	onGround = false;

	SetPosition(100, 420);
	ySpeed = 200.0f;
	score = 0;
	AddScore(0);
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

void Player::SetIsOnGround(bool a_grounded){
	onGround = a_grounded;
}
bool Player::GetIsOnGround(){
	return onGround;
}

void Player::SetIsActive(float a_isActive){
	isActive = a_isActive;
}
bool Player::GetIsActive(){
	return isActive;
}

void Player::AddScore(unsigned int a_score){
	score += a_score;
	char buff[6];
	sprintf(buff, "%05d", score);
	strcpy(scoreAsString, buff);
}
int Player::GetScore(){
	return score;
}

char* Player::GetScoreAsString(){
	return scoreAsString;
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

void Player::SetXSpeed(float a_speed){
	xSpeed = a_speed;
}

float Player::GetXSpeed(){
	return xSpeed;
}

void Player::SetIsWinner(bool a_winner){
	isWinner = a_winner;
}
bool Player::GetIsWinner(){
	return isWinner;
}

//Check a collision box above the other object
bool Player::scoreCheck(Entity* other){
	if (GetLeft() > other->GetRight() ||
		GetRight() < other->GetLeft() ||
		GetBottom() < other->GetTop() ||
		GetTop() > other->GetTop() + (other->GetHeight() * 4)){
		return false;
	}
	else{
		return true;
	}
}

bool Player::IsCollideTop(Entity* other){
	if (GetBottom() - yChange >= other->GetTop()){
		return true;
	}
	else{
		return false;
	}
}

void Player::SetOnLadder(bool a_onLadder){
	onLadder = a_onLadder;
}
bool Player::GetOnLadder(){
	return onLadder;
}

void Player::Draw(){
	MoveSprite(spriteID, x, y);
	DrawSprite(spriteID);
}
void Player::Update(float a_deltaTime){

	//Speed * Velocity * Delta
	yChange = ySpeed * velocity.y * a_deltaTime;
	y += yChange;

	// change in horizontal
	if (IsKeyDown(moveLeft)){
		velocity.x = -1;
		x += a_deltaTime * xSpeed * velocity.x;
		if (x < (leftExtreme + width * .5f)){
			x = (leftExtreme + width * .5f);
		}
	}
	if (IsKeyDown(moveRight)){
		velocity.x = 1;
		x += a_deltaTime * xSpeed * velocity.x;
		if (x > (rightExtreme - width * .5f)){
			x = (rightExtreme - width * .5f);
		}
	}
	
}

Player::~Player()
{
}
