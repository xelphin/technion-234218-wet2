#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <memory>
#include "wet2util.h"
#include "Player.h"
#include "NodeList.h"
#include <math.h>  

// TODO: possibly make Hash (+NodeList) generic -> template
// TODO: maybe make it also generic with <..., int N> which is the size of array

class Hash {
public:

    explicit Hash(int size = 1023); 
    explicit Hash(Hash& prevHash); 
    ~Hash();
    Hash(const Hash &) = delete;
    Hash &operator=(Hash &other) = delete;

    void add(std::shared_ptr<Player> player);
    std::shared_ptr<Player> find(int playerId) const;

    

    // DEBUGGING
    std::string allLists() const;

private:
    NodeList<Player>* arr;
    int total_elem;
    int size;

    void rehash();
};


#endif // HASH_H
