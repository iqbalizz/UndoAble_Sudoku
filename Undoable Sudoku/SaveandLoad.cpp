#include "SaveandLoad.h"

SaveandLoad::SaveandLoad()
{
	namespace fs = filesystem;
	for (const auto&entry : fs::directory_iterator(path))
		file.push_back(entry.path().string());
}

void SaveandLoad::Save(Board* board, string name)
{
	string destination = path + name + ".txt";
	ofstream out(destination);
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9 ; j++)
		{
			out << board->getCellValue(i, j) << " ";
		}
		out << endl;
	}
	cout << endl << "Saved" << endl;
	cout << destination;
	out.close();
}

void SaveandLoad::Load(Board* board, string name)
{
	string loadFile = path + name + ".txt";
	ifstream inputFile(loadFile);
	Board tempBoard;

	if (!inputFile.is_open())
		cout << "Error opening loadfile!";

	int temp[9][9];

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			inputFile >> temp[i][j];
			board->setCell(i, j, temp[i][j]);
			tempBoard.setCell(i, j, temp[i][j]);
		}
	}

	tempBoard.solve();
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			board->setSolCell(i, j, tempBoard.getCellValue(i, j));
		}
	}
}

void SaveandLoad::show_save_list()
{
	for (string i : file)
	{
		cout << endl << file.back() << endl;
		file.pop_back();
	}
}