#include "CommandFill.h"

CommandFill::CommandFill()
{
	type = "fill";
}

void CommandFill::undo()
{
	board->deleteCell(query[0], query[1]);
}

void CommandFill::redo()
{
	board->fillCell(query[0], query[1], query[2]);
}

void CommandFill::execute(int x, int y, int value)
{
	query[0] = x;
	query[1] = y;
	query[2] = value;
	board->fillCell(query[0], query[1], query[2]);
}