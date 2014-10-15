#include "Entity.h"
#include <math.h>

Entity::Entity()
{
	collisionDx = 0.0f;
	isOnLadder = false;
}

//bool Entity::isCollided(Entity* other){
//	return pow(x - other->GetX(), 2) + pow(y - other->GetY(), 2) <= pow(other->collisionDx + collisionDx, 2);
//}

//Box collision between entities
bool Entity::isCollided(Entity* other){
	if (GetLeft() > other->GetRight() ||
		GetRight() < other->GetLeft() ||
		GetTop() < other->GetBottom() ||
		GetBottom() > other->GetTop()){
		return false;
	}
}

//If the entity is colliding with the top, true
//Else entity is colliding with the bottom
bool Entity::isCollideTop(Entity* other){
	return false;
}

void Entity::SetCollisionDx(float a_Dx){
	collisionDx = a_Dx;
}

float Entity::GetCollisionDx(){
	return collisionDx;
}

void Entity::SetSize(float a_width, float a_height)
{
	width = a_width;
	height = a_height;
}

void Entity::SetPosition(float a_x, float a_y)
{
	x = a_x;
	y = a_y;
}

void Entity::SetSpriteID(unsigned int a_spriteID)
{
	spriteID = a_spriteID;
}

unsigned int Entity::GetSpriteID()
{
	return spriteID;
}

void Entity::SetWidth(float a_width)
{
	width = a_width;
}

void Entity::SetHeight(float a_height)
{
	height = a_height;
}

float Entity::GetWidth()
{
	return width;
}

float Entity::GetHeight()
{
	return height;
}

void Entity::SetX(float a_x)
{
	x = a_x;
}

void Entity::SetY(float a_y)
{
	y = a_y;
}

float Entity::GetX()
{
	return x;
}

float Entity::GetY()
{
	return y;
}

float Entity::GetTop(){
	return y + (height / 2);
}
float Entity::GetBottom(){
	return y - (height / 2);
}
float Entity::GetLeft(){
	return x - (width / 2);
}
float Entity::GetRight(){
	return x + (width / 2);
}

Entity::~Entity()
{
}