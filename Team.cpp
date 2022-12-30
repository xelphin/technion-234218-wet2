#include "Team.h"

Team::Team(int teamId)
: teamId(teamId), total_players(0), sum_player_abilities(0), points(0), current_accumalated_spirit(1)
{}

int Team::get_id() const
{
    return this->teamId;
}
int Team::operator ID() const {
    return get_id();
}

int Team::operator SCORE(const Team& other) const {
    int ability_diff = this->sum_player_abilities - other.get_sumPlayerAbilities();
    if (ability_diff != 0) {
        return ability_diff;
    }
    return teamId - other.get_id(); // TODO: I'm pretty sure this is right, even though it wasn't this way in wet1.
}
int Team::compare(const Team& team2) const
{
    return this->teamId - team2.get_id();
}
int Team::compare(const Team& team2, bool sort_by_score) const
{
    if (sort_by_score == SORT_BY_SCORE){
        int score_diff = sum_player_abilities - team2.get_sumPlayerAbilities();
        if (score_diff != 0)
            return score_diff;
        else
            return Team::get_id() - team2.get_id(); // TODO: Pretty sure this else is useless if you just take the 'return' below out of the else
    }
    else
    {
        return Team::get_id() - team2.get_id();
    }
}
int Team::get_totalPlayers() const
{
    return this->total_players;
}
int Team::get_sumPlayerAbilities() const
{
    return this->sum_player_abilities;
}
int Team::get_points() const
{
    return this->points;
}
// DEBUGGING

std::ostream& operator<<(std::ostream& os, const Team& toPrint)
{
    os << std::to_string(toPrint.get_id());
    return os;
}
