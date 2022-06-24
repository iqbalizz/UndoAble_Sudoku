#include "Invoker.h"

Invoker::Invoker()
{
	history.clear();
}

void Invoker::push(Command* command)
{
	history.push_back(command);
}

Command& Invoker::pop()
{
	if (history.empty())
	{
		cout << endl << "You've ran out of undo/redo action" << endl;
	}
	else
	{
		Command* temp = move(history.back());
		CommandFill* a;

		history.pop_back();

		return *temp;
	}
}

bool Invoker::is_empty()
{
	return history.empty();
}

int Invoker::get_size()
{
	return history.size();
}