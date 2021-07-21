#include <iostream>
#include <string>
#include <vector>

int print_board(std::vector<int>& board) {
	std::cout << "_______________________________________\n";
	for (int i = 0; i < 9; i++) {
		std::string row[9];
		for (int j = 0; j < 9; j++) {
			if (board[i * 9 + j] == 0) {
				row[j] = " ";
			}
			else {
				row[j] = std::to_string(board[i * 9 + j]);
			}
		}

		std::cout << "| " << row[0] << " | "  << row[1] << " | "  << row[2] << " || "  << row[3] << " | "  << row[4] << " | " << row[5] << " || " << row[6] << " | "  << row[7] << " | "  << row[8] << " |" << std::endl;
		if (i == 2 || i == 5) {
			std::cout << "|===|===|===||===|===|===||===|===|===|" << std::endl;
		}
		else if (i == 8) {
			std::cout << "|___|___|___||___|___|___||___|___|___|" << std::endl;
		}
		else {
			std::cout << "|---|---|---||---|---|---||---|---|---|" << std::endl;
		}
	}
	int unfilled_boxes = 0;
	for (int i = 0; i < 81; i++) {
		if (board[i] == 0) {
			unfilled_boxes++;
		}
	}
	std::cout << "Unfilled Boxes: " << unfilled_boxes << std::endl;
	return unfilled_boxes;
}

void set_vector(std::vector< std::vector<int> >& vector, unsigned int position, int value) {
	if (position < vector.size()) {
		vector[position].push_back(value);
	}
	else {
		vector.push_back({value});
	}
}

struct Positions {
	int row;
	int column;
	int box;
};

Positions get_positions(int i) {
	int row = i / 9;
	//std::cout << "\n \n" << i + 1 << " - Row: " << row + 1 << std::endl;


	double d_column = double(i) / 9.0;
	while (d_column >= 1) {
		d_column--;
	}
	d_column *= 9;
	d_column = round(d_column);
	int column = int(d_column);
	//std::cout << "" << i + 1 << " - Column: " << column + 1 << std::endl;


	int box = 0;
	if (row < 3) {
		if (column < 3)
			box = 0;
		else if (column < 6)
			box = 1;
		else if (column < 9)
			box = 2;
	}
	else if (row < 6) {
		if (column < 3)
			box = 3;
		else if (column < 6)
			box = 4;
		else if (column < 9)
			box = 5;
	}
	else if (row < 9) {
		if (column < 3)
			box = 6;
		else if (column < 6)
			box = 7;
		else if (column < 9)
			box = 8;
	}
	// std::cout << "" << i << " - Box: " << box << std::endl;
	return { row, column, box };
}


void remove_values(std::vector< std::vector<int> >& rows, std::vector< std::vector<int> >& columns, std::vector< std::vector<int> >& boxes, Positions& positions, int i, std::vector<int>& possible_values)
{
	// Checks if the proposed value (i) is already present in the same row, column, and box. If it is, it is removed from the possible values.
	int r_value = rows[positions.row][i];
	if (std::find(possible_values.begin(), possible_values.end(), r_value) != possible_values.end()) {
		possible_values.erase(std::remove(possible_values.begin(), possible_values.end(), r_value), possible_values.end());
	}
	int c_value = columns[positions.column][i];
	if (std::find(possible_values.begin(), possible_values.end(), c_value) != possible_values.end()) {
		possible_values.erase(std::remove(possible_values.begin(), possible_values.end(), c_value), possible_values.end());
	}
	int b_value = boxes[positions.box][i];
	if (std::find(possible_values.begin(), possible_values.end(), b_value) != possible_values.end()) {
		possible_values.erase(std::remove(possible_values.begin(), possible_values.end(), b_value), possible_values.end());
	}
}

void check_grouping(std::string g_name, std::vector<int>& group, std::vector<int>& possible_values, std::vector<std::vector<int>>& rows, Positions& positions, std::vector<std::vector<int>>& columns, std::vector<std::vector<int>>& boxes, std::vector<int>& board, int i, bool& found_answer)
{
	for (int j = 0; j < possible_values.size(); j++) {
		int possible_slots = 0;
		int value = possible_values[j];

		for (int k = 0; k < 9; k++) {
			if (group[k] == 0) {
				int index = 0;
				if (g_name == "row")
					index = positions.row * 9 + k;
				else if (g_name == "column")
					index = positions.column + 9 * k;
				else
					index = positions.box * 3 + k + (k / 3) * 6 + (positions.box / 3) * 18;
				Positions temp_positions = get_positions(index);

				if (std::find(rows[temp_positions.row].begin(), rows[temp_positions.row].end(), value) != rows[temp_positions.row].end()) {
					continue;
				}
				else if (std::find(columns[temp_positions.column].begin(), columns[temp_positions.column].end(), value) != columns[temp_positions.column].end()) {
					continue;
				}
				else if (std::find(boxes[temp_positions.box].begin(), boxes[temp_positions.box].end(), value) != boxes[temp_positions.box].end()) {
					continue;
				}
				else {
					possible_slots++;
				}
			}
		}

		if (possible_slots == 1) {
			board[i] = value;
			found_answer = true;
			break;
		}
	}
}

void check_spaces(std::vector<int>& board) {
	std::vector< std::vector<int> > rows;
	std::vector< std::vector<int> > columns;
	std::vector< std::vector<int> > boxes;

	for (int i = 0; i < 81; i++) {
		Positions positions = get_positions(i);

		set_vector(rows, positions.row, board[i]);
		set_vector(columns, positions.column, board[i]);
		set_vector(boxes, positions.box, board[i]);
	}

	for (int i = 0; i < 81; i++) {
		if (board[i] == 0) {
			std::vector<int> possible_values = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			Positions positions = get_positions(i);

			for (int j = 0; j < 9; j++) {
				remove_values(rows, columns, boxes, positions, j, possible_values);
			}

			if (possible_values.size() == 1) {
				board[i] = possible_values[0];
			}
			else {
				bool found_answer = false;
				check_grouping("box", boxes[positions.box], possible_values, rows, positions, columns, boxes, board, i, found_answer);
				if (!found_answer) {
					check_grouping("row", rows[positions.row], possible_values, rows, positions, columns, boxes, board, i, found_answer);
				}
				if (!found_answer) {
					check_grouping("column", columns[positions.column], possible_values, rows, positions, columns, boxes, board, i, found_answer);
				}
			}

			/*std::cout << "\n[" << i + 1 << "] Possible values: ";
			for (int j : possible_values) {
				std::cout << j << ", ";
			}*/
		}
	}
}

int main() {
	// Hard Puzzle
	/*std::vector<int> game_board = { 
		0, 0, 6,  5, 0, 0,  8, 4, 0, 
		0, 9, 0,  0, 7, 0,  0, 0, 0,
		3, 0, 0,  6, 0, 0,  0, 0, 9,

		0, 0, 0,  0, 2, 3,  5, 0, 0,
		0, 0, 0,  9, 0, 5,  0, 0, 0,
		0, 0, 7,  8, 1, 0,  0, 0, 0,

		4, 0, 0,  0, 0, 6,  0, 0, 2,
		0, 0, 0,  0, 8, 0,  0, 1, 0,
		0, 6, 1,  0, 0, 9,  3, 0, 0 };*/

	// Hard Puzzle 2
	std::vector<int> game_board = {
		0, 0, 7,  0, 0, 4,  9, 0, 0,
		0, 0, 0,  0, 0, 2,  7, 4, 0,
		5, 0, 0,  1, 0, 8,  0, 0, 0,

		2, 0, 9,  0, 0, 0,  0, 0, 7,
		4, 0, 0,  0, 3, 0,  0, 0, 1,
		8, 0, 0,  0, 0, 0,  3, 0, 2,

		0, 0, 0,  8, 0, 3,  0, 0, 4,
		0, 1, 5,  4, 0, 0,  0, 0, 0,
		0, 0, 8,  7, 0, 0,  1, 0, 0 };

	// Expert Puzzle
	/*std::vector<int> game_board = {
		0, 0, 5,  0, 2, 0,  6, 0, 0,
		4, 9, 0,  8, 0, 5,  0, 0, 0,
		0, 0, 0,  0, 0, 0,  0, 1, 0,

		0, 4, 0,  1, 0, 0,  5, 0, 6,
		0, 0, 0,  0, 3, 0,  0, 0, 0,
		5, 0, 9,  0, 0, 7,  0, 8, 0,

		0, 3, 0,  0, 0, 0,  0, 0, 0,
		0, 0, 0,  3, 0, 8,  0, 9, 4,
		0, 0, 8,  0, 4, 0,  7, 0, 0 };*/

	// Easy Puzzle
	/*std::vector<int> game_board = {
		6, 0, 0,  0, 0, 9,  7, 4, 0,
		0, 0, 2,  7, 0, 5,  1, 0, 8,
		0, 0, 0,  6, 2, 1,  0, 0, 0,

		0, 0, 9,  2, 0, 0,  4, 5, 0,
		4, 0, 0,  0, 7, 0,  0, 0, 1,
		0, 5, 7,  0, 0, 4,  6, 0, 0,

		0, 0, 0,  9, 1, 6,  0, 0, 0,
		9, 0, 1,  8, 0, 7,  3, 0, 0,
		0, 8, 6,  4, 0, 0,  0, 0, 5 };*/

	while (true) {
		int unfilled_boxes = print_board(game_board);
		if (unfilled_boxes == 0) {
			break;
		}
		check_spaces(game_board);
		int num = 0;
		for (int i = 0; i < 300000000; i++) {
			num++;
			continue;
		}
		system("cls");
	}
}