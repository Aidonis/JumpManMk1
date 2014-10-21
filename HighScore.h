#pragma once

#include <list>

class HighScore
{
public:
	HighScore();
	~HighScore();

	void LoadScores();
	void SaveScores();
	void AddScore(int a_score);
	bool IsEmpty();

	const std::list<unsigned int> GetScores();

private:
	std::list<unsigned int> scores;
};

