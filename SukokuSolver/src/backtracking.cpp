#include "backtracking.h"
#include "gameboard.h"

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

bool valid(Gameboard& gameboard, int& index) {
	// Checks whether the current gameboard is valid (no repeating values in any row, column, or box).
	int value = gameboard.get_board()[index];
	if (value > 9)
		return false;

	int row_index = index / 9;
	int column_index = index % 9;
	int box_index = (index / 27) * 3 + ((index % 9) / 3);
	
	// Loop through each group
	for (int i = 0; i < 9; i++) {
		// Check row
		if (gameboard.get_board()[row_index * 9 + i] == value && (row_index * 9 + i) != index)
			return false;

		// Check column
		if (gameboard.get_board()[column_index + i * 9] == value && (column_index + i * 9) != index)
			return false;

		// Check box
		if (gameboard.get_board()[(box_index / 3) * 18 + box_index * 3 + (i / 3) * 9 + (i % 3)] == value && ((box_index / 3) * 18 + box_index * 3 + (i / 3) * 9 + (i % 3)) != index)
			return false;
	}
	return true;
}

int find_empty_cell(Gameboard& gameboard) {
	// Loop through all cells and if you hit a cell with value 0 (empty), then return that index.
	for (int i = 0; i < 81; i++) {
		if (gameboard.get_board()[i] == 0)
			return i;
	}
	// If No empty cells, return -1;
	return -1;
}

bool test_cells(Gameboard& gameboard) {
	// Get next empty cell index. If returns -1, no empty cells so board is solved.
	int cell_num = find_empty_cell(gameboard);
	if (cell_num == -1)
		return true;

	// Loop through all possible values, checking if it is valid at the index. If it is, call recursive function to go to next empty cell. If it returns true, the board is solved so continue returning true.
	for (int i = 1; i < 10; i++) {
		gameboard.set_cell_value(cell_num, i);
		if (valid(gameboard, cell_num))
			if (test_cells(gameboard))
				return true;
	}

	// If loop passes, the cell has no possible values so set value to 0 and backtrack to previous cells
	gameboard.set_cell_value(cell_num, 0);
	return false;
}

void solve_gameboard_backtracking(Gameboard& gameboard) {
	gameboard.print_board();

	test_cells(gameboard);

	system("cls");
	gameboard.print_board();
}