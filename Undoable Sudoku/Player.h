#pragma once
#include <iostream>
using namespace std;

class Player
{
private:
	int score;
public:
	Player();
	~Player() = default;
	void set_score(int);
	int get_score();
};