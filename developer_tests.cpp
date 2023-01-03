#include "developer_tests.h"
#include <cassert>

#ifdef NDEBUG // I DONT want to debug
void printFail ();
void printSuccess ();
#define printFail() ((void)0)
#define printSuccess() ((void)0)
#else // I DO want to debug
#define printFail() (std::cout << test_name << " FAILED." << std::endl)
#define printSuccess() (std::cout << "-------------------" << std::endl << test_name << " SUCCESS." << std::endl << "-------------------" << std::endl)
#endif


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
    run_test(createAVL, "createAVL", success_string, success);
    run_test(balanceAVL_LL, "balanceAVL_LL", success_string, success);
    run_test(balanceAVL_LR, "balanceAVL_LR", success_string, success);
    run_test(balanceAVL_RL, "balanceAVL_RL", success_string, success);
    run_test(find_test, "get_content", success_string, success);
    run_test(remove_test, "remove", success_string, success);
    run_test(worldcup_basic, "worldcup_basic", success_string, success);
    run_test(worldcup_addTeam, "worldcup_addTeam", success_string, success);
    run_test(worldcup_removeTeam_basic, "worldcup_removeTeam_basic", success_string, success);
    run_test(basic_cards_and_UF, "basic_cards_and_UF", success_string, success);
    run_test(hashTest_fillList, "hashTest_fillList", success_string, success);
    run_test(unionFind_basic, "unionFind_basic", success_string, success);
    run_test(unionFindTest_show_union_find, "unionFindTest_show_union_find", success_string, success);
    run_test(worldcup_add_player, "worldcup_add_player", success_string, success);
    run_test(worldcup_play_match_noPermutation, "worldcup_play_match_noPermutation", success_string, success);
    run_test(worldcup_get_partial_spirit, "worldcup_get_partial_spirit", success_string, success);

    std::cout << success_string << std::endl;
    return success;
}


void run_test(std::function<bool()> test, std::string test_name, std::string& success_string, bool& success)
{
    std::cout << test_name << " \n";
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

bool treeCompare(const std::string& tree, const std::string& wantedTree)
{
    if (wantedTree.compare(tree) == 0)
        return true;
    return false;
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

bool hashTest_fillList()
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
    hash.add(player3);
    hash.add(player4);
    hash.add(player5);
    hash.add(player6);
    hash.add(player8);
    std::cout << hash.allLists();
    //
    std::list<std::shared_ptr<Player>> lst;
    Hash_Tests<Player>::fill_list(hash, lst);
    //
    std::list<std::shared_ptr<Player>>::iterator it;
    std::string str = "";
    for (it = lst.begin(); it != lst.end(); ++it){
        str += std::to_string((*it)->get_id()) + " ";
    }
    std::cout<< str << std::endl;
    return (str.compare("1 8 3 4 5 6 ") == 0);
}

bool createAVL()
{
    int tests = 0;
    AVL_tree<Player*> tree1(false); // sort by ID
    permutation_t per;
    Player player1(4, 1, per, 1, 1, 1, false); // id: 4
    Player player2(1, 1, per, 1, 1, 1, false); // id: 1
    Player player3(7, 1, per, 1, 1, 1, false); // id: 7
    Player player4(3, 1, per, 1, 1, 1, false); // id: 3
    tree1.add(&player1);
    std::cout << tree1.debugging_printTree_new();
    tree1.add(&player2);
    std::cout << tree1.debugging_printTree_new();
    tree1.add(&player3);
    std::cout << tree1.debugging_printTree_new();
    tree1.add(&player4);

    std::string finalTree = tree1.debugging_printTree();
    std::cout << finalTree;
    std::string wantedTree = "└──4\n    ├──1\n    │   └──3\n    └──7\n";
    tests += treeCompare(finalTree,wantedTree);

    std::cout << "amount of nodes " << std::to_string(tree1.get_amount()) << std::endl;
    tests += (tree1.get_amount() == 4);

    return tests == 2;
}

bool balanceAVL_LL()
{
    AVL_tree<Player*> tree1(false); // sort by ID
    permutation_t per;
    Player player1(8, 1, per, 1, 1, 1, false); // id: 8
    Player player2(5, 1, per, 1, 1, 1, false); // id: 5
    Player player3(3, 1, per, 1, 1, 1, false); // id: 3
    Player player4(2, 1, per, 1, 1, 1, false); // id: 2
    Player player5(1, 1, per, 1, 1, 1, false); // id: 1
    tree1.add(&player1);
    tree1.add(&player2);
    tree1.add(&player3);
    tree1.add(&player4);
    tree1.add(&player5);

    std::string finalTree = tree1.debugging_printTree();
    std::cout << finalTree;
    std::string wantedTree = "└──5\n    ├──2\n    │   ├──1\n    │   └──3\n    └──8\n";

    return treeCompare(finalTree,wantedTree);
}

bool balanceAVL_RR()
{
    AVL_tree<Player*> tree1(false); // sort by ID
    permutation_t per;
    Player player1(1, 1, per, 1, 1, 1, false); // id: 1
    Player player2(2, 1, per, 1, 1, 1, false); // id: 2
    Player player3(3, 1, per, 1, 1, 1, false); // id: 3
    Player player4(4, 1, per, 1, 1, 1, false); // id: 4
    Player player5(5, 1, per, 1, 1, 1, false); // id: 5
    Player player6(6, 1, per, 1, 1, 1, false); // id: 6
    Player player7(7, 1, per, 1, 1, 1, false); // id: 7
    tree1.add(&player1);
    tree1.add(&player2);
    tree1.add(&player3);
    tree1.add(&player4);
    tree1.add(&player5);
    tree1.add(&player6);
    tree1.add(&player7);

    std::string finalTree = tree1.debugging_printTree();
    std::cout << finalTree;
    std::string wantedTree = "└──4\n    ├──2\n    │   ├──1\n    │   └──3\n    └──6\n        ├──5\n        └──7\n";

    return treeCompare(finalTree,wantedTree);
}

bool balanceAVL_LR()
{
    AVL_tree<Player*> tree1(false); // sort by ID
    permutation_t per;
    Player player2(2, 1, per, 1, 1, 1, false); // id: 2
    Player player3(3, 1, per, 1, 1, 1, false); // id: 3
    Player player4(4, 1, per, 1, 1, 1, false); // id: 4
    Player player5(5, 1, per, 1, 1, 1, false); // id: 5
    Player player6(6, 1, per, 1, 1, 1, false); // id: 6
    Player player7(7, 1, per, 1, 1, 1, false); // id: 7
    Player player8(8, 1, per, 1, 1, 1, false); // id: 8
    Player player10(10, 1, per, 1, 1, 1, false); // id: 10
    Player player20(20, 1, per, 1, 1, 1, false); // id: 20
    Player player21(21, 1, per, 1, 1, 1, false); // id: 21
    tree1.add(&player10);
    tree1.add(&player4);
    tree1.add(&player20);
    tree1.add(&player21);
    tree1.add(&player3);
    tree1.add(&player7);
    tree1.add(&player2);
    tree1.add(&player6);
    tree1.add(&player8);
    std::cout << tree1.debugging_printTree_new();
    //
    tree1.add(&player5);
    //
    std::string finalTree = tree1.debugging_printTree();
    std::cout << finalTree;
    std::string wantedTree = "└──7\n    ├──4\n    │   ├──3\n    │   │   ├──2\n    │   └──6";
    wantedTree += "\n    │       ├──5\n    └──10\n        ├──8\n        └──20\n            └──21\n";

    return treeCompare(finalTree,wantedTree);
}

bool balanceAVL_RL()
{
    AVL_tree<Player*> tree1(false); // sort by ID
    permutation_t per;
    Player player10(10, 1, per, 1, 1, 1, false);
    Player player5(5, 1, per, 1, 1, 1, false);
    Player player20(20, 1, per, 1, 1, 1, false);
    Player player4(4, 1, per, 1, 1, 1, false);
    Player player6(6, 1, per, 1, 1, 1, false);
    Player player15(15, 1, per, 1, 1, 1, false);
    Player player30(30, 1, per, 1, 1, 1, false);
    Player player12(12, 1, per, 1, 1, 1, false);
    Player player18(18, 1, per, 1, 1, 1, false);
    Player player25(25, 1, per, 1, 1, 1, false);
    Player player40(40, 1, per, 1, 1, 1, false);
    //
    Player player19(19, 1, per, 1, 1, 1, false);
    //
    tree1.add(&player10);
    tree1.add(&player5);
    tree1.add(&player20);
    tree1.add(&player4);
    tree1.add(&player6);
    tree1.add(&player15);
    tree1.add(&player30);
    tree1.add(&player12);
    tree1.add(&player18);
    tree1.add(&player25);
    tree1.add(&player40);
    std::cout << tree1.debugging_printTree_new();
    //
    tree1.add(&player19);
    //
    std::string finalTree = tree1.debugging_printTree();
    std::cout << finalTree;
    std::string wantedTree = "└──15\n    ├──10\n    │   ├──5\n    │   │   ├──4\n    │   │   └──6\n    │   └──12\n    └──20\n        ├──18";
    wantedTree += "\n        │   └──19\n        └──30\n            ├──25\n            └──40\n";

    return treeCompare(finalTree,wantedTree);
}

bool find_test() {
    AVL_tree<Player*> tree1(false); // sort by ID
    permutation_t per;
    Player player10(10, 1, per, 1, 1, 1, false);
    Player player5(5, 1, per, 1, 1, 1, false);
    Player player20(20, 1, per, 1, 1, 1, false);
    Player player4(4, 1, per, 1, 1, 1, false);
    Player player6(6, 1, per, 1, 1, 1, false);
    Player player15(15, 1, per, 1, 1, 1, false);
    Player player30(30, 1, per, 1, 1, 1, false);
    Player player12(12, 1, per, 1, 1, 1, false);
    Player player18(18, 1, per, 1, 1, 1, false);
    Player player25(25, 1, per, 1, 1, 1, false);
    Player player40(40, 1, per, 1, 1, 1, false);
    //
    Player player19(19, 1, per, 1, 1, 1, false);
    //
    tree1.add(&player10);
    tree1.add(&player5);
    tree1.add(&player20);
    tree1.add(&player4);
    tree1.add(&player6);
    tree1.add(&player15);
    tree1.add(&player30);
    tree1.add(&player12);
    tree1.add(&player18);
    tree1.add(&player25);
    tree1.add(&player40);
    tree1.add(&player19);
    //
    std::string finalTree = tree1.debugging_printTree();
    std::cout << finalTree;

    std::cout << "get_content test, id range: 1-11\n";
    for (int id = 1; id <= 11; ++id) {
        tree1.find_test_wrapper(id);
    }

    return true;
}

bool remove_test() {
    AVL_tree<Player*> tree1(false); // sort by ID
    permutation_t per;
    Player player10(10, 1, per, 1, 1, 1, false);
    Player player5(5, 1, per, 1, 1, 1, false);
    Player player20(20, 1, per, 1, 1, 1, false);
    Player player4(4, 1, per, 1, 1, 1, false);
    Player player6(6, 1, per, 1, 1, 1, false);
    Player player15(15, 1, per, 1, 1, 1, false);
    Player player30(30, 1, per, 1, 1, 1, false);
    Player player12(12, 1, per, 1, 1, 1, false);
    Player player18(18, 1, per, 1, 1, 1, false);
    Player player25(25, 1, per, 1, 1, 1, false);
    Player player40(40, 1, per, 1, 1, 1, false);
    //
    Player player19(19, 1, per, 1, 1, 1, false);
    //
    tree1.add(&player10);
    tree1.add(&player5);
    tree1.add(&player20);
    tree1.add(&player4);
    tree1.add(&player6);
    tree1.add(&player15);
    tree1.add(&player30);
    tree1.add(&player12);
    tree1.add(&player18);
    tree1.add(&player25);
    tree1.add(&player40);
    tree1.add(&player19);
    //
    std::string finalTree = tree1.debugging_printTree();
    std::cout << finalTree;
    //tree1.in_order_traversal_wrapper(AVL_tree<Player*>::print_node);

    std::cout << "remove test: \n";
    std::cout << "remove test, id range: 9-20\n";
    for (int id = 9; id <= 20; ++id) {
        std::cout << "-----------------------REMOVAL. id: " << id << std::endl;
        if(tree1.remove(id)){
            //tree1.in_order_traversal_wrapper(AVL_tree<Player*>::print_node);
            finalTree = tree1.debugging_printTree();
            std::cout << finalTree;
        }
    }
    finalTree = tree1.debugging_printTree();
    std::cout << finalTree;

    return tree1.get_amount() == 6;
}

bool unionFind_basic()
{
    UnionFind<Player> uf;
    std::shared_ptr<Team> team(new Team(1));
    permutation_t per;
    // Captain
    std::shared_ptr<UnionFind<Player>::Node> captain = std::make_shared<UnionFind<Player>::Node>(
            Player(1, 1, per, 2, 3, 0, true), per);
    uf.makeset(captain, team->get_captain_node());
    team->set_captain_node(&*captain);
    // Others
    std::shared_ptr<UnionFind<Player>::Node> node2 = std::make_shared<UnionFind<Player>::Node>(
        Player(2, 1, per, 2, 3, 0, true), per);
    uf.makeset(node2, team->get_captain_node());
    std::shared_ptr<UnionFind<Player>::Node> node3 = std::make_shared<UnionFind<Player>::Node>(
        Player(3, 1, per, 2, 3, 0, true), per);
    uf.makeset(node3, team->get_captain_node());
    //
    std::cout << UnionFind_Tests<Player>::show_hash(uf);
    std::cout << UnionFind_Tests<Player>::show_team_captains(uf) << std::endl;
    std::cout << UnionFind_Tests<Player>::show_union_find(uf) << std::endl;
    //
    return true;
}

bool unionFindTest_show_union_find()
{
    UnionFind<Player> uf;
    std::shared_ptr<Team> team1(new Team(1));
    std::shared_ptr<Team> team2(new Team(2));
    permutation_t per = permutation_t::neutral();

    // Captain 1
    std::shared_ptr<UnionFind<Player>::Node> captain1 = std::make_shared<UnionFind<Player>::Node>(
            Player(11, 1, per, 2, 3, 0, true), per);
    uf.makeset(captain1, team1->get_captain_node());
    team1->set_captain_node(&*captain1);

    // Others
    std::shared_ptr<UnionFind<Player>::Node> node12 = std::make_shared<UnionFind<Player>::Node>(
        Player(12, 1, per, 2, 3, 0, true), per);
    uf.makeset(node12, team1->get_captain_node());
    std::shared_ptr<UnionFind<Player>::Node> node13 = std::make_shared<UnionFind<Player>::Node>(
        Player(13, 1, per, 2, 3, 0, true), per);
    uf.makeset(node13, team1->get_captain_node());
    std::shared_ptr<UnionFind<Player>::Node> node14 = std::make_shared<UnionFind<Player>::Node>(
        Player(14, 1, per, 2, 3, 0, true), per);
    uf.makeset(node14, team1->get_captain_node());

    // Captain 2
    std::shared_ptr<UnionFind<Player>::Node> captain2 = std::make_shared<UnionFind<Player>::Node>(
            Player(21, 2, per, 2, 3, 0, true), per);
    uf.makeset(captain2, team2->get_captain_node());
    team2->set_captain_node(&*captain2);

    // Others
    std::shared_ptr<UnionFind<Player>::Node> node22 = std::make_shared<UnionFind<Player>::Node>(
        Player(22, 2, per, 2, 3, 0, true), per);
    uf.makeset(node22, team2->get_captain_node());
    std::shared_ptr<UnionFind<Player>::Node> node23 = std::make_shared<UnionFind<Player>::Node>(
        Player(23, 2, per, 2, 3, 0, true), per);
    uf.makeset(node23, team2->get_captain_node());
    //
    std::cout << UnionFind_Tests<Player>::show_union_find(uf) << std::endl;

    // Unite
    std::cout << "Uniting Teams" << std::endl;
    uf.unite(team2->get_captain_node(), team1->get_captain_node()); // TODO: Fix permutation causes memory leak here
    std::cout << UnionFind_Tests<Player>::show_union_find(uf) << std::endl;

    // Add more players
    std::shared_ptr<UnionFind<Player>::Node> node15 = std::make_shared<UnionFind<Player>::Node>(
        Player(15, 1, per, 2, 3, 0, true), per);
    uf.makeset(node15, team1->get_captain_node());
    std::cout << UnionFind_Tests<Player>::show_union_find(uf) << std::endl;

    return true;
}

bool basic_cards_and_UF(){
    UnionFind<Player> uf;

    permutation_t neutral = permutation_t::neutral();
    uf.makeset(std::make_shared<UnionFind<Player>::Node>(Player(1,1,neutral,0,5,5, true),neutral), nullptr);
    uf.makeset(std::make_shared<UnionFind<Player>::Node>(Player(2,1,neutral,0,5,5, true),neutral), nullptr);
    uf.makeset(std::make_shared<UnionFind<Player>::Node>(Player(3,1,neutral,0,5,5, true),neutral), nullptr);
    uf.unite(uf.find_set_of_id(1), uf.find_set_of_id(2));
    uf.unite(uf.find_set_of_id(3), uf.find_set_of_id(2));
    assert(uf.id_is_in_data(1) && uf.id_is_in_data(2) && uf.id_is_in_data(3));
    assert(uf.find_set_of_id(3) == uf.find_set_of_id(2) && uf.find_set_of_id(2) == uf.find_set_of_id(1));

    world_cup_t wc;
    wc.add_team(1);
    wc.add_player(3,1,neutral,0,5,5, true);
    wc.add_player(2,1,neutral,0,5,5, true);
    wc.add_player(1,1,neutral,0,5,5, true);
    wc.add_player(4,1,neutral,0,5,5, true);
    assert(wc.get_player_cards(1).ans() == output_t<int>(5).ans());
    wc.add_player_cards(2, 6);
    assert(wc.get_player_cards(2).ans() == output_t<int>(5+6).ans());

    return true;
}

bool worldcup_basic()
{
    world_cup_t worldCup;
    return true;
}

bool worldcup_addTeam()
{
    int test = 0;
    world_cup_t worldCup;
    test += StatusType::SUCCESS == worldCup.add_team(1);
    test += StatusType::FAILURE == worldCup.add_team(1);
    test += StatusType::INVALID_INPUT == worldCup.add_team(-1);
    test += StatusType::SUCCESS == worldCup.add_team(2);
    return test == 4;
}

bool worldcup_removeTeam_basic()
{
    // AVL tests for remove are assumed to be correct
    int tests = 0;
    world_cup_t worldCup;
    worldCup.add_team(1);
    worldCup.add_team(2);
    worldCup.add_team(3);
    worldCup.add_team(4);
    worldCup.add_team(5);
    worldCup.add_team(6);
    worldCup.add_team(7);
    worldCup.add_team(8);
    worldCup.add_team(9);
    //
    tests += StatusType::SUCCESS == worldCup.remove_team(3);
    tests += StatusType::SUCCESS == worldCup.remove_team(2);
    tests += StatusType::FAILURE == worldCup.remove_team(3);
    tests += StatusType::INVALID_INPUT == worldCup.remove_team(-2);
    //
    worldCup.add_team(3);
    tests += StatusType::SUCCESS == worldCup.remove_team(3);
    tests += StatusType::SUCCESS == worldCup.remove_team(4);
    tests += StatusType::FAILURE == worldCup.remove_team(3);
    return tests == 7;
}

bool worldcup_add_player()
{
    int test = 0;
    world_cup_t worldCup;
    // Teams
    test += StatusType::SUCCESS == worldCup.add_team(1);
    test += StatusType::SUCCESS == worldCup.add_team(2);
    test += StatusType::SUCCESS == worldCup.add_team(3);
    // Players
    permutation_t per;
    worldCup.add_player(11, 1, per, 2, 3, 4, true);
    worldCup.add_player(21, 2, per, 2, 3, 4, true);
    worldCup.add_player(12, 1, per, 2, 3, 4, true);
    worldCup.add_player(13, 1, per, 2, 3, 4, true);
    worldCup.add_player(14, 1, per, 2, 3, 4, true);
    worldCup.add_player(22, 2, per, 2, 3, 4, true);
    worldCup.add_player(23, 2, per, 2, 3, 4, true);
    worldCup.add_player(24, 2, per, 2, 3, 4, true);
    worldCup.add_player(31, 3, per, 2, 3, 4, true);
    worldCup.add_player(32, 3, per, 2, 3, 4, true);

    // Tests
    // std::cout << UnionFind_Tests<Player>::show_union_find(worldCup.players_UF) << std::endl; // TODO: Implement like this instead
    std::cout << worldCup.show_uf() << std::endl; // Above is better, but doesn't work even though I did friend
    std::string res = "Union Find: \n31\n  ---32\n21\n  ---22\n  ---23\n  ---24\n11\n  ---12\n  ---13\n  ---14\n";
    test += (worldCup.show_uf().compare(res) == 0);

    return test == 4;
}

bool worldcup_play_match_noPermutation()
{
    world_cup_t worldCup;
    // Teams
    worldCup.add_team(1);
    worldCup.add_team(2);
    worldCup.add_team(3);
    assert(worldCup.get_team_points(1).ans() == 0);
    assert(worldCup.get_team_points(2).ans() == 0);
    assert(worldCup.get_team_points(3).ans() == 0);
    // Players
    permutation_t per;
    worldCup.add_player(11, 1, per, 2, 3, 4, true); // Sum ability = 3
    worldCup.add_player(12, 1, per, 2, 0, 4, true);
    worldCup.add_player(13, 1, per, 2, 0, 4, true);
    worldCup.add_player(14, 1, per, 2, 0, 4, true);

    worldCup.add_player(21, 2, per, 2, 5, 4, true); // Sum ability = 5
    worldCup.add_player(22, 2, per, 2, 0, 4, true);
    worldCup.add_player(23, 2, per, 2, 0, 4, true);
    worldCup.add_player(24, 2, per, 2, 0, 4, true);

    worldCup.add_player(31, 3, per, 2, 7, 4, true); // Sum ability = 7
    worldCup.add_player(32, 3, per, 2, 0, 4, true);
    // UF
    std::cout << worldCup.show_uf() << std::endl;
    // Play Match
    worldCup.play_match(1,2);
    assert(worldCup.get_team_points(1).ans() == 0);
    assert(worldCup.get_team_points(2).ans() == 3);
    // Play Match
    worldCup.play_match(2,3);
    assert(worldCup.get_team_points(2).ans() == 6);
    assert(worldCup.get_team_points(3).ans() == 0);

    return true;
}

bool worldcup_get_partial_spirit()
{
    permutation_t per1 = permutation_t::neutral();
    int arr2[] = { 2, 3, 4, 0, 1};
    permutation_t per2(arr2);
    //
    world_cup_t worldCup;

    // Teams
    worldCup.add_team(1);
    worldCup.add_team(2);

    // Players + Tests

    worldCup.add_player(11, 1, per1, 2, 3, 4, true); // player11
    std::cout << "player 11: " << worldCup.get_partial_spirit(11).ans() << std::endl; // 1, 2, 3, 4, 5
    std::cout << "player 11: " << std::to_string(worldCup.get_partial_spirit(11).ans().strength()) << std::endl;
    assert(worldCup.get_partial_spirit(11).ans().strength() == 55);

    worldCup.add_player(12, 1, per1, 2, 0, 4, true); // player12
    std::cout << "player 12: " << worldCup.get_partial_spirit(12).ans() << std::endl; // 1, 2, 3, 4, 5
    std::cout << "player 12: " << std::to_string(worldCup.get_partial_spirit(12).ans().strength()) << std::endl;
    assert(worldCup.get_partial_spirit(12).ans().strength() == 55);

    worldCup.add_player(13, 1, per2, 2, 0, 4, true); // player13 (uses per2)
    std::cout << "player 13: " << worldCup.get_partial_spirit(13).ans() << std::endl; // 3, 4, 5, 1, 2
    std::cout << "player 13: " << std::to_string(worldCup.get_partial_spirit(13).ans().strength()) << std::endl;
    assert(worldCup.get_partial_spirit(13).ans().strength() == 40);

    worldCup.add_player(14, 1, per2, 2, 0, 4, true); // player14 (uses per2)
    std::cout << "player 14: " << worldCup.get_partial_spirit(14).ans() << std::endl; // 5, 1, 2, 3, 4 !!!
    std::cout << "player 14: " << std::to_string(worldCup.get_partial_spirit(14).ans().strength()) << std::endl;
    // assert(worldCup.get_partial_spirit(14).ans().strength() == 45);

    worldCup.add_player(21, 2, per1, 2, 5, 4, true); 
    worldCup.add_player(22, 2, per1, 2, 0, 4, true);
    worldCup.add_player(23, 2, per1, 2, 0, 4, true);
    worldCup.add_player(24, 2, per1, 2, 0, 4, true);

    // TODO: Check that an invalid permutation given to player will make worldcup act accordingly
    return true;
}