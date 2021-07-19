#include <iostream>
#include <string>

void print_board(int board[]) {
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
}