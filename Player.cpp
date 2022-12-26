#include "Player.h"

Player::Player(int playerId, int teamId, const permutation_t &spirit, int gamesPlayed, int ability, int cards, bool goalKeeper) 
: playerId(playerId), teamId(teamId), spirit(spirit), gamesPlayed(gamesPlayed), cards(cards),
goalKeeper(goalKeeper), team(nullptr)

{}

int Player::get_id() const
{
    return this->playerId;
}
int Player::get_teamId() const
{
    return this->teamId;
}
int Player::get_gamesPlayed() const
{
    return this->gamesPlayed;
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

// DEBUGGING FUNCTIONS

std::ostream& operator<<(std::ostream& os, const Player& toPrint)
{
    os << std::to_string(toPrint.get_id());
    return os;
}