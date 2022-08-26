#pragma once
#include "gameboard.h"

bool valid(Gameboard& gameboard, int& index);
int find_empty_cell(Gameboard& gameboard);
bool test_cells(Gameboard& gameboard);
void solve_gameboard_backtracking(Gameboard& gameboard);