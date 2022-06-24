#pragma once
#include "Command.h"
#include "CommandFill.h"
#include "CommandDelete.h"
using namespace std;

class Invoker
{
private:
	vector<Command*> history;
public:
	Invoker();
	~Invoker() = default;
	void push(Command*);
	Command& pop();
	bool is_empty();
	int get_size();
};