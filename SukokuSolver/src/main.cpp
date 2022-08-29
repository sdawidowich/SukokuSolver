#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <windows.h>

#include "gameboard.h"
#include "logic.h"
#include "backtracking.h"

bool valid_board(Gameboard& gameboard) {
	gameboard.update_groups();
	// Loop group
	for (int i = 0; i < 9; i++) {

		// Loop values
		for (int j = 1; j < 10; j++) {
			
			int row_matches = 0;
			int column_matches = 0;
			int box_matches = 0;
			// Loop cells
			for (int k = 0; k < 9; k++) {
				// Check row
				if (gameboard.get_rows()[i][k] == j) {
					row_matches++;

					if (row_matches > 1) {
						return false;
					}
				}

				// Check column
				if (gameboard.get_columns()[i][k] == j) {
					column_matches++;

					if (column_matches > 1) {
						return false;
					}
				}

				// Check box
				if (gameboard.get_boxes()[i][k] == j) {
					box_matches++;

					if (box_matches > 1) {
						return false;
					}
				}
			}
		}
	}

	return true;
}

void select_method(Gameboard& gameboard) {
	while (true) {
		// Print menu
		std::cout << "Select Solving Method" << std::endl;
		std::cout << "1. Logic Based Algorithm" << std::endl;
		std::cout << "2. Backtracking Algorithm" << std::endl;
		std::cout << "3. Back" << std::endl;
		std::cout << "4. Quit\n" << std::endl;
		std::cout << ">> ";

		// Get menu choice from user
		char choice;
		std::cin >> choice;
		std::cout << std::endl;

		// Handle the specified choice. Anything but 1, 2, or 3 returns an invalid menu option
		switch (choice) {
		case '1':
			system("cls");
			solve_gameboard_logic(gameboard);
			return;
		case '2':
			system("cls");
			solve_gameboard_backtracking(gameboard);
			return;
		case '3':
			system("cls");
			return;
			break;
		case '4':
			std::cout << "Quitting..." << std::endl;
			exit(0);
		default:
			system("cls");
			std::cout << "Invalid Menu Option.\n" << std::endl;
			break;
		}
	}
}

void create_custom_gameboard() {
	Gameboard new_gameboard;

	std::cout << "Enter a number from 1-9. Enter 0 for an empty space and - to go back a cell." << std::endl;
	new_gameboard.print_board();

	// Get the numbers in the custom game board
	int cell_num = 0;
	while (cell_num < 81) {
		// Set cursor position to the right cell number
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		short x_pos = (cell_num % 9) * 4 + 2 + (cell_num / 3) - (cell_num / 9) * 3;
		short y_pos = (cell_num / 9) * 2 + 2;
		COORD pos = {x_pos, y_pos};
		SetConsoleCursorPosition(hConsole, pos);

		char choice;
		int int_choice = -1;

		while (true) {
			SetConsoleCursorPosition(hConsole, pos);
			std::cin.get(choice);
			int_choice = choice - '0';
			if (choice == '-' && cell_num > 0) {
				cell_num--;
				break;
			}
			else if (choice == '-' && cell_num <= 0) {
				system("cls");
				return;
			}
			else if (int_choice >= 0 && int_choice <= 9) {
				new_gameboard.set_cell_value(cell_num, int_choice);
				cell_num++;

				system("cls");
				std::cout << "Enter a number from 1-9. Enter 0 for an empty space and - to go back a cell." << std::endl;
				new_gameboard.print_board();
				break;
			}
			else {
				system("cls");
				std::cout << "Enter a number from 1-9. Enter 0 for an empty space and - to go back a cell." << std::endl;
				new_gameboard.print_board();
				SetConsoleCursorPosition(hConsole, pos);
			}
		}

		if (cell_num >= 81) {
			system("cls");
			std::cin.clear();
			std::cin.ignore();
			while (true) {
				new_gameboard.print_board();
				std::cout << "Enter DONE to finish entering your gameboard or enter - to continue editing your gameboard." << std::endl;
				std::string selection;
				std::getline(std::cin, selection);

				if (selection == "DONE" && !valid_board(new_gameboard)) {
					system("cls");
					std::cout << "The gameboard is invalid. Each row, column, and box must not have any repeating numbers.\n\n";
				}
				else if (selection == "DONE" && valid_board(new_gameboard)) {
					break;
				}
				else if (selection == "-") {
					cell_num--;

					system("cls");
					std::cout << "Enter a number from 1-9. Enter - to go back a box." << std::endl;
					new_gameboard.print_board();
					break;
				}
				else {
					system("cls");
					std::cout << "Invalid option.\n\n";
				}
			}
		}
	}

	system("cls");
	select_method(new_gameboard);
	return;
}

void select_preset_gameboard() {
	// Define Preset Game Boards
	std::vector< std::vector<int> > preset_gameboards = {
		{	// Hard 
			0, 0, 6,  5, 0, 0,  8, 4, 0,
			0, 9, 0,  0, 7, 0,  0, 0, 0,
			3, 0, 0,  6, 0, 0,  0, 0, 9,

			0, 0, 0,  0, 2, 3,  5, 0, 0,
			0, 0, 0,  9, 0, 5,  0, 0, 0,
			0, 0, 7,  8, 1, 0,  0, 0, 0,

			4, 0, 0,  0, 0, 6,  0, 0, 2,
			0, 0, 0,  0, 8, 0,  0, 1, 0,
			0, 6, 1,  0, 0, 9,  3, 0, 0
		},
		{	// Hard
			0, 0, 7,  0, 0, 4,  9, 0, 0,
			0, 0, 0,  0, 0, 2,  7, 4, 0,
			5, 0, 0,  1, 0, 8,  0, 0, 0,

			2, 0, 9,  0, 0, 0,  0, 0, 7,
			4, 0, 0,  0, 3, 0,  0, 0, 1,
			8, 0, 0,  0, 0, 0,  3, 0, 2,

			0, 0, 0,  8, 0, 3,  0, 0, 4,
			0, 1, 5,  4, 0, 0,  0, 0, 0,
			0, 0, 8,  7, 0, 0,  1, 0, 0
		},
		{	// Expert
			0, 0, 5,  0, 2, 0,  6, 0, 0,
			4, 9, 0,  8, 0, 5,  0, 0, 0,
			0, 0, 0,  0, 0, 0,  0, 1, 0,

			0, 4, 0,  1, 0, 0,  5, 0, 6,
			0, 0, 0,  0, 3, 0,  0, 0, 0,
			5, 0, 9,  0, 0, 7,  0, 8, 0,

			0, 3, 0,  0, 0, 0,  0, 0, 0,
			0, 0, 0,  3, 0, 8,  0, 9, 4,
			0, 0, 8,  0, 4, 0,  7, 0, 0
		},
		{	// Expert
			3, 0, 9,  0, 0, 6,  0, 0, 0,
			4, 0, 0,  3, 0, 0,  1, 0, 0,
			0, 0, 2,  7, 0, 0,  0, 0, 0,

			9, 0, 1,  0, 0, 0,  0, 0, 7,
			0, 0, 4,  5, 0, 7,  8, 0, 0,
			8, 0, 0,  0, 0, 0,  3, 0, 9,

			0, 0, 0,  0, 0, 8,  6, 0, 0,
			0, 0, 5,  0, 0, 2,  0, 0, 8,
			0, 0, 0,  9, 0, 0,  7, 0, 4 
		},
		{	// Easy
			6, 0, 0,  0, 0, 9,  7, 4, 0,
			0, 0, 2,  7, 0, 5,  1, 0, 8,
			0, 0, 0,  6, 2, 1,  0, 0, 0,

			0, 0, 9,  2, 0, 0,  4, 5, 0,
			4, 0, 0,  0, 7, 0,  0, 0, 1,
			0, 5, 7,  0, 0, 4,  6, 0, 0,

			0, 0, 0,  9, 1, 6,  0, 0, 0,
			9, 0, 1,  8, 0, 7,  3, 0, 0,
			0, 8, 6,  4, 0, 0,  0, 0, 5
		}
	};
	unsigned int board_selection = 0;

	while (true) {
		// Display current preset gameboard selection
		std::cout << "Select Preset Gameboard\n" << std::endl;
		std::cout << "Preset #" << board_selection + 1 << std::endl;
		Gameboard gameboard_selection(preset_gameboards[board_selection]);
		gameboard_selection.print_board();
		std::cout << "\n<<        Select        Back         >>" << std::endl;
		std::cout << "1           2            3            4\n" << std::endl;
		std::cout << ">> ";

		// Get menu choice from user
		char choice;
		std::cin >> choice;
		std::cout << std::endl;

		// Handle the specified choice. Anything but 1, 2, 3, or 4 returns an invalid menu option
		switch (choice) {
		case '1':
			system("cls");
			if (board_selection <= 0)
				board_selection = preset_gameboards.size() - 1;
			else
				board_selection--;
			
			break;
		case '2':
			system("cls");
			select_method(gameboard_selection);
			break;
		case '3':
			system("cls");
			return;
		case '4':
			system("cls");
			if (board_selection >= preset_gameboards.size() - 1)
				board_selection = 0;
			else
				board_selection++;

			break;
		default:
			system("cls");
			std::cout << "Invalid Menu Option.\n" << std::endl;
			break;
		}
	}
}

bool is_solveable(Gameboard gameboard) {
	int unfilled_cells = gameboard.get_unfilled_cells();
	
	std::vector < std::vector<int> > previous_p_values = { };

	// Check the spaces for possible values until 0 cells are unfilled.
	while (unfilled_cells > 0) {
		check_logic(gameboard);

		unfilled_cells = gameboard.get_unfilled_cells();

		// Check whether the possible values changed from the previous iteration. If not, the board cannot be solved with this algorithm.
		if (gameboard.get_possible_values() == previous_p_values && unfilled_cells != 0) {
			return false;
		}
		else {
			previous_p_values = gameboard.get_possible_values();
		}
	}

	return true;
}

bool fill_cell(Gameboard& gameboard, std::random_device& rd, std::mt19937& engine) {
	// Get next empty cell index. If returns -1, no empty cells so board is solved.
	int cell_num = find_empty_cell(gameboard);

	if (cell_num == -1) 
		return true;

	// Update the row, column, and box gameboard vectors, get the basic possible values for the cell, and shuffle those values in a new vector
	gameboard.update_groups();
	check_base_values(gameboard, cell_num);
	auto cell_p_values = gameboard.get_possible_values()[cell_num];
	std::shuffle(std::begin(cell_p_values), std::end(cell_p_values), engine);

	// Loop through the possible values so if it needs to backtrack, the next possible value is used. 
	for (auto p_value : cell_p_values) {
		gameboard.set_cell_value(cell_num, p_value);
		if (fill_cell(gameboard, rd, engine)) {
			return true;
		}
	}

	// If pass loop, no value is possible, so reset the cell's possible values, set the cell value to empty, and backtrack to the previous cell by returning false
	auto p_values = gameboard.get_possible_values();
	p_values[cell_num] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	gameboard.set_cell_value(cell_num, 0);
	gameboard.set_possible_values(p_values);
	return false;
}

bool empty_cells(Gameboard& gameboard, std::random_device& rd, std::mt19937& engine, int& num_empty) {
	while (true) {
		if (gameboard.get_unfilled_cells() == num_empty) {
			return true;
		}

		// Get random cell number. If returns -1, no empty cells so board is solved.
		std::uniform_int_distribution<int> dist(0, 80);
		int cell_num = dist(engine);

		// Loop through the possible values so if it needs to backtrack, the next possible value is used.
		int value_save = gameboard.get_board()[cell_num];
		gameboard.set_cell_value(cell_num, 0);
		if (is_solveable(gameboard)) {
			if (empty_cells(gameboard, rd, engine, num_empty))
				return true;

			gameboard.set_cell_value(cell_num, value_save);
		}
		else {
			gameboard.set_cell_value(cell_num, value_save);
			return false;
		}
	}
	
}

Gameboard generate_random_gameboard() {
	std::cout << "Loading gameboard..." << std::endl;
	Gameboard new_gameboard;

	std::random_device rd;
	std::mt19937 engine{ rd() };

	// Backtracking random cell filler
	fill_cell(new_gameboard, rd, engine);

	// Reset p values
	auto p_values = new_gameboard.get_possible_values();
	for (int i = 0; i < 81; i++) {
		p_values[i] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	}
	new_gameboard.set_possible_values(p_values);

	// 
	std::uniform_int_distribution<int> dist(50, 55);
	int num_empty = dist(engine);
	empty_cells(new_gameboard, rd, engine, num_empty);

	system("cls");
	return new_gameboard;
}

void select_random_gameboard() {
	Gameboard gameboard = generate_random_gameboard();

	while (true) {
		// Display current preset gameboard selection
		std::cout << "Select Random Gameboard\n" << std::endl;

		gameboard.print_board();
		std::cout << "\nSelect      Back         New" << std::endl;
		std::cout << "1           2            3\n" << std::endl;
		std::cout << ">> ";

		// Get menu choice from user
		char choice;
		std::cin >> choice;
		std::cout << std::endl;

		// Handle the specified choice. Anything but 1, 2, 3, or 4 returns an invalid menu option
		switch (choice) {
		case '1':
			system("cls");
			select_method(gameboard);
			break;
		case '2':
			system("cls");
			return;
		case '3':
			system("cls");
			gameboard = generate_random_gameboard();
			break;
		default:
			system("cls");
			std::cout << "Invalid Menu Option.\n" << std::endl;
			break;
		}
	}
}

void main_menu() {
	while (true) {
		// Print menu
		std::cout << "Main Menu" << std::endl;
		std::cout << "1. Custom Game Board" << std::endl;
		std::cout << "2. Preset Game Board" << std::endl;
		std::cout << "3. Random Game Board" << std::endl;
		std::cout << "4. Quit\n" << std::endl;
		std::cout << ">> ";

		// Get menu choice from user
		char choice;
		std::cin >> choice;
		std::cout << std::endl;

		// Handle the specified choice. Anything but 1, 2, or 3 returns an invalid menu option
		switch (choice) {
		case '1':
			system("cls");
			create_custom_gameboard();
			break;
		case '2':
			system("cls");
			select_preset_gameboard();
			break;
		case '3':
			system("cls");
			select_random_gameboard();
			break;
		case '4':
			std::cout << "Quitting..." << std::endl;
			return;
			break;
		default:
			system("cls");
			std::cout << "Invalid Menu Option.\n" << std::endl;
			break;
		}
	}
}

int main() {
	main_menu();
}