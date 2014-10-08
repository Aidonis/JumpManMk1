#pragma once
#include "AIE.h"
#include "Entity.h"
class Platform : public Entity
{
public:
	Platform();
	~Platform();;

	virtual void Update(float a_deltaTime);
	virtual void Draw();

private:

};

