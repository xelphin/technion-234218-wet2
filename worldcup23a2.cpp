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
            team->remove_team_players();
            removed_avl_id = teams_AVL.remove(teamId);
            removed_avl_ability = teams_ability_AVL.remove(teamId);
        }
        else{
            return StatusType::FAILURE;
        }
    } catch (std::bad_alloc const& ) {
        return StatusType::ALLOCATION_ERROR;
    }
	if (removed_avl_id != removed_avl_ability) {
		throw std::logic_error("Can't be that a team existed (and was removed) from only one AVL");
	}
    return removed_avl_id ? StatusType::SUCCESS : StatusType::FAILURE;
}

StatusType world_cup_t::add_player(int playerId, int teamId,
                                   const permutation_t &spirit, int gamesPlayed,
                                   int ability, int cards, bool goalKeeper)
{
    if(playerId <= 0 || teamId <=0 || gamesPlayed < 0 || cards < 0){
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Team> team = teams_AVL.get_content(teamId);
    if (team && !players_UF.id_is_in_data(playerId))
    {
        std::shared_ptr<UnionFind<Player>::Node> new_node = std::make_shared<UnionFind<Player>::Node>(
            Player(playerId, teamId, spirit, gamesPlayed, ability, cards, goalKeeper), spirit);
        if (new_node == nullptr) {
            return StatusType::FAILURE;
        }
        players_UF.makeset(new_node, team->get_captain_node());
        if (team->get_captain_node() == nullptr) { // TODO: Check correct implementation
            team->set_captain_node(&*new_node);
        }
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
	// TODO: This is a basic implementation, when class becomes more implemented, then maybe revist and check
    // CHECK INVALID - O(1)
    if(teamId <= 0)
        return StatusType::INVALID_INPUT;
    // FIND TEAM - O(log(k))
    Team* team = &(*(teams_AVL.get_content(teamId)));
    // GET TEAM POINTS - O(1)
    if (team == nullptr) {
        return StatusType::FAILURE;
    }
	return team->get_points();
}

output_t<int> world_cup_t::get_ith_pointless_ability(int i)
{
	// TODO: Your code goes here
	return 12345;
}

output_t<permutation_t> world_cup_t::get_partial_spirit(int playerId)
{
    if (playerId <= 0){
        return StatusType::INVALID_INPUT;
    }

    if (players_UF.get_partial_spirit(playerId).isvalid()){
        return players_UF.get_partial_spirit(playerId);
    }
    return StatusType::FAILURE;
}

StatusType world_cup_t::buy_team(int teamId1, int teamId2)
{
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }
    std::shared_ptr<Team> team1 = teams_AVL.get_content(teamId1);
    std::shared_ptr<Team> team2 = teams_AVL.get_content(teamId2);
    if (team1 == nullptr || team2 == nullptr){
        return StatusType::FAILURE;
    }

    team1->set_points(team1->get_points() + team2->get_points());
    team1->set_captain_node(players_UF.unite(team1->get_captain_node(), team2->get_captain_node()));
    //now the captain node is the root of the UF. it may be team2's captain if team2 was the bigger team. or a nullptr if no players.
    if (team1->get_captain_node() != nullptr){
        team1->set_team_spirit(team1->get_captain_node()->get_team_product());
    }
    teams_AVL.remove(teamId2);
    return StatusType::SUCCESS;
}
