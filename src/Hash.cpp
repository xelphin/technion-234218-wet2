#include "Hash.h"

Hash::Hash(int size) : arr(new NodeList_Players[size]), total_elem(0), size(size)
{
    if (size < 1)
        throw;
 }
// TODO: Find a way to have instead: Hash(int exp) and then arr(new NodeList_Players[2^exp -1]) without having bugs

Hash::~Hash()
{
    delete[] arr;
}

void Hash::add(std::shared_ptr<Player> player)
{
    int index = player->get_id()%size;
    if (index < 0 || index > size -1)
        return;
    arr[index].add(player);
    total_elem++;

    if (total_elem > size) {
        this->rehash();
    }
}

void Hash::rehash()
{
    NodeList_Players* newArr;
    int newSize = size*2 + 1; // TODO: correct?
    try {
        newArr = new NodeList_Players[newSize];
    } catch (const std::bad_alloc& e) {
        throw e;
    }
    for (int i=0; i< size; i++) {
        while (arr[i].getAmount() > 0) {
           std::shared_ptr<Player> player = arr[i].popStart();
           if (player == nullptr) {
                return;
           }
           int newIndex =  player->get_id()%newSize;
           if (newIndex < 0 || newIndex > newSize -1) {
                return;
           }
           newArr[newIndex].add(player);
        }
    }
    delete[] arr;
    arr = newArr;
    size = newSize;
}

std::shared_ptr<Player> Hash::find(int playerId) const
{
    if (playerId <= 0) {
        return nullptr;
    }
    int index = playerId%size;
    return arr[index].find(playerId);
}

std::string Hash::allLists() const
{
    std::string str = "Hash with size: " + std::to_string(size) + " contains: \n";

    for (int i=0; i < size; i++) {
        if(arr[i].getAmount() != 0) {
            str += "line " + std::to_string(i) + ": " + arr[i].strList() + "\n";
        }
    }
    return str;
}