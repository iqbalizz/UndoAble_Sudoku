#pragma once
#include "Board.h"

class SaveandLoad
{
private:
	string const path = "saveandload/";
	vector <string> file;
public:
	SaveandLoad();
	void Save(Board*, string);
	void Load(Board*, string);
	void show_save_list();
};