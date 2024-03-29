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
        std::shared_ptr<Team> team = teams_AVL.get_content(teamId); // O(log(k))
        if (team != nullptr) {
            team->remove_team_players();
            removed_avl_id = teams_AVL.remove_by_item(team);
            removed_avl_ability = teams_ability_AVL.remove_by_item(team);
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
    if(playerId <= 0 || teamId <=0 || gamesPlayed < 0 || cards < 0 || !spirit.isvalid()){
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
            teams_ability_AVL.remove_by_item(team); // Later add again
            if (team->get_captain_node() == nullptr) { // Team is empty
                team->set_captain_node(&*new_node);
                new_node->setIsCaptain();
            } else { // Team is not empty (already has a captain)
                int games_of_captain = team->get_captain_node()->get_captain_games();
                new_node->set_games_of_captain_when_joined(games_of_captain);
            }
            if (goalKeeper) {
                team->update_status_to_exist_goalKeeper();
            }
            team->increment_total_players();
            team->add_sum_player_abilities(ability);
            if (teams_ability_AVL.add(team) == nullptr){ // Added again
                throw std::logic_error("Team should have been re-added to teams_ability_AVL");
            }
            // Set Player Stats
            new_node->get_content()->set_team_games_played_when_joined(team->get_team_games());
            new_node->get_content()->set_team(&*team);
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
    if (team1->get_has_goalKeeper() != true || team2->get_has_goalKeeper() != true) {
        return StatusType::FAILURE;
    }
    // Get Stats,Compare and Update O(1)
    int score1 = team1->get_sumPlayerAbilities() + team1->get_points();
    int score2 = team2->get_sumPlayerAbilities() + team2->get_points();
    int strength1 = team1->get_spirit_strength();
    int strength2 = team2->get_spirit_strength();

    int winningValue = 0;
    if (score1 > score2) {
        team1->add_team_points(3);
        winningValue = 1;
    } else if (score1 < score2) {
        team2->add_team_points(3);
        winningValue = 3;
    } else if (strength1 > strength2) {
        team1->add_team_points(3);
        winningValue = 2;
    } else if (strength1 < strength2) {
        team2->add_team_points(3);
        winningValue = 4;
    } else {
        team1->add_team_points(1);
        team2->add_team_points(1);
        winningValue = 0;
    }
    // Update Games Played O(1)
    team1->get_captain_node()->increment_captain_games();
    team2->get_captain_node()->increment_captain_games();

    return winningValue;
}

output_t<int> world_cup_t::num_played_games_for_player(int playerId)
{
    if (playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (!players_UF.id_is_in_data(playerId)){
        return StatusType::FAILURE;
    }
    
    UnionFind<Player>::Node* player = players_UF.find_node(playerId);
    // if (playerId != player->get_id()) {
    //     throw std::logic_error("The id of the player given does not match our required playerId");
    // }
    // IF player is Captain
    int captain_games = player->get_captain_games();
    int ans_games_played = captain_games;
    // IF player is NOT Captain
    if (player->get_isCaptain() == false) {
        UnionFind<Player>::Node* captain = players_UF.find_set_of_id(playerId);
        if (captain->get_isCaptain() == false || captain->get_isRetired() == true) {
            throw std::logic_error("The captain node doesn't have Captain status");
        }
        int games_of_captain_when_joined = player->get_games_of_captain_when_joined();
        captain_games = captain->get_captain_games();
        ans_games_played = captain_games - games_of_captain_when_joined; 
    }
    // Return
	return players_UF.get_content(playerId)->get_gamesPlayed_when_initialized() + ans_games_played;
}

StatusType world_cup_t::add_player_cards(int playerId, int cards)
{
    if (playerId <= 0 || cards < 0){
        return StatusType::INVALID_INPUT;
    }
    if (!players_UF.id_is_in_data(playerId) || players_UF.find_set_of_id(playerId)->is_removed())
    {
        return StatusType::FAILURE;
    }
    players_UF.get_content(playerId)->add_cards(cards);
	return StatusType::SUCCESS;
}

output_t<int> world_cup_t::get_player_cards(int playerId)
{
    if (playerId <= 0){
        return StatusType::INVALID_INPUT;
    }
    if (!players_UF.id_is_in_data(playerId)){
        return StatusType::FAILURE;
    }
    return players_UF.get_content(playerId)->get_cards();
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
	if (i<0 || i >= this->teams_ability_AVL.get_amount()) {
        return StatusType::FAILURE;
    }
    return this->teams_ability_AVL.find_ith_rank_id(i);
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
    teams_ability_AVL.remove_by_item(team1); //should be done before doing other stuff so we can find it in the AVL.
    teams_ability_AVL.remove_by_item(team2);
    // Update Team Stats
    team1->set_points(team1->get_points() + team2->get_points());
    if (team2->get_has_goalKeeper()) {
        team1->update_status_to_exist_goalKeeper();
    }
    team1->add_total_players(team2->get_totalPlayers());
    team1->add_sum_player_abilities(team2->get_sumPlayerAbilities());
    // Merge Teams
    UnionFind<Player>::Node* team1_captain = team1->get_captain_node();
    UnionFind<Player>::Node* team2_captain = team2->get_captain_node();
    team1->set_captain_node(players_UF.unite(team1_captain, team2_captain));
    //now the captain node is the root of the UF. it may be team2's captain if team2 was the bigger team. or a nullptr if no players.

    // Update Status of Captains
    UnionFind<Player>::Node* new_captain = team1->get_captain_node();
    if (team1_captain != nullptr && team2_captain != nullptr && new_captain->get_id() == team1_captain->get_id()) {
        team2_captain->setIsRetired();
        team2_captain->set_games_of_captain_when_joined(new_captain->get_captain_games() - team2_captain->get_captain_games());
        team2_captain->reset_captain_games();
    } else if(team1_captain != nullptr && team2_captain != nullptr && new_captain->get_id() == team2_captain->get_id()) {
        team1_captain->setIsRetired();
        team1_captain->set_games_of_captain_when_joined(new_captain->get_captain_games() - team1_captain->get_captain_games());
        team1_captain->reset_captain_games();    
    } 

    // Remove team2 from AVLs
    teams_AVL.remove_by_item(team2);
    // Re add team2 to teams_ability
    if(teams_ability_AVL.add(team1) == nullptr) {
        throw std::logic_error("Should have added the buying team back to ability_AVL");
    }
    return StatusType::SUCCESS;
}
