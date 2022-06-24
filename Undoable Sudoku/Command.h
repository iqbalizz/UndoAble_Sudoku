#pragma once
#include "Board.h"

class Command
{
protected:
	int query[3]{};
	Board* board{};
	string type = "";
public:
	Command();
	~Command() = default;
	virtual void undo() {}
	virtual void redo() {}
	virtual void execute() {}
	void set_board(Board*);
	int get_query(int);
	string get_type();
};