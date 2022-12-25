////
//// Created by Administrator on 04/12/2022.
////

#include "NodeList_Players.h"

NodeList_Players::NodeList_Players() : start(nullptr), end(nullptr)
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
}

std::shared_ptr<Player> NodeList_Players::find(int playerId) // O(n[amount of nodes in this list])
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

// TODO: Remove this function, most likely unnecessary
void NodeList_Players::remove(Node* node)
{
    if (node == nullptr)
        return;
    NodeList_Players::Node* prevNode = node->prev;
    NodeList_Players::Node* nextNode = node->next;
    // ONE NODE
    if (prevNode == nullptr && nextNode == nullptr) {
        if (start != end && start != nullptr) {
            std::cout << "ERROR!" << std::endl;
            return;
        }
        delete node;
        start = nullptr;
        end = nullptr;
        return;
    }
    // node == start
    if (prevNode == nullptr) {
        if (start != node) {
            std::cout << "ERROR!" << std::endl;
            return;
        }
        start = nextNode;
        if (start == nullptr)
            std::cout << "ERROR!" << std::endl;
        nextNode->prev = nullptr;
        delete node;
        return;
    }
    // node == end
    if (nextNode == nullptr) {
        if (end != node) {
            std::cout << "ERROR2!" << std::endl;
            return;
        }
        end = prevNode;
        prevNode->next = nullptr;
        delete node;
        return;
    }
    // node is in middle
    prevNode->next = nextNode;
    nextNode->prev = prevNode;
    delete node;
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