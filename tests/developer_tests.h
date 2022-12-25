#ifndef DEVELOPER_TESTS_H
#define DEVELOPER_TESTS_H

#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>
#include <random>
#include <array>
#include <memory>
#include <cstdio>
#include <fstream>
#include <cstring>
#include <functional>
#include <cmath>

#include "../src/worldcup23a2.h"
#include "../src/wet2util.h"
#include "../src/Player.h"
#include "../src/Team.h"
#include "../src/NodeList_Players.h"


bool run_all_tests();
void run_test(std::function<bool()> test, std::string test_name, std::string& success_string, bool& success);


// SYSTEM TESTS
bool system_basic();

// PLAYER
bool player_basic();

// TEAM
bool team_basic();

// NODELIST_PLAYERS
bool nodeListPlayers_basic();
bool nodeListPlayers_find();
bool nodeListPlayers_popStart();

// HASH TESTS




#endif