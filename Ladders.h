#pragma once
#include "Entity.h"
#include "AIE.h"

class Ladders :
	public Entity
{
public:
	Ladders();
	~Ladders();

	virtual void Update(float a_deltaTime);
	virtual void Draw();

};

