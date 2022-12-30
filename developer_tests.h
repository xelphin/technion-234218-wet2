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

#include "worldcup23a2.h"
#include "wet2util.h"
#include "Player.h"
#include "Team.h"
#include "NodeList.h"
#include "Hash.h"
#include "AVL_tree.h"
#include "Exception.h"

// HASH
template<class T>
class Hash;

template<class T>
class Hash_Tests{
public:
    static bool total_elem_correct(Hash<T>& hash);
};

template<class T>
bool Hash_Tests<T>::total_elem_correct(Hash<T>& hash) {
    int count  = 0;
    for (int i=0; i < hash.size; i++) {
        count += hash.arr[i].getAmount();
    }
    if (count != hash.total_elem) {
        throw std::logic_error("Total elem, does not reflect true total elements in array");
    }
    return true;
}





bool run_all_tests();
void run_test(std::function<bool()> test, std::string test_name, std::string& success_string, bool& success);
bool treeCompare(const std::string& tree, const std::string& wantedTree);


// SYSTEM TESTS
bool system_basic();

// PLAYER
bool player_basic();

// TEAM
bool team_basic();

// NODELIST
bool nodeList_basic();
bool nodeList_find();
bool nodeList_popStart();

// HASH TESTS

bool hash_basic();
bool hash_add();
bool hash_find();

// AVL TESTS
bool createAVL();
bool balanceAVL_LL();
bool balanceAVL_RR();
bool balanceAVL_LR();
bool balanceAVL_RL();
bool find_test();
bool remove_test();

// WORLCUP TESTS
bool worldcup_basic();
bool worldcup_addTeam();

#endif