#pragma once
#include <iostream>
#include <random>
#include <ctime>
#include <vector>
#include <fstream>
#include <filesystem>
using namespace std;


class Board {
private:
	bool nInRegion(int, int, int);
	bool nInCol(int, int);

	vector<bool> getRegionPossibilities(int, int);
	vector<bool> getColPossibilites(int);
	vector<bool> getRowPossibilities(int);

	void setCellSolved(int, int, int);
	int checkSolvedCells();
	void checkRegion(int, int);
	void copySol();

	int grid[9][9];
	int solution[9][9];
	vector<bool> possibles[9][9];

	int CELLS_TO_REMOVE = 50;
	int solution_changes;

public:
	Board();
	~Board() = default;

	bool isSolRight();
	void difficulty(int);
	void generate();
	bool solve();
	void draw();
	void drawSolution();
	int getCellSolValue(int, int);
	int getCellValue(int, int);
	void fillCell(int, int, int);
	void deleteCell(int, int);
	void setCell(int, int, int);
	void setSolCell(int, int, int);
};