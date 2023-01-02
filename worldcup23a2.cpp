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
    // Check Input
    if(playerId <= 0 || teamId <=0 || gamesPlayed < 0 || cards < 0){
        return StatusType::INVALID_INPUT;
    }
    // Get Team
    std::shared_ptr<Team> team = teams_AVL.get_content(teamId);
    if (team && !players_UF.id_is_in_data(playerId))
    {
        try {
            // Create Player
            std::shared_ptr<UnionFind<Player>::Node> new_node = std::make_shared<UnionFind<Player>::Node>(
                Player(playerId, teamId, spirit, gamesPlayed, ability, cards, goalKeeper), spirit);
            // Add Player to players_UF
            players_UF.makeset(new_node, team->get_captain_node());
            // Update Team
            if (team->get_captain_node() == nullptr) {
                team->set_captain_node(&*new_node);
            }
            if (goalKeeper) {
                team->update_status_to_exist_goalKeeper();
            }
            team->increment_total_players();
            team->add_sum_player_abilities(ability);
            // Set Player Stats
            new_node->get_content().set_team_games_played_when_joined(team->get_team_games());
            new_node->get_content().set_team(&*team);
            // Completed Successfully
            return StatusType::SUCCESS;
        } catch (std::bad_alloc const&) {
            return StatusType::ALLOCATION_ERROR;
        }
    }
    else{
        return StatusType::FAILURE;
    }
}

output_t<int> world_cup_t::play_match(int teamId1, int teamId2)
{
    // Check Input O(1)
    if(teamId1 <= 0 || teamId2 <=0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }
    // Get Teams O(log(k))
    std::shared_ptr<Team> team1 = teams_AVL.get_content(teamId1);
    std::shared_ptr<Team> team2 = teams_AVL.get_content(teamId2);
    if (team1 == nullptr || team2 == nullptr) {
        return StatusType::FAILURE;
    }
    // Get Stats,Compare and Update O(1)
    int score1 = team1->get_sumPlayerAbilities() + team1->get_points();
    int score2 = team2->get_sumPlayerAbilities() + team2->get_points();
    if (score1 < 0 || score2 < 0) {
        throw std::logic_error("Team scores should not be negative");
    }
    if (score1 > score2) {
        team1->add_team_points(3);
    } else if (score1 < score2) {
        team2->add_team_points(3);
    } else if (team1->get_spirit_strength() > team2->get_spirit_strength()) {
        team1->add_team_points(3);
    } else if (team1->get_spirit_strength() < team2->get_spirit_strength()) {
        team2->add_team_points(3);
    } else {
        team1->add_team_points(1);
        team2->add_team_points(1);
    }
    // Update Games Played O(1)
    team1->increment_team_games();
    team2->increment_team_games();

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
    // Check Input
    if (teamId1 <= 0 || teamId2 <= 0 || teamId1 == teamId2){
        return StatusType::INVALID_INPUT;
    }
    // Find Teams
    std::shared_ptr<Team> team1 = teams_AVL.get_content(teamId1);
    std::shared_ptr<Team> team2 = teams_AVL.get_content(teamId2);
    if (team1 == nullptr || team2 == nullptr){
        return StatusType::FAILURE;
    }
    // Update Team Stats
    team1->set_points(team1->get_points() + team2->get_points());
    if (team2->get_has_goalKeeper()) {
        team1->update_status_to_exist_goalKeeper();
    }
    team1->add_total_players(team2->get_totalPlayers());
    team1->add_sum_player_abilities(team2->get_sumPlayerAbilities());
    // Merge Teams
    team1->set_captain_node(players_UF.unite(team1->get_captain_node(), team2->get_captain_node()));
    //now the captain node is the root of the UF. it may be team2's captain if team2 was the bigger team. or a nullptr if no players.
    if (team1->get_captain_node() != nullptr){
        team1->set_team_spirit(team1->get_captain_node()->get_team_product());
    }
    // Remove team2 from AVLs
    teams_AVL.remove(teamId2);
    teams_ability_AVL.remove(teamId2); // TODO: Right? I'm not too certain about this ability AVL
    //
    return StatusType::SUCCESS;
}

// DEBUGGING - TODO: DELETE in the end
// Obviously 'friend' is optimal, but it doesn't work for some reason :/
std::string world_cup_t::show_uf()
{
    return UnionFind_Tests<Player>::show_union_find(this->players_UF);
}
