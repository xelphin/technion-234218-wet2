#include "NodeList_Players.h"

NodeList_Players::NodeList_Players() : start(nullptr), end(nullptr), amount(0)
{}

NodeList_Players::~NodeList_Players() {
    NodeList_Players::Node* currentNode = this->start; // initialize current node to start
    while (currentNode)
    {
        NodeList_Players::Node* nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
}

void NodeList_Players::add(std::shared_ptr<Player> player)
{
    if (player == nullptr)
        return;
    // O(1)
    NodeList_Players::Node* newNode = new NodeList_Players::Node(player);
    // List is empty:
    if (start == nullptr) {
        start = newNode;
        end = newNode;
    } else {
    // List not empty:
        if (end == nullptr)
            throw;
        end->next = newNode;
        newNode->prev = end;
        end = newNode; // update end to point at most recent node addition
    }
    this->amount++;
}

std::shared_ptr<Player> NodeList_Players::find(int playerId) const // O(n[amount of nodes in this list])
{
    // Go one by one and check
    NodeList_Players::Node* currentNode = this->start; // initialize current node to start
    while (currentNode)
    {
        NodeList_Players::Node* nextNode = currentNode->next;
        if (currentNode->get_id() == playerId)
            return currentNode->player;
        currentNode = nextNode;
    }
    return nullptr;
}

std::shared_ptr<Player> NodeList_Players::popStart()
{
    if (start == nullptr){
        return nullptr;
    }
    NodeList_Players::Node* startNode = this->start;
    std::shared_ptr<Player> startPlayer = startNode->player;
    NodeList_Players::Node* secondNode = start->next;
    start = secondNode;
    if (secondNode != nullptr)
        secondNode->prev = nullptr;
    delete startNode;
    this->amount--;
    return startPlayer;
}

int NodeList_Players::getAmount() const
{
    return this->amount;
}

std::string NodeList_Players::strList() const
{
    std::string str = "";
    NodeList_Players::Node* currentNode = this->start; // initialize current node to start
    while (currentNode)
    {
        NodeList_Players::Node* nextNode = currentNode->next;
        str += std::to_string(currentNode->player->get_id()) + " ";
        currentNode = nextNode;
    }
    return str;
}

NodeList_Players::Node::Node(std::shared_ptr<Player> player)
        : prev(nullptr), next(nullptr), player(player)
        {}


int NodeList_Players::Node::get_id() const
{
    return this->player->get_id();
}