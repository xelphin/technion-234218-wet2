#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <memory>
#include "wet2util.h"
#include "Player.h"
#include "NodeList_Players.h"

// TODO: possibly make Hash (+NodeList) generic -> template
// TODO: maybe make it also generic with <..., int N> which is the size of array

class Hash {
public:
    static const int defaultM = 10;

    explicit Hash(int m = defaultM); 
    explicit Hash(int m, Hash& prevHash); 
    ~Hash();
    Hash(const Hash &) = delete;
    Hash &operator=(Hash &other) = delete;

    void add(std::shared_ptr<Player> player);
    std::shared_ptr<Player> find(int playerId) const;

    // DEBUGGING
    std::string allLists() const;

private:
    NodeList_Players* arr;
    int total_elem;
    int m;
};


#endif // HASH_H
