#pragma once
#include "Command.h"

class CommandFill : public Command
{
public:
	CommandFill();
	~CommandFill();
	virtual void undo();
	virtual void redo();
	virtual void execute(int, int, int);
};