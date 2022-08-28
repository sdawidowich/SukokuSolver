#pragma once
#include <vector>

enum class Group {
	ROW = 0, COLUMN = 1, BOX = 2
};

struct Positions {
	int row;
	int column;
	int box;
};

class Gameboard {
private:
	std::vector<int> board;
	std::vector< std::vector<int> > possible_values;
	std::vector< std::vector<int> > rows;
	std::vector< std::vector<int> > columns;
	std::vector< std::vector<int> > boxes;
public:
	// Constructors
	Gameboard();
	Gameboard(std::vector<int> p_board);

	// Getters
	std::vector<int> get_board();
	std::vector <std::vector<int> > get_possible_values();
	std::vector <std::vector<int> > get_rows();
	std::vector <std::vector<int> > get_columns();
	std::vector <std::vector<int> > get_boxes();

	// Setters
	void set_board(std::vector<int>& new_board);
	void set_cell_value(int index, int value);
	void set_possible_values(std::vector< std::vector<int> >& new_possible_values);
	void set_rows(std::vector< std::vector<int> >& new_rows);
	void set_columns(std::vector< std::vector<int> >& new_columns);
	void set_boxes(std::vector< std::vector<int> >& new_boxes);

	// Helper Functions
	int print_board();
	void set_group(std::vector< std::vector<int> >& group, unsigned int position, int value);
	void update_groups();
	Positions get_positions(int index);
	int get_index(Positions& positions);
	void set_vector(std::vector< std::vector<int> >& vector, int row, int value);
	int get_unfilled_cells();
};