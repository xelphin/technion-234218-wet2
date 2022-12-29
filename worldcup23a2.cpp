#include "worldcup23a2.h"

world_cup_t::world_cup_t() : teams_AVL(SORT_BY_ID), teams_ability_AVL(SORT_BY_SCORE)
{
	// TODO: Your code goes here
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
}

StatusType world_cup_t::add_team(int teamId) // O(log(k))
{

	if (teamId <= 0){
        return StatusType::INVALID_INPUT;
	}
    try {
        std::shared_ptr<Team> team(new Team(teamId));
        if (team == nullptr){
            throw std::logic_error("If an allocation error wasn't thrown, then it shouldn't be nullptr");
        }
        teams_AVL.add(team);
		teams_ability_AVL.add(team);
	} catch (std::bad_alloc const&){
        return StatusType::ALLOCATION_ERROR;
	} catch (const ID_ALREADY_EXISTS& e) {
        return StatusType::FAILURE;
    }
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
    bool removed_avl_id = false;
	bool removed_avl_ability = false;
    if (teamId <=0) {
        return StatusType::INVALID_INPUT;
    }
	try {
        Team* team = &(*(teams_AVL.get_content(teamId))); // O(log(k))
        if (team != nullptr) {
            if (team->get_totalPlayers() > 0){
                return StatusType::FAILURE;
			}
            removed_avl_id = teams_AVL.remove(teamId);
            removed_avl_ability = teams_ability_AVL.remove(teamId);
        }
        else{
            return StatusType::FAILURE;
        }
    } catch (std::bad_alloc const& ) {
        return StatusType::ALLOCATION_ERROR;
    }
	if ((removed_avl_id && !removed_avl_ability) || (!removed_avl_id && removed_avl_ability)) {
		throw std::logic_error("Can't be that a team existed (and was removed) from only one AVL");
	}
    return removed_avl_id ? StatusType::SUCCESS : StatusType::FAILURE;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
	// TODO: Your code goes here
	return 22;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_team_points(int teamId)
{
	// TODO: Your code goes here
	return 30003;
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// TODO: Your code goes here
	return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
	// TODO: Your code goes here
	return permutation_t();
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
