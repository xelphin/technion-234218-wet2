#ifndef NodeList_H
#define NodeList_H

#include <iostream>
#include <memory>
#include "wet2util.h"
#include "Player.h"
#include "Team.h"

template <class T>
class NodeList {
public:
    class Node;

    explicit NodeList(); 
    ~NodeList();
    NodeList(const NodeList &) = delete; // When re-hashing, the mod changes so current NodeList is not useful
    NodeList &operator=(NodeList &other) = delete;

    // Add to end of list
    void add(std::shared_ptr<T> obj);

    // Find using ID
    std::shared_ptr<T> find(int id) const;

    // Remove and return the first node in list
    std::shared_ptr<T> popStart();

    // Get amount of nodes in list (length)
    int getAmount() const;

    // DEBUGGING
    std::string strList() const;

private:
    NodeList::Node *start;
    NodeList::Node *end;
    int amount;
};
//

template <class T>
class NodeList<T>::Node{
public:
    NodeList::Node *prev;
    NodeList::Node *next;
    std::shared_ptr<T> obj;

    explicit Node(std::shared_ptr<T> obj);

    int get_match_points() const;
    int get_id() const;

    Node(const Node &) = delete; //cant copy nodes. make new ones.
    Node &operator=(Node &other) = delete;
    ~Node() = default;
};



template <class T>
NodeList<T>::NodeList() : start(nullptr), end(nullptr), amount(0)
{}

template <class T>
NodeList<T>::~NodeList() {
    NodeList<T>::Node* currentNode = this->start; // initialize current node to start
    while (currentNode)
    {
        NodeList::Node* nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
}

template <class T>
void NodeList<T>::add(std::shared_ptr<T> obj)
{
    if (obj == nullptr)
        return;
    // O(1)
    NodeList::Node* newNode = new NodeList::Node(obj);
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

template <class T>
std::shared_ptr<T> NodeList<T>::find(int id) const // O(n[amount of nodes in this list])
{
    // Go one by one and check
    NodeList::Node* currentNode = this->start; // initialize current node to start
    while (currentNode)
    {
        NodeList::Node* nextNode = currentNode->next;
        if (currentNode->get_id() == id)
            return currentNode->obj;
        currentNode = nextNode;
    }
    return nullptr;
}

template <class T>
std::shared_ptr<T> NodeList<T>::popStart()
{
    if (start == nullptr){
        return nullptr;
    }
    NodeList::Node* startNode = this->start;
    std::shared_ptr<T> startObj = startNode->obj;
    NodeList::Node* secondNode = start->next;
    start = secondNode;
    if (secondNode != nullptr)
        secondNode->prev = nullptr;
    delete startNode;
    this->amount--;
    return startObj;
}

template <class T>
int NodeList<T>::getAmount() const
{
    return this->amount;
}

template <class T>
std::string NodeList<T>::strList() const
{
    std::string str = "";
    NodeList::Node* currentNode = this->start; // initialize current node to start
    while (currentNode)
    {
        NodeList::Node* nextNode = currentNode->next;
        str += std::to_string(currentNode->obj->get_id()) + " ";
        currentNode = nextNode;
    }
    return str;
}

template <class T>
NodeList<T>::Node::Node(std::shared_ptr<T> obj)
        : prev(nullptr), next(nullptr), obj(obj)
        {}

template <class T>
int NodeList<T>::Node::get_id() const
{
    return this->obj->get_id();
}

#endif // NodeList_H
