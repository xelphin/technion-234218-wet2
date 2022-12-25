#ifndef NODELIST_PLAYERS_H
#define NODELIST_PLAYERS_H

#include <iostream>
#include <memory>
#include "wet2util.h"
#include "Player.h"

class NodeList_Players {
public:
    class Node;

    explicit NodeList_Players(); 
    ~NodeList_Players();
    NodeList_Players(const NodeList_Players &) = delete; // When re-hashing, the mod changes so current NodeList is not useful
    NodeList_Players &operator=(NodeList_Players &other) = delete;

    void add(std::shared_ptr<Player> player);
    std::shared_ptr<Player> find(int playerId) const;
    std::shared_ptr<Player> popStart();

    int getAmount() const;

    // DEBUGGING
    std::string strList() const;

private:
    NodeList_Players::Node *start;
    NodeList_Players::Node *end;
    int amount;
};
//
class NodeList_Players::Node{
public:
    NodeList_Players::Node *prev;
    NodeList_Players::Node *next;
    std::shared_ptr<Player> player;

    explicit Node(std::shared_ptr<Player> player);

    int get_match_points() const;
    int get_id() const;

    Node(const Node &) = delete; //cant copy nodes. make new ones.
    Node &operator=(Node &other) = delete;
    ~Node() = default;
};

#endif // NODELIST_PLAYERS_H
