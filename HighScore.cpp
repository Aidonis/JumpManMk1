#include "HighScore.h"
#include <fstream>

HighScore::HighScore()
{
}


HighScore::~HighScore()
{
}

void HighScore::AddScore(int a_score){
	scores.push_back(a_score);
}

bool HighScore::IsEmpty(){
	return (scores.size() == 0);
}

const std::list<unsigned int> HighScore::GetScores(){
	return scores;
}

void HighScore::LoadScores(){
	std::fstream fs;
	fs.open("leaderboard.txt", std::fstream::in);
	if (fs.is_open()){
		while (!fs.eof()){
			int score = 0;
			fs >> score;
			if (fs.good()){
				scores.push_back(score);
			}
		}
		fs.close();
	}
}