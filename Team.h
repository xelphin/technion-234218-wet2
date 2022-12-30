#ifndef TEAM_H
#define TEAM_H

#include "Player.h"
#include "UnionFind.h"
#include "AVL_tree.h"
#include "wet2util.h"
#include <memory>

class Player;

class Team{
public:
    Team(int teamId);

    int get_id() const;

    /*
    * Return called team ID minus argument team ID
    * @param team2 - Team object (argument team)
    * @return value of our team - team2
    */
    int compare(const Team& team2) const;
    int compare(const Team& team2, bool sort_by_score) const;

    int operator ID() const;
    int operator SCORE(const Team& other) const;

    UnionFind<Player>::Node* set_captain_node(UnionFind<Player>::Node* new_captain_node);
    UnionFind<Player>::Node* get_captain_node();

    // DEBUGGING
    friend std::ostream& operator<<(std::ostream& os, const Team& team);


private:
    int teamId;
    int total_players;
    UnionFind<Player>::Node* captain_node;
};

#endif // TEAM_H