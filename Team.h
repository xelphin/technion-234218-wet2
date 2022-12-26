#ifndef TEAM_H
#define TEAM_H

#include "Player.h"
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


    // DEBUGGING
    friend std::ostream& operator<<(std::ostream& os, const Team& team);


private:
    int teamId;
    int total_players;
};

#endif // TEAM_H