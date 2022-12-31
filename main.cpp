

#include "worldcup23a2.h"
#include "developer_tests.h" 
#include <string>
#include <iostream>


using namespace std;

// TODO: Erase this file later and make main23a2.cpp the main file
int main()
{
    world_cup_t worldCup;
    worldCup.add_team(1);
    int a[5];
    for (int i = 1; i < 6; ++i) {
        a[i-1] = i;
    }
    worldCup.add_player(10, 1, permutation_t(a), 5,5,5,true);
    worldCup.add_player(20, 1, permutation_t(a), 5,5,5,true);
    worldCup.add_player(30, 1, permutation_t(a), 5,5,5,true);


    run_all_tests();
}
