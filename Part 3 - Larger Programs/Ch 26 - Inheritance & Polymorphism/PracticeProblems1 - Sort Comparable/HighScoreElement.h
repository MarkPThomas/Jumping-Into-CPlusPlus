#pragma once
#include <string>

class HighScoreElement
{
public:
	HighScoreElement(std::string name, int score);

	std::string getName() const;
	int getScore() const;

	int compare(const HighScoreElement& other) const;
private:
	std::string _name;
	int _score;
};
