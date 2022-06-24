#include "Player.h"

Player::Player()
{
	score = 0;
}

void Player::set_score(int score)
{
	this->score = score;
}

int Player::get_score()
{
	return score;
}