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

#include <list> // For debugging

#include "worldcup23a2.h"


template<class T>
class Hash;
template<class T>
class UnionFind;

// HASH

template<class T>
class Hash_Tests{
public:
    static bool total_elem_correct(Hash<T>& hash);
    static bool fill_list(Hash<T>& hash, std::list<std::shared_ptr<T>>& lst);
    // static bool fill_list(Hash<UnionFind<T>::Node>& hash, std::list<std::shared_ptr<T>>& lst);
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
bool Hash_Tests<T>::fill_list(Hash<T>& hash, std::list<std::shared_ptr<T>>& lst) {
    // Fill lst with all the elements
    for (int i=0; i< hash.size; i++) { // Iterate over each block in arr
        // Fill lst with all its content
        typename NodeList<T>::Node* curr = hash.arr[i].start;
        while (curr!=nullptr) {
            lst.push_back(curr->obj);
            curr = curr->next;
        }
    }
    return true;
}

// UNION FIND


template<class T>
class UnionFind_Tests{
public:
    static std::string show_hash(UnionFind<T>& uf);
    static std::string show_team_captains(UnionFind<T>& uf);
    static std::string show_union_find(UnionFind<T>& uf);
private:
    static std::string show_union_find_aux(UnionFind<T>& uf,
                                           std::list<std::shared_ptr<typename UnionFind<T>::Node>>& lst,
                                           std::shared_ptr<typename UnionFind<T>::Node> parent,
                                           std::string& str,
                                           std::string prefix);
};

template<class T>
std::string UnionFind_Tests<T>::show_hash(UnionFind<T>& uf) {
    return uf.hash.allLists();
}

template<class T>
std::string UnionFind_Tests<T>::show_team_captains(UnionFind<T>& uf) {
    std::list<std::shared_ptr<typename UnionFind<T>::Node>> lst;
    Hash_Tests<typename UnionFind<T>::Node>::fill_list(uf.hash, lst);
    typename std::list<std::shared_ptr<typename UnionFind<T>::Node>>::iterator it;
    //
    std::string captain = "Players that are Team Captains: ";
    for (it = lst.begin(); it != lst.end(); ++it){
        if ((**it).parent == nullptr){
            captain += std::to_string((*it)->get_id()) + " ";
        }
    }

    return captain;
}

template<class T>
std::string UnionFind_Tests<T>::show_union_find(UnionFind<T>& uf) {
    std::list<std::shared_ptr<typename UnionFind<T>::Node>> lst;
    Hash_Tests<typename UnionFind<T>::Node>::fill_list(uf.hash, lst);
    typename std::list<std::shared_ptr<typename UnionFind<T>::Node>>::iterator it;
    //
    std::string str = "Union Find: \n";
    // Find Captains
    for (it = lst.begin(); it != lst.end(); ++it){
        std::string str_team = "";
        std::string prefix = " ";
        if ((**it).parent == nullptr){
            str_team += std::to_string((*it)->get_id());
            show_union_find_aux(uf, lst, *it, str_team, prefix + std::string(((*it)->get_id()) % 10, ' '));
            str += str_team + "\n";
        }

    }

    return str;
}

template<class T>
std::string UnionFind_Tests<T>::show_union_find_aux(UnionFind<T>& uf,
                                                    std::list<std::shared_ptr<typename UnionFind<T>::Node>>& lst,
                                                    std::shared_ptr<typename UnionFind<T>::Node> parent,
                                                    std::string& str,
                                                    std::string prefix)
{
    //
    typename std::list<std::shared_ptr<typename UnionFind<T>::Node>>::iterator it;
    for (it = lst.begin(); it != lst.end(); ++it){
        if (&(*(*it)->parent) == &(*parent)){
            str += "\n"+ prefix +"---" + std::to_string((*it)->get_id());
            show_union_find_aux(uf, lst, *it, str, prefix + "     " + std::string(((*it)->get_id()) % 10, ' '));
        }
    }

    //
    return str;
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
bool hashTest_fillList();

// AVL TESTS
bool createAVL();
bool balanceAVL_LL();
bool balanceAVL_RR();
bool balanceAVL_LR();
bool balanceAVL_RL();
bool find_test();
bool remove_test();

// UNION FIND TESTS
bool basic_cards_and_UF();
bool unionFind_basic();
bool unionFindTest_show_union_find();

// WORLCUP TESTS
bool worldcup_basic();
bool worldcup_addTeam();
bool worldcup_removeTeam_basic(); // TODO: Make one that's more updated when add/remove player gets implemented
bool worldcup_add_player();
bool worldcup_play_match_noPermutation();
bool worldcup_play_match();
bool worldcup_get_partial_spirit();

#endif