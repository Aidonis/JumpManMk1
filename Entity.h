#pragma once

#ifndef _ENTITY_H_
#define _ENTITY_H_

class Entity
{
public:
	Entity();

	void SetSize(float width, float height);
	void SetPosition(float x, float y);

	virtual void Update(float a_deltaTime) = 0;
	virtual void Draw() = 0;

	void SetSpriteID(unsigned int a_spriteID);
	unsigned GetSpriteID();

	void SetWidth(float a_width);
	void SetHeight(float a_height);

	float GetWidth();
	float GetHeight();

	void SetX(float x);
	void SetY(float y);

	float GetX();
	float GetY();

	float GetBottom();
	float GetTop();
	float GetLeft();
	float GetRight();

	void SetCollisionDx(float a_dx);
	float GetCollisionDx();

	bool isCollided(Entity* other);
	virtual bool isCollideTop(Entity* other);

	bool isOnLadder;

	~Entity();

protected:

	unsigned int spriteID;

	float width;
	float height;

	float x;
	float y;

	float collisionDx;

};

#endif _ENTITY_H_