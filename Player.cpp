#include "Player.h"

Player::Player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed, int ability, int cards, bool goalKeeper) 
: playerId(playerId), teamId(teamId), spirit(spirit), gamesPlayed(gamesPlayed), cards(cards),
goalKeeper(goalKeeper), team(nullptr)

{}

int Player::get_id() const
{
    return this->playerId;
}
int Player::operator ID() const {
    return get_id();
}
int Player::operator SCORE(const Player& other) const {
    // TODO: Check if i even need a score comparison, if not, then erase need for this in here, teams and AVL implementation
    return 0;
}
int Player::get_teamId() const
{
    return this->teamId;
}
int Player::get_gamesPlayed(int team_games) const
{
    // TODO
    return this->gamesPlayed + team_games - team_games_played_when_joined;
}
int Player::get_ability() const
{
    return this->ability;
}
int Player::get_cards() const
{
    return this->cards;
}
bool Player::get_isGoalKeeper() const
{
    return this->goalKeeper;
}

int Player::compare(const Player& player2) const
{
    return this->playerId - player2.get_id();
}
int Player::compare(const Player& player2, bool sort_by_score) const
{
    if (this->get_id() == player2.get_id()){
        throw; // THROW something that can be caught (use Exception.h or something)
    }
    if (sort_by_score == SORT_BY_SCORE){
        int score_diff = 0; // TODO: Implement properly if score is needed
        if (score_diff != 0)
            return score_diff;
        else // if scores are identical, compare id. one id has to be bigger than the other since its different players.
            return this->get_id() - player2.get_id();
    }
    else
    {
        return Player::get_id() - player2.get_id();
    }
}
void Player::set_team_games_played_when_joined(int team_games)
{
    // Happens only when a player is added to a Team (can also be used when bought)
    if (team_games < 0) {
        throw std::logic_error("Invalid input of team_games");
    }
    this->team_games_played_when_joined = team_games;
}
void Player::set_team(Team* team)
{
    this->team = team;
}

// DEBUGGING FUNCTIONS

std::ostream& operator<<(std::ostream& os, const Player& toPrint)
{
    os << std::to_string(toPrint.get_id());
    return os;
}

void Player::add_cards(int extra_cards) {
    cards += extra_cards;
}
