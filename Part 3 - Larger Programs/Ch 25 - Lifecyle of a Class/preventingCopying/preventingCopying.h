#pragma once
class Player
{
public:
	Player();
	~Player();

private:
	// Prohibited, by declaring but not defining these methods, the compiler will not generate them for us.
	Player& operator=(const Player& other);
	Player(const Player& other);
};