#include "GameManager.h"

GameManager::GameManager(Board* board, Player* player)
{
	this->board = board;
	this->player = player;
}

void GameManager::check_wrong_cell()
{
	struct wrongCell
	{
		int x;
		int y;
		int value;
	};

	vector <wrongCell> Cell;

	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (this->board->getCellValue(i, j) != this->board->getCellSolValue(i, j)) {
				Cell.push_back({ i, j, this->board->getCellValue(i,j) });
			}
		}
	}

	cout << endl
		<< "Every cells correct except: " << endl;
	for (const auto& arr : Cell)
	{
		cout << "Cell "
			<< "[" << arr.x << "]"
			<< "[" << arr.y << "] : ";
		if (arr.value == 0)
		{
			cout << "Still Empty";
		}
		else {
			cout << arr.value;
		}
		cout << endl;
		Cell.pop_back();
	}
}

void GameManager::save_file()
{
	SaveandLoad save;
	string filename;
	save.show_save_list();
	cout << endl << "Save as: "; cin >> filename;
	save.Save(board, filename);
}

void GameManager::load_file()
{
	SaveandLoad load;
	string filename;
	load.show_save_list();
	cout << endl << "Load from: "; cin >> filename;
	load.Load(board, filename);
}

void GameManager::play()
{
	cout << endl << "How many blank cells: ";
	int r = 0; cin >> r;
	this->board->difficulty(r);
	board->generate();
	continue_game();
}

void GameManager::continue_game()
{
	int userMenu = 10;
	int x, y, z;
	while (userMenu != 0)
	{
		if (this->board->isSolRight())
		{
			cout << endl << "Congratulations!!" << endl
				<< "you have finished the sudoku with "
				<< (undo.get_size() + redo.get_size())
				<< " action!" << endl << endl;
			break;
		}
		board->draw();
		cout << endl
		<< "1. Fill Cell" << endl
		<< "2. Delete Cell" << endl
		<< "3. Undo Turn " << endl
		<< "4. Redo Turn " << endl
		<< "5. Check Wrong Cell" << endl
		<< "0. Exit Game" << endl
		<< "Pilihan : "; cin >> userMenu;
		switch (userMenu)
		{
		case 1:
			cout << "X     :"; cin >> x;
			cout << "Y     :"; cin >> y;
			cout << "Angka :"; cin >> z;
			fill_cell(x, y, z);
			break;
		case 2:
			cout << "X     :"; cin >> x;
			cout << "Y     :"; cin >> y;
			delete_cell(x, y);
			break;
		case 3:
			undo_act();
			break;
		case 4:
			redo_act();
			break;
		case 5:
			check_wrong_cell();
		default:;
		}
	}
}

void GameManager::undo_act()
{
	Command* copy;
	copy = &undo.pop();
	cout << copy->get_type();
	redo.push(copy);
	copy->undo();

	cout << "Undo on ["
		<< copy->get_query(0) << "]["
		<< copy->get_query(1) << "]" << endl;
}

void GameManager::redo_act()
{
	Command* copy;
	copy = &redo.pop();
	undo.push(copy);
	copy->redo();
	cout << "Redo on ["
		<< copy->get_query(0) << "]["
		<< copy->get_query(1) << "]" << endl;
}

void GameManager::fill_cell(int x, int y, int value)
{
	CommandFill* copy = new CommandFill;
	copy->set_board(board);
	if (board->getCellValue(x, y) != 0)
	{
		cout << endl << "Cell already has value!" << endl;
	}
	else
	{
		copy->execute(x, y, value);
	}
	undo.push(copy);
}

void GameManager::delete_cell(int x, int y)
{
	CommandDelete* copy = new CommandDelete;
	copy->set_board(board);
	undo.push(copy);
	copy->execute(x, y);
}