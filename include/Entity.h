#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Vector2.h"

class Entity
{
public:
	Entity();

	void SetSize(float width, float height);
	void SetPosition(float x, float y);

	virtual void Update(float a_deltaTime) = 0;
	virtual void Draw() = 0;
	virtual void Move(float a_deltaTime);

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

	bool IsCollided(Entity* other);
	virtual bool IsCollideTop(Entity* other);

	Vector2 velocity;



	//variables
	float xSpeed;
	float ySpeed;

	~Entity();

protected:

	unsigned int spriteID;

	float width;
	float height;

	float x;
	float y;

	float yChange;
};

#endif _ENTITY_H_