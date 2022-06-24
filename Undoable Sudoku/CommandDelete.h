#pragma once
#include "Command.h"

class CommandDelete : public Command
{
public:
	CommandDelete();
	~CommandDelete();
	virtual void undo();
	virtual void redo();
	virtual void execute(int, int);
};