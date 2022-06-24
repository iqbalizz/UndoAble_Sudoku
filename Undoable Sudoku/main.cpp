#include <iostream>
#include "GameManager.h"

int main() {
	Board board;
	Player player;
	GameManager game(&board, &player);

	int menu = 10;
	while (menu != 0)
	{
		cout << "   SUDOKU   " << endl
			<< "1. Play" << endl
			<< "2. Continue " << endl
			<< "3. Save Turn" << endl
			<< "4. Load Turn" << endl
			<< "0. Exit Game" << endl
			<< "Pilihan : "; cin >> menu;

		switch (menu)
		{
		case 1:
			game.play();
			break;
		case 2:
			game.continue_game();
			break;
		case 3:
			game.save_file();
			break;
		case 4:
			game.load_file();
			break;
		case 0:
			break;
		default:;
		}
	}
}