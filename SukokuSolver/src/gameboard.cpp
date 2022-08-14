#include "gameboard.h"
#include <iostream>
#include <string>

Gameboard::Gameboard() {
	// Generate blank board with 0s being empty boxes
	std::vector<int> new_board;
	for (int i = 0; i < 81; i++)
		new_board.push_back(0);

	Gameboard::set_board(new_board);

	// Fill out the rows, columns, and boxes groups
	std::vector< std::vector<int> > new_rows;
	std::vector< std::vector<int> > new_columns;
	std::vector< std::vector<int> > new_boxes;

	for (int i = 0; i < 81; i++) {
		Positions positions = get_positions(i);

		Gameboard::set_vector(new_rows, positions.row, board[i]);
		Gameboard::set_vector(new_columns, positions.column, board[i]);
		Gameboard::set_vector(new_boxes, positions.box, board[i]);
	}

	Gameboard::set_rows(new_rows);
	Gameboard::set_columns(new_columns);
	Gameboard::set_boxes(new_boxes);

	// Set the default possible values for each box
	std::vector< std::vector<int> > new_p_values;
	for (int i = 0; i < 81; i++) {
		std::vector<int> p_values = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		new_p_values.push_back(p_values);
	}
	Gameboard::set_possible_values(new_p_values);
}

Gameboard::Gameboard(std::vector<int> p_board) {
	// Generate blank board with 0s being empty boxes
	std::vector<int> new_board;

	if (p_board.size() >= 81) {
		for (int i = 0; i < 81; i++)
			new_board.push_back(p_board[i]);
	}
	else if (p_board.size() < 81) {
		for (int box : p_board)
			new_board.push_back(box);
		for (int i = p_board.size(); i < 81; i++)
			new_board.push_back(0);
	}

	Gameboard::set_board(new_board);

	// Fill out the rows, columns, and boxes groups
	std::vector< std::vector<int> > new_rows;
	std::vector< std::vector<int> > new_columns;
	std::vector< std::vector<int> > new_boxes;

	for (int i = 0; i < 81; i++) {
		Positions positions = get_positions(i);

		Gameboard::set_vector(new_rows, positions.row, board[i]);
		Gameboard::set_vector(new_columns, positions.column, board[i]);
		Gameboard::set_vector(new_boxes, positions.box, board[i]);
	}

	Gameboard::set_rows(new_rows);
	Gameboard::set_columns(new_columns);
	Gameboard::set_boxes(new_boxes);

	// Set the default possible values for each box
	std::vector< std::vector<int> > new_p_values;
	for (int i = 0; i < 81; i++) {
		std::vector<int> p_values = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		new_p_values.push_back(p_values);
	}
	Gameboard::set_possible_values(new_p_values);
}

std::vector<int> Gameboard::get_board() {
	return Gameboard::board;
}

std::vector<std::vector<int>> Gameboard::get_possible_values() {
	return Gameboard::possible_values;
}

std::vector<std::vector<int>> Gameboard::get_rows() {
	return Gameboard::rows;
}

std::vector<std::vector<int>> Gameboard::get_columns() {
	return Gameboard::columns;
}

std::vector<std::vector<int>> Gameboard::get_boxes() {
	return Gameboard::boxes;
}

void Gameboard::set_board(std::vector<int>& new_board) {
	Gameboard::board = new_board;
}

void Gameboard::set_cell_value(int index, int value) {
	Gameboard::board[index] = value;
}

void Gameboard::set_possible_values(std::vector<std::vector<int>>& new_possible_values) {
	Gameboard::possible_values = new_possible_values;
}

void Gameboard::set_rows(std::vector<std::vector<int>>& new_rows) {
	Gameboard::rows = new_rows;
}

void Gameboard::set_columns(std::vector<std::vector<int>>& new_columns) {
	Gameboard::columns = new_columns;
}

void Gameboard::set_boxes(std::vector<std::vector<int>>& new_boxes) {
	Gameboard::boxes = new_boxes;
}

int Gameboard::print_board() {
	int unfilled_boxes = 0;

	std::cout << "_______________________________________\n";
	for (int i = 0; i < 9; i++) {
		std::string row[9];
		for (int j = 0; j < 9; j++) {
			if (board[i * 9 + j] == 0) {
				unfilled_boxes++;
				row[j] = " ";
			}
			else {
				row[j] = std::to_string(board[i * 9 + j]);
			}
		}

		std::cout << "| " << row[0] << " | " << row[1] << " | " << row[2] << " || " << row[3] << " | " << row[4] << " | " << row[5] << " || " << row[6] << " | " << row[7] << " | " << row[8] << " |" << std::endl;
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

	std::cout << "Unfilled Boxes: " << unfilled_boxes << std::endl;
	return unfilled_boxes;
}

void Gameboard::set_group(std::vector< std::vector<int> >& group, unsigned int position, int value) {
	if (position < group.size()) {
		group[position].push_back(value);
	}
	else {
		group.push_back({ value });
	}
}

void Gameboard::update_groups() {
	std::vector< std::vector<int> > new_rows;
	std::vector< std::vector<int> > new_columns;
	std::vector< std::vector<int> > new_boxes;

	for (int i = 0; i < 81; i++) {
		Positions positions = get_positions(i);

		Gameboard::set_vector(new_rows, positions.row, board[i]);
		Gameboard::set_vector(new_columns, positions.column, board[i]);
		Gameboard::set_vector(new_boxes, positions.box, board[i]);
	}

	Gameboard::set_rows(new_rows);
	Gameboard::set_columns(new_columns);
	Gameboard::set_boxes(new_boxes);
}

Positions Gameboard::get_positions(int index) {
	int row = index / 9;
	//std::cout << "\n \n" << index + 1 << " - Row: " << row + 1 << std::endl;


	double d_column = double(index) / 9.0;
	while (d_column >= 1) {
		d_column--;
	}
	d_column *= 9;
	d_column = round(d_column);
	int column = int(d_column);
	//std::cout << "" << index + 1 << " - Column: " << column + 1 << std::endl;


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
	// std::cout << "" << index << " - Box: " << box << std::endl;
	return { row, column, box };
}

int Gameboard::get_index(Positions& positions) {
	int index = 0;
	index += positions.column;
	index += positions.row * 9;
	return index;
}

void Gameboard::set_vector(std::vector< std::vector<int> >& vector, int row, int value) {
	if (row < vector.size()) {
		vector[row].push_back(value);
	}
	else {
		vector.push_back({ value });
	}
}
