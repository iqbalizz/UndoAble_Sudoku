#include "Board.h"

typedef mt19937 RandGenerator;
RandGenerator rng;

Board::Board() {
	// clear grid memory
	for (int i = 0; i < 9; ++i)
		for (int j = 0; j < 9; ++j) {
			grid[i][j] = 0;
			solution[i][j] = 0;
		}
	// random number generator
	rng.seed(time(nullptr));
}

void Board::difficulty(int n)
{
	CELLS_TO_REMOVE = n;
}

void Board::fillCell(int x, int y, int z)
{
	grid[x][y] = z;
}

void Board::deleteCell(int x, int y)
{
	if (grid[x][y] != 0)
	{
		grid[x][y] = 0;
	}
	else {
		cout << endl << "Cell is already empty!" << endl;
	}
}

int Board::getCellValue(int x, int y)
{
	return grid[x][y];
}

int Board::getCellSolValue(int x, int y)
{
	return solution[x][y];
}

bool Board::nInRegion(int n, int i, int j) {
	//  region coordinate to center position in grid
	int center[2] = { i * 3 + 1, j * 3 + 1 };
	// iterate over region to check if n exists in it
	for (int x = center[0] - 1; x <= center[0] + 1; ++x) {
		for (int y = center[1] - 1; y <= center[1] + 1; ++y) {
			if (solution[x][y] == 0) return false;
			if (n == solution[x][y]) return true;
		}
	}
	return false;
}

bool Board::nInCol(int n, int j) {
	// iterate over the column to check if n exists in it
	for (int i = 0; i < 9; ++i) {
		if (solution[i][j] == 0) break;
		if (solution[i][j] == n) return true;
	}
	return false;
}

vector<bool> Board::getRegionPossibilities(int i, int j) {
	vector<bool> output(9, true);
	// region coordinate to center position in grid
	int center[2] = { i * 3 + 1, j * 3 + 1 };
	// iterate over region to check if n exists in it
	for (int x = center[0] - 1; x <= center[0] + 1; ++x) {
		for (int y = center[1] - 1; y <= center[1] + 1; ++y) {
			if (this->grid[x][y] != 0)
				output[this->grid[x][y] - 1] = false;
		}
	}
	return output;
}

vector<bool> Board::getColPossibilites(int j) {
	vector<bool> output(9, true);
	for (int i = 0; i < 9; ++i) {
		if (this->grid[i][j] != 0)
			output[this->grid[i][j] - 1] = false;
	}
	return output;
}

vector<bool> Board::getRowPossibilities(int i) {
	vector<bool> output(9, true);
	for (int j = 0; j < 9; ++j) {
		if (this->grid[i][j] != 0)
			output[this->grid[i][j] - 1] = false;
	}
	return output;
}

int possiblesCount(vector<bool> possibles) {
	int count = 0;
	for (int i = 0; i < possibles.size(); ++i) {
		if (possibles[i]) ++count;
	}
	return count;
}

void Board::generate() {
	vector<bool> oneToNine(9, true);

	// generate sudoku grid
	for (int i = 0; i < 9; ++i) {
		// generate horizontal 
		vector<bool> h_possibles = oneToNine;

		int j = 0;
		while (j < 9) {
			// if not initialized yet store the possibles of the row
			if (this->possibles[i][j].size() == 0) {
				this->possibles[i][j] = h_possibles;
			}

			// check if out of possible numbers
			if (possiblesCount(this->possibles[i][j]) == 0) {
				// replenish this square numbers
				this->possibles[i][j].resize(0);
				--j; // back to 1 cell

				// remove the chosen one from the possibles
				this->possibles[i][j][solution[i][j] - 1] = false;
				h_possibles[solution[i][j] - 1] = true;
				solution[i][j] = 0;
			}
			else {
				// get a number randomly from the available numbers
				uniform_int_distribution<uint32_t> tempGenerator(0, possiblesCount(this->possibles[i][j]) - 1);
				int n = tempGenerator(rng) + 1;
				int choosen = 0;
				while (true) { // choose from the possible ones the n-one
					if (this->possibles[i][j][choosen]) --n;
					if (n == 0) break;
					++choosen;
				}

				// check if it conflicts
				if (nInRegion(choosen + 1, i / 3, j / 3) || nInCol(choosen + 1, j)) {
					// remove from available numbers for this square
					this->possibles[i][j][choosen] = false;
				}
				else {
					// use it and continue
					solution[i][j] = choosen + 1;
					h_possibles[choosen] = false;
					++j;
				}
			}
		}
	}
	// remove from grid according to the only-one-solution rule
	copySol();
}

void Board::setCellSolved(int i, int j, int n) {
	int center[2] = { (i / 3) * 3 + 1, (j / 3) * 3 + 1 };
	// iterate over region to remove n from possibles
	for (int x = center[0] - 1; x <= center[0] + 1; ++x) {
		for (int y = center[1] - 1; y <= center[1] + 1; ++y) {
			this->possibles[x][y][n] = false;
		}
	}

	// vertical and horizontal place in grid removal
	for (int x = 0; x < 9; ++x) {
		this->possibles[x][j][n] = false;
		this->possibles[i][x][n] = false;
	}

	this->solution_changes++;
	this->grid[i][j] = n + 1;
}

int Board::checkSolvedCells() {
	int solved = 0;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (this->grid[i][j] == 0 &&
				possiblesCount(this->possibles[i][j]) == 1) {
				// get the only possible one possibile
				for (int x = 0; x < 9; ++x) {
					if (this->possibles[i][j][x]) {
						solved++;
						setCellSolved(i, j, x);
						break;
					}
				}
			}
		}
	}
	return solved;
}

// last cell
void Board::checkRegion(int i, int j) {
	// get region center coords
	int center[2] = { (i / 3) * 3 + 1, (j / 3) * 3 + 1 };

	// check for repeated in region
	int times[9] = { 0 };
	for (int x = center[0] - 1; x <= center[0] + 1; ++x)
		for (int y = center[1] - 1; y <= center[1] + 1; ++y)
			if (x != i && y != j) {
				// when cell is different Count the possibles
				for (int n = 0; n < 9; ++n) {
					if (this->possibles[x][y][n]) times[n]++;
				}
			}
	for (int n = 0; n < 9; ++n) {
		if (times[n] == 1) {
			// only one possible n in region
			setCellSolved(i, j, n);
		}
	}

	// check for repeated in row and column
	fill_n(times, 9, 0); // reset times array
	int times_col[9] = { 0 };
	for (int x = 0; x < 9; ++x) {
		for (int n = 0; n < 9; ++n) {
			// count the possibles in the row
			if (this->possibles[i][x][n]) times[n]++;
			// count the possibles in the column
			if (this->possibles[x][j][n]) times_col[n]++;
		}
	}
	for (int n = 0; n < 9; ++n) {
		if (times[n] == 1) {
			// if only one possible n in row
			setCellSolved(i, j, n);
		}
		else if (times_col[n] == 1) {
			// if only one possible n in column
			setCellSolved(i, j, n);
		}
	}
}

bool Board::solve() {
	this->solution_changes = 0;
	// clear memory from possibles array
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			this->possibles[i][j] = vector<bool>(9, false);
		}
	}

	while (true) {
		int lastChanges = this->solution_changes;
		// get absolute vertical possibilities
		vector<bool> v_possibles[9];
		vector<bool> h_possibles[9];
		for (int j = 0; j < 9; ++j) {
			v_possibles[j] = getColPossibilites(j);
		}

		// calculate all possibles of each cell
		for (int i = 0; i < 9; ++i) {
			h_possibles[i] = getRowPossibilities(i);
			for (int j = 0; j < 9; ++j) {
				vector<bool> q_possibles = getRegionPossibilities(i / 3, j / 3);
				for (int n = 0; n < 9; ++n) {
					this->possibles[i][j][n] = (h_possibles[i][n] &&
						v_possibles[j][n] &&
						q_possibles[n]);
				}
			}
		}

		// check for solved cells
		if (checkSolvedCells() == 0) {
			for (int i = 0; i < 9; ++i) {
				for (int j = 0; j < 9; ++j) {
					if (this->grid[i][j] != 0) continue;
					checkRegion(i, j);
				}
			}
		}

		// avoid infinite loops
		if (lastChanges == this->solution_changes) break;
	}

	return isSolRight();
}

void Board::copySol() {
	// Save the removed cells coordinates
	// int x_removed[CELLS_TO_REMOVE];
	// int y_removed[CELLS_TO_REMOVE];

	int* x_removed = new int[CELLS_TO_REMOVE];
	int* y_removed = new int[CELLS_TO_REMOVE];

	while (true) { // while more than one solution
		for (int i = 0; i < 9; ++i) {
			for (int j = 0; j < 9; ++j) {
				this->grid[i][j] = this->solution[i][j];
			}
		}
		uniform_int_distribution<uint32_t> tempGenerator(0, 8);
		for (int i = 0; i < CELLS_TO_REMOVE; ++i) {
			x_removed[i] = tempGenerator(rng);
			y_removed[i] = tempGenerator(rng);
			// Avoid repeated cells
			while (this->grid[x_removed[i]][y_removed[i]] == 0) {
				x_removed[i] = tempGenerator(rng);
				y_removed[i] = tempGenerator(rng);
			}
			this->grid[x_removed[i]][y_removed[i]] = 0;
		}
		if (this->solve()) break; // end loop when found only one solution Board
	}

	for (int i = 0; i < CELLS_TO_REMOVE; ++i) {
		this->grid[x_removed[i]][y_removed[i]] = 0;
	}
}

bool Board::isSolRight() {
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			if (this->grid[i][j] != this->solution[i][j]) {
				return false;
			}
		}
	}
	return true;
}

// printing the Board board
void draw_separator() {
	cout << "+-------+-------+-------+" << endl;
}

char draw_cell_content(const int n) {
	// if cell holds a 0 , draw a ' ' instead
	if (n == 0) return ' ';
	else return n + '0';
}

void drawBoard(int grid[][9]) {
	for (int i = 0; i < 9; ++i) {
		if (i % 3 == 0) draw_separator();
		for (int j = 0; j < 9; ++j) {
			// draw column separator
			if (j % 3 == 0) cout << (!j ? "" : " ") << "|";
			cout << " " << draw_cell_content(grid[i][j]);
		}
		cout << " |" << endl;
	}
	draw_separator();
}

void Board::draw() 
{
	drawBoard(this->grid);
}

void Board::drawSolution() {
	drawBoard(this->solution);
}

void Board::setCell(int x, int y, int z) 
{
	grid[x][y] = z;
}

void Board::setSolCell(int x, int y, int z)
{
	solution[x][y] = z;
}