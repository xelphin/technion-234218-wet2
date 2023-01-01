#ifndef TEAM_H
#define TEAM_H


#include "UnionFind.h"
#include "Player.h"
#include "AVL_tree.h"
#include "wet2util.h"
#include <memory>


//template<class T>
//class UnionFind; 
class Player;

class Team{
public:
    Team(int teamId);
    // TODO: D'tor might throw logic error if removed when there are players that belong to it

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

    UnionFind<Player>::Node* set_captain_node(UnionFind<Player>::Node* new_captain_node); // TODO: Shouln't this be <std::shared_ptr<Player>>?
    UnionFind<Player>::Node* get_captain_node();
    int get_totalPlayers() const;
    int get_sumPlayerAbilities() const;
    int get_points() const;
    int get_spirit_strength() const;
    int get_team_games() const;
    void update_status_to_exist_goalKeeper();
    void add_team_points(int add);
    void increment_team_games();


    // DEBUGGING
    friend std::ostream& operator<<(std::ostream& os, const Team& team);


private:
    int teamId;
    int total_players;
    int sum_player_abilities;
    int points;
    int current_accumalated_spirit;
    UnionFind<Player>::Node* captain_node;
    bool hasGoalKeeper;
    int team_games;
    
};

#endif // TEAM_H