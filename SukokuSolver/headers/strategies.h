#pragma once
#include "gameboard.h"
#include "strategies.h"
#include "gameboard.h"

#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

bool check_base_values(Gameboard& gameboard, int index);
void check_naked_pair_group(std::vector< std::vector<int> >& p_values, int sIndex, int ref, int increment, Group group);
void check_naked_pairs(Gameboard& gameboard);
void check_hidden_pair_group(std::vector< std::vector<int> >& p_values, std::vector< std::vector<int> >& group_appearances, int p_value, int cell, int index);
void check_hidden_pair_matches(std::vector<std::vector<int>>& p_values, std::vector<std::vector<int>>& group_appearances, int i, int j, Group group);
void check_hidden_pairs(Gameboard& gameboard);
void check_row_boxes_group(Gameboard& gameboard, std::vector<std::vector<int>>& p_values, int& i, int& j, Group group);
void check_row_boxes(Gameboard& gameboard);
void solve_gameboard_strategy(Gameboard& gameboard);