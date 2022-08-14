#pragma once
#include "gameboard.h"

bool get_baseline_values(Gameboard& gameboard, int index);
void check_spaces(Gameboard& gameboard);
void check_group_pairs(std::vector<std::vector<int>>& p_values, int sIndex, int j, int increment);
void solve_gameboard(Gameboard& gameboard);