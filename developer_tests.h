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

// HASH
template<class T>
class Hash;

template<class T>
class Hash_Tests{
public:
    static bool total_elem_correct(Hash<T>& hash);
    static void print_hash(Hash<T>& hash);
    static void hash_elements_prints(Hash<T>& hash);
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

template<class T>
void Hash_Tests<T>::print_hash(Hash<T> &hash) {
    std::cout << hash.allLists();
}

template<class T>
void Hash_Tests<T>::hash_elements_prints(Hash<T> &hash) {
    std::string str = "Hash with size: " + std::to_string(hash.size) + " contains: \n";

    for (int i=0; i < hash.size; i++) {
        if(hash.arr[i].getAmount() != 0) {
            str += "line " + std::to_string(i) + ": " + hash.arr[i].strList() + "\n";
        }
    }
}


template<class T>
class UF_tests{
    static void print_UF_subsets();
};

template<class T>
void UF_tests<T>::print_UF_subsets() {

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

// UF TESTS
bool UF_test();

// WORLCUP TESTS
bool worldcup_basic();
bool worldcup_addTeam();
bool worldcup_removeTeam_basic(); // TODO: Make one that's more updated when add/remove player gets implemented

#endif