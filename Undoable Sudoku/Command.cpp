#include "Command.h"

Command::Command()
{
	type = "base";
}

string Command::get_type()
{
	return type;
}

void Command::set_board(Board* board)
{
	this->board = board;
}

int Command::get_query(int val)
{
	return query[val];
}