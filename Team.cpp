#include "Team.h"

Team::Team(int teamId)
: teamId(teamId), total_players(0)
{}

int Team::get_id() const
{
    return this->teamId;
}

int Team::compare(const Team& team2) const
{
    return this->teamId - team2.get_id();
}

// DEBUGGING

std::ostream& operator<<(std::ostream& os, const Team& toPrint)
{
    os << std::to_string(toPrint.get_id());
    return os;
}
