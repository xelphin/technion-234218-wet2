#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <memory>
#include "wet2util.h"
#include "Player.h"
#include "Team.h"
#include "NodeList.h"
#include <math.h>  

#include "developer_tests.h" // TODO: Delete this (when done)

template<class T>
class Hash_Tests;

template<class T>
class Hash {
public:

    explicit Hash(int size = 1023);
    ~Hash();
    Hash(const Hash &) = delete;
    Hash &operator=(Hash &other) = delete;

    void add(std::shared_ptr<T> obj);
    std::shared_ptr<T> find(int id) const;

    

    // DEBUGGING // TODO: Delete when done
    std::string allLists() const;
    friend Hash_Tests<T>;


private:
    NodeList<T>* arr;
    int total_elem;
    int size;

    void rehash();
};

template<class T>
Hash<T>::Hash(int size) : arr(new NodeList<T>[size]), total_elem(0), size(size)
{
    if (size < 1)
        throw;
 }

template<class T>
Hash<T>::~Hash()
{
    delete[] arr;
}

template<class T>
void Hash<T>::add(std::shared_ptr<T> obj)
{
    int index = obj->get_id()%size;
    if (index < 0 || index > size -1)
        return;
    arr[index].add(obj);
    total_elem++;

    if (total_elem > size) {
        this->rehash();
    }

    //Hash_Tests<T>::total_elem_correct(*this);
}

template<class T>
void Hash<T>::rehash()
{
    NodeList<T>* newArr;
    int newSize = size*2 + 1; // TODO: correct?
    try {
        newArr = new NodeList<T>[newSize];
    } catch (const std::bad_alloc& e) {
        throw e;
    }
    for (int i=0; i< size; i++) { // Iterate over each block in arr
        while (arr[i].getAmount() > 0) { // While the NodeList was not completley emptied
           std::shared_ptr<T> obj = arr[i].popStart(); // Remove from arr
           if (obj == nullptr) {
                return;
           }
           int newIndex =  obj->get_id()%newSize;
           if (newIndex < 0 || newIndex > newSize -1) {
                return;
           }
           newArr[newIndex].add(obj); // Add to newArr
        }
    }

    // Make newArr our new arr
    delete[] arr;
    arr = newArr;
    size = newSize;

    //Hash_Tests<T>::total_elem_correct(*this);
}

template<class T>
std::shared_ptr<T> Hash<T>::find(int id) const
{
    if (id <= 0) {
        return nullptr;
    }
    int index = id%size;
    return arr[index].find(id);
}

template<class T>
std::string Hash<T>::allLists() const
{
    std::string str = "Hash with size: " + std::to_string(size) + " contains: \n";

    for (int i=0; i < size; i++) {
        if(arr[i].getAmount() != 0) {
            str += "line " + std::to_string(i) + ": " + arr[i].strList() + "\n";
        }
    }
    return str;
}

#endif // HASH_H
