﻿#include <iostream>
#include <string>
#include <vector>

void print_board(int (&board)[81]) {
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
}

void set_vector(std::vector< std::vector<int> >& vector, unsigned int position, int value) {
	if (position < vector.size()) {
		vector[position].push_back(value);
	}
	else {
		vector.push_back({value});
	}
}

void check_spaces(int(&board)[81]) {
	std::vector< std::vector<int> > rows;
	std::vector< std::vector<int> > columns;
	std::vector< std::vector<int> > boxes;

	for (int i = 0; i < 81; i++) {
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
		//std::cout << "" << i + 1 << " - Box: " << box + 1 << std::endl;


		set_vector(rows, row, board[i]);
		set_vector(columns, column, board[i]);
		set_vector(boxes, box, board[i]);
	}
	for (int i = 0; i < 81; i++) {
		if (board[i] == 0) {
			std::vector<int> possible_values = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };



			std::cout << "\n[" << i + 1 << "] Possible values: ";
			for (int j : possible_values) {
				std::cout << j << ", ";
			}
		}
	}
}

int main() {
	int game_board[81] = { 
		6, 0, 0,  0, 0, 9,  7, 4, 0, 
		0, 0, 2,  7, 0, 5,  1, 0, 8,
		0, 0, 0,  6, 2, 1,  0, 0, 0,

		0, 0, 9,  2, 0, 0,  4, 5, 0,
		4, 0, 0,  0, 7, 0,  0, 0, 1,
		0, 5, 7,  0, 0, 4,  6, 0, 0,

		0, 0, 0,  9, 1, 6,  0, 0, 0,
		9, 0, 1,  8, 0, 7,  3, 0, 0,
		0, 8, 6,  4, 0, 0,  0, 0, 5 };

	print_board(game_board);

	check_spaces(game_board);
}