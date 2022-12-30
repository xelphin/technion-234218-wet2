#include "worldcup23a2.h"

#include <memory>

world_cup_t::world_cup_t() : teams_AVL(SORT_BY_ID), teams_ability_AVL(SORT_BY_SCORE), players_UF()
{
	// TODO: Your code goes here
}

world_cup_t::~world_cup_t()
{
	// TODO: Your code goes here
}

StatusType world_cup_t::add_team(int teamId) // O(log(k))
{
	std::cout << "------Starting new test:--------" << std::endl;

	if (teamId <= 0){
        return StatusType::INVALID_INPUT;
	}
    try {
        std::shared_ptr<Team> team(new Team(teamId));
        if (team == nullptr){
            throw;
        }
		std::cout << teams_AVL.debugging_printTree_new();
		std::cout << teams_ability_AVL.debugging_printTree_new();
        teams_AVL.add(team);
		// BUG: throws error if two teams have same ability score, shouldn't, only for same ID
		// teams_ability_AVL.add(team); //  TODO: Notice that the .compare compares ability, and that if two teams have equal ability to not throw error
    } catch (std::bad_alloc const&){
        return StatusType::ALLOCATION_ERROR;
    } catch (const ID_ALREADY_EXISTS& e) {
		std::cout << "Id "<< (teamId) << " already exists" << std::endl;

        return StatusType::FAILURE;
    }
	return StatusType::SUCCESS;
}

StatusType world_cup_t::remove_team(int teamId)
{
	// TODO: Your code goes here
	return StatusType::FAILURE;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
    if(playerId <= 0 || teamId <=0 || gamesPlayed < 0 || cards < 0){
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Team> team = teams_AVL.get_content(teamId);
    if (team && !players_UF.exists(playerId))
    {
        std::shared_ptr<UnionFind<Player>::Node> new_node = std::make_shared<UnionFind<Player>::Node>(
            Player(playerId, teamId, spirit, gamesPlayed, ability, cards, goalKeeper), spirit);
        players_UF.makeset(new_node, team->get_captain_node());
        return StatusType::SUCCESS;
    }
    else{
        return StatusType::FAILURE;
    }
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
	return players_UF.get_partial_spirit(playerId);
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}
