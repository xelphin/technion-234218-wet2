#include "./developer_tests.h"

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
    run_test(nodeListPlayers_basic, "nodeListPlayers_basic", success_string, success);

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

bool nodeListPlayers_basic()
{
    permutation_t per;
    std::shared_ptr<Player> player1(new Player(1, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player2(new Player(2, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player3(new Player(3, 1, per, 1, 1, 1, false));
    std::shared_ptr<Player> player4(new Player(4, 1, per, 1, 1, 1, false));

    NodeList_Players lst;

    //

    lst.add(player1);
    lst.add(player2);
    lst.add(player3);
    lst.add(player4);

    //

    return (lst.strList().compare("1 2 3 4"));
}