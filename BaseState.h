#pragma once

class StateMachine;

class BaseState
{
public:
	BaseState(void);
	~BaseState(void);

	virtual void Initialize() = 0;
	virtual void Update(float a_deltaTime, StateMachine* a_pSM) = 0;
	virtual void Draw() = 0;
	virtual void Destroy() = 0;

	static int SCORE;
};