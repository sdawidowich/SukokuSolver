#include "strategies.h"
#include "gameboard.h"

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

bool check_base_values(Gameboard& gameboard, int index) {
	// Remove used values in the same row, column, and 9x9 box from the possible values of at an index
	bool found_value = false;

	// Get positions (row, column, box) at index and possible values of the board
	Positions gameboard_positions = gameboard.get_positions(index);
	std::vector< std::vector<int> > p_values = gameboard.get_possible_values();

	for (int j = 0; j < 9; j++) {
		// Checks if the value of the cell for each group in the current iteration is in the cell's possible values and if it is, the value is removed from the possible values.
		int r_value = gameboard.get_rows()[gameboard_positions.row][j];
		if (std::find(p_values[index].begin(), p_values[index].end(), r_value) != p_values[index].end()) {
			p_values[index].erase(std::remove(p_values[index].begin(), p_values[index].end(), r_value), p_values[index].end());
		}

		int c_value = gameboard.get_columns()[gameboard_positions.column][j];
		if (std::find(p_values[index].begin(), p_values[index].end(), c_value) != p_values[index].end()) {
			p_values[index].erase(std::remove(p_values[index].begin(), p_values[index].end(), c_value), p_values[index].end());
		}

		int b_value = gameboard.get_boxes()[gameboard_positions.box][j];
		if (std::find(p_values[index].begin(), p_values[index].end(), b_value) != p_values[index].end()) {
			p_values[index].erase(std::remove(p_values[index].begin(), p_values[index].end(), b_value), p_values[index].end());
		}

		// If only 1 possible value for the box, that box's value in the only possible value
		if (p_values[index].size() == 1) {
			gameboard.set_cell_value(index, p_values[index][0]);
			found_value = true;
			break;
		}
	}

	// Set the possible values of the gameboard to the new p values 
	gameboard.set_possible_values(p_values);

	return found_value;
}

void check_group_pairs(std::vector< std::vector<int> >& p_values, int sIndex, int ref, int increment, Group group) {
	int ref_cell = sIndex + ref * increment;
	if (group == Group::BOX)
		ref_cell = sIndex + (ref / 3) * 9 + ref % 3;

	// If reference cell only has 1 possible value (i.e. already filled), don't waste your time and return
	if (p_values[ref_cell].size() == 1)
		return;

	// Check how many cells in the group have the same p values as the ref cell
	int pair_count = 0;
	for (int k = 0; k < 9; k++) {
		int inc_cell = (group != Group::BOX) ? (sIndex + k * increment) : (sIndex + (k / 3) * 9 + k % 3);

		if (p_values[ref_cell] == p_values[inc_cell])
			pair_count++;
	}

	// If ref cell equals as many cells as it has p values, remove the p values of ref cell from all the unmatching cells
	if (pair_count == p_values[ref_cell].size()) {

		// Loop through all cells in group
		for (int k = 0; k < 9; k++) {
			int inc_cell = (group != Group::BOX) ? (sIndex + k * increment) : (sIndex + (k / 3) * 9 + k % 3);

			// Don't remove ref cell p values from matching cells
			if (p_values[ref_cell] == p_values[inc_cell])
				continue;
			else
				// For each p value in the ref cell, remove it from the p values of all unmatching cell
				for (auto p_value : p_values[ref_cell])
					p_values[inc_cell].erase(std::remove(p_values[inc_cell].begin(), p_values[inc_cell].end(), p_value), p_values[inc_cell].end());
		}
	}
}

void check_pairs(Gameboard& gameboard) {
	// Check each group for lone pairs of possible values (etc. 3 and 8 as the only possible values for a cell). 
	// If 2 cells in a group have the same pair, those possible values are removed from all the other cells' possible values. 
	// Works with set of 3 possible values with 3 cells, 4 values with 4 cells, etc.

	std::vector< std::vector<int> > p_values = gameboard.get_possible_values();

	// Loop each group
	for (int i = 0; i < 9; i++) {

		// Loop each cell in each group
		for (int j = 0; j < 9; j++) {

			// Check row group where sIndex is the starting index of the group and increment is amount to next cell in the group
			check_group_pairs(p_values, i * 9, j, 1, Group::ROW);
			// Check column group
			check_group_pairs(p_values, i, j, 9, Group::COLUMN);
			// Check box group
			check_group_pairs(p_values, i * 3 + 18 * (i / 3), j, 0, Group::BOX);
		}
	}

	// Set the possible values of the gameboard to the new p values 
	gameboard.set_possible_values(p_values);
}

void check_row_boxes(Gameboard& gameboard) {
	// If a possible value in a row or column only appears in cells in one box group, then that p value has to appear in that row or column in that box.
	// So, the p value is removed from the other cells in the box outside of that row or column. 

	std::vector< std::vector<int> > p_values = gameboard.get_possible_values();

	// Loop each row and column
	for (int i = 0; i < 9; i++) {

		// Loop each p value (1-9)
		for (int j = 0; j < 9; j++) {
			std::vector<int> boxes;
			
			// Loop each cell in the row
			for (int k = 0; k < 9; k++) {
				int index = i * 9 + k;

				// Check if the p value appears in the box, and if it does check if the cell's box is already added to the boxes vector
				if (std::find(p_values[index].begin(), p_values[index].end(), j) != p_values[index].end()) {
					Positions position = gameboard.get_positions(index);
					if (std::find(boxes.begin(), boxes.end(), position.box) == boxes.end())
						boxes.push_back(position.box);
				}
			}

			// If the boxes vector only found the p value appearing in 1 box in the row, remove the p value from all the cells in the box that are not in that row.
			if (boxes.size() == 1) {
				for (int k = 0; k < 9; k++) {
					int index = boxes[0] * 3 + 18 * (boxes[0] / 3) + (k / 3) * 9 + (k % 3);
					Positions positions = gameboard.get_positions(index);
					if (positions.row != i) {
						p_values[index].erase(std::remove(p_values[index].begin(), p_values[index].end(), j), p_values[index].end());
					}
				}
			}

			boxes = {};
			// Loop each cell in the column
			for (int k = 0; k < 9; k++) {
				int index = i + k * 9;

				// Check if the p value appears in the box, and if it does check if the cell's box is already added to the boxes vector
				if (std::find(p_values[index].begin(), p_values[index].end(), j) != p_values[index].end()) {
					Positions position = gameboard.get_positions(index);
					if (std::find(boxes.begin(), boxes.end(), position.box) == boxes.end())
						boxes.push_back(position.box);
				}
			}

			// If the boxes vector only found the p value appearing in 1 box in the column, remove the p value from all the cells in the box that are not in that column.
			if (boxes.size() == 1) {
				for (int k = 0; k < 9; k++) {
					int index = boxes[0] * 3 + 18 * (boxes[0] / 3) + (k / 3) * 9 + (k % 3);
					Positions positions = gameboard.get_positions(index);
					if (positions.column != i) {
						p_values[index].erase(std::remove(p_values[index].begin(), p_values[index].end(), j), p_values[index].end());
					}
				}
			}
		}
	}

	// Set the possible values of the gameboard to the new p values 
	gameboard.set_possible_values(p_values);
}

void check_spaces(Gameboard& gameboard) {
	// Reduce the number of possible values for each cell using variety of strategy, filling in values when 1 possible value remains.
	for (int i = 0; i < 81; i++) {
		// If cell is empty, reduce the number of possible values, else set the possible values equal to the known value of the cell
		if (gameboard.get_board()[i] == 0) {
			// Determine baseline possible values for each cell by removing already used cell values in the same row, column, or 9x9 box from the possible values
			if (check_base_values(gameboard, i))
				continue;
		}
		else {
			std::vector< std::vector<int> > p_values = gameboard.get_possible_values();
			p_values[i] = { gameboard.get_board()[i] };
			gameboard.set_possible_values(p_values);
		}
	}
	check_pairs(gameboard);
	check_row_boxes(gameboard);

	gameboard.update_groups();
}

void solve_gameboard(Gameboard& gameboard) {
	while (true) {
		int unfilled_boxes = gameboard.print_board();
		if (unfilled_boxes == 0) {
			break;
		}

		check_spaces(gameboard);
		
		// Pause for 1 sec
		using namespace std::this_thread;     // sleep_for, sleep_until
		using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
		using std::chrono::system_clock;

		sleep_for(10ns);
		sleep_until(system_clock::now() + 1s);

		system("cls");
	}
}