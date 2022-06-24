#include "CommandDelete.h"

CommandDelete::CommandDelete()
{
	type = "delete";
}

void CommandDelete::undo()
{
	board->fillCell(query[0], query[1], query[2]);
}

void CommandDelete::redo()
{
	board->deleteCell(query[0], query[1]);
}

void CommandDelete::execute(int x, int y)
{
	query[0] = x;
	query[1] = y;
	query[2] = board->getCellValue(x, y);
	board->deleteCell(query[0], query[1]);
}