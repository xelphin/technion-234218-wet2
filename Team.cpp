#include "Team.h"

Team::Team(int teamId)
: teamId(teamId), total_players(0)
{}

int Team::get_id() const
{
    return this->teamId;
}
int Team::operator ID() const {
    return get_id();
}

int Team::operator SCORE(const Team& other) const {
    // TODO: Check if needed, if yes, then implement, otherwise, erase all SCORE functions here, Player and AVL_tree
    return 0;
}
int Team::compare(const Team& team2) const
{
    return this->teamId - team2.get_id();
}
int Team::compare(const Team& team2, bool sort_by_score) const
{
    if (sort_by_score == SORT_BY_SCORE){
        int score_diff = 0; // TODO: Implement
        if (score_diff != 0)
            return score_diff;
        else
            return Team::get_id() - team2.get_id();
    }
    else
    {
        return Team::get_id() - team2.get_id();
    }
}

// DEBUGGING

std::ostream& operator<<(std::ostream& os, const Team& toPrint)
{
    os << std::to_string(toPrint.get_id());
    return os;
}

UnionFind<Player>::Node Team::set_captain_node(UnionFind<Player>::Node new_captain_node) {
    captain_node = captain_node;
    return captain_node;
}
