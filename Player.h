#ifndef PLAYER_H
#define PLAYER_H

#include "Team.h"
#include "AVL_tree.h"
#include "wet2util.h"
#include <memory>


class Team;

class Player{
public:
    Player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed, int ability, int cards, bool goalKeeper);

    int get_id() const;
    int get_teamId() const;
    int get_gamesPlayed(int team_games) const;
    int get_ability() const;
    int get_cards() const;
    bool get_isGoalKeeper() const;

    Team* get_team() const;

    void set_team_games_played_when_joined(int team_games);
    void set_team(Team* team);

    /*
    * Return called player ID minus argument player ID
    * @param player2 - Player object (argument player)
    * @return value of our player - player2
    */
    int compare(const Player& player2) const;
    int compare(const Player& player2, bool sort_by_score) const;

    int operator SCORE(const Player&) const;
    int operator ID() const;

    // DEBUGGING FUNCTIONS
    friend std::ostream& operator<<(std::ostream& os, const Player& player);

private:
    int playerId;
    int teamId;
    permutation_t spirit; // TODO: Should it be a pointer? Don't think so...
    int gamesPlayed;
    int ability;
    int cards;
    bool goalKeeper;
    Team* team;
    int team_games_played_when_joined;
};





#endif // PLAYER_H
