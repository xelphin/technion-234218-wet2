#include "developer_tests.h"

#ifdef NDEBUG // I DONT want to debug
void printFail ();
void printSuccess ();
#define printFail() ((void)0)
#define printSuccess() ((void)0)
#else // I DO want to debug
#define printFail() (std::cout << test_name << " FAILED." << std::endl)
#define printSuccess() (std::cout << "-------------------" << std::endl << test_name << " SUCCESS." << std::endl << "-------------------" << std::endl)
#endif

#include <cassert>


bool run_all_tests() {
    std::string success_string = "ALL (OUR) TESTS SUCCEEDED";
    bool success = true;

    run_test(system_basic, "system_basic", success_string, success);
    run_test(player_basic, "player_basic", success_string, success);
    run_test(team_basic, "team_basic", success_string, success);
    run_test(nodeList_basic, "nodeList_basic", success_string, success);
    run_test(nodeList_find, "nodeList_find", success_string, success);
    run_test(nodeList_popStart, "nodeList_popStart", success_string, success);
    run_test(hash_basic, "hash_basic", success_string, success);
    run_test(hash_add, "hash_add", success_string, success);
    run_test(hash_find, "hash_find", success_string, success);

    std::cout << success_string << std::endl;
    return success;
}


void run_test(std::function<bool()> test, std::string test_name, std::string& success_string, bool& success)
{
    if(!test()){
        printFail();
        std::cout << std::endl;
        success_string = "FAILED TEST: " + test_name;
        success = false;
        return;
    }
    printSuccess();
    std::cout << std::endl;
}



// ----------------------------- TESTS -----------------------------


bool system_basic()
{
    return true;
}

bool player_basic()
{
    permutation_t per;
    Player player1(1, 1, per, 1, 1, 1, false);
    return true;

}

bool team_basic()
{
    Team team(1);
    return true;
}

bool nodeList_basic()
{
    permutation_t per;
    std::shared_ptr<Player> player1(new Player(1, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player2(new Player(2, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player3(new Player(3, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player4(new Player(4, 1, per, 1, 1, 1, false));

    NodeList<Player> lst;

    //

    lst.add(player1);
    lst.add(player2);
    lst.add(player3);
    lst.add(player4);

    //

    return (lst.strList().compare("1 2 3 4"));
}

bool nodeList_find()
{
    int tests = 0;
    permutation_t per;
    std::shared_ptr<Player> player1(new Player(1, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player2(new Player(2, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player3(new Player(3, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player4(new Player(4, 1, per, 1, 1, 1, false));

    NodeList<Player> lst;

    //

    lst.add(player1);
    lst.add(player2);
    lst.add(player3);
    lst.add(player4);

    //

    tests += (lst.find(2) == player2);
    tests += (lst.find(5) == nullptr);
    tests += (lst.find(1) == player1);
    tests += (lst.find(4) == player4);

    return tests == 4;
}

bool nodeList_popStart()
{

    int tests = 0;
    permutation_t per;
    std::shared_ptr<Player> player1(new Player(1, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player2(new Player(2, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player3(new Player(3, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player4(new Player(4, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player5(new Player(5, 1, per, 1, 1, 1, false));

    NodeList<Player> lst;

    //

    lst.add(player1);
    tests += (lst.popStart() == player1);
    tests += (lst.popStart() == nullptr);
    lst.add(player2);
    lst.add(player3);
    lst.add(player4);
    tests += (lst.strList().compare("2 3 4 ") == 0);
    tests += (lst.popStart() == player2);
    tests += (lst.popStart() == player3);
    tests += (lst.strList().compare("4 ") == 0);
    lst.add(player5);
    tests += (lst.strList().compare("4 5 ") == 0);

    return tests == 7;
}

bool hash_basic()
{
    Hash<Player> hash1;
    Hash<Player> hash2(10);

    return true;
}

bool hash_add()
{
    Hash<Player> hash(3);

    permutation_t per;
    std::shared_ptr<Player> player1(new Player(1, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player3(new Player(3, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player4(new Player(4, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player5(new Player(5, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player6(new Player(6, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player8(new Player(8, 1, per, 1, 1, 1, false));

    hash.add(player1);
    std::cout << hash.allLists();

    hash.add(player3);

    std::cout << hash.allLists();
    hash.add(player4);

    std::cout << hash.allLists();
    hash.add(player5);

    std::cout << hash.allLists();
    hash.add(player6);

    std::cout << hash.allLists();
    hash.add(player8);

    std::cout << hash.allLists();

    return true;
}

bool hash_find()
{
    int tests = 0;
    Hash<Player> hash(3);

    permutation_t per;
    std::shared_ptr<Player> player1(new Player(1, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player3(new Player(3, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player4(new Player(4, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player5(new Player(5, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player6(new Player(6, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player8(new Player(8, 1, per, 1, 1, 1, false));

    hash.add(player1);
    hash.add(player3);
    hash.add(player4);
    hash.add(player5);
    hash.add(player6);
    hash.add(player8);

    std::cout << hash.allLists();

    tests += (hash.find(2) == nullptr);
    tests += (hash.find(3) == player3);

    return tests == 2;
}