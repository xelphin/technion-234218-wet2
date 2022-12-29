#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <memory>
#include "wet2util.h"
#include "Player.h"
#include "Team.h"
#include "NodeList.h"
#include "Exception.h"
#include <math.h>  

#include "developer_tests.h" // TODO: Delete this (when done)

template<class T>
class Hash_Tests;

template<class T>
class Hash {
public:
    static const int init_size = 1023;

    explicit Hash(int size = init_size); 
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
    int calcIndex(int id, int sizeArr) const; // note: important to keep 'size' argument (rehash)
};

template<class T>
Hash<T>::Hash(int size) : total_elem(0), size(size)
{
    try {
        arr = new NodeList<T>[size];
    } catch (const std::bad_alloc& e) {
        throw e;
    }
    if (size < 1)
        throw BAD_INPUT();
 }

template<class T>
Hash<T>::~Hash()
{
    delete[] arr;
}

template<class T>
void Hash<T>::add(std::shared_ptr<T> obj)
{
    int index = calcIndex(obj->get_id(), this->size);
    if (index < 0 || index > size -1)
        return;
    arr[index].add(obj);
    total_elem++;

    if (total_elem > size) {
        this->rehash();
    }

    Hash_Tests<T>::total_elem_correct(*this);
}

template<class T>
void Hash<T>::rehash()
{
    NodeList<T>* newArr;
    int newSize = size*2 + 1;
    try {
        newArr = new NodeList<T>[newSize];
    } catch (const std::bad_alloc& e) {
        throw e;
    }
    for (int i=0; i< size; i++) { // Iterate over each block in arr
        while (arr[i].getAmount() > 0) { // While the NodeList was not completley emptied
           std::shared_ptr<T> obj = arr[i].popStart(); // Remove from arr
           if (obj == nullptr) {
                throw std::logic_error("List amount > 0, yet when  popStart() it returns a nullptr");
           }
           int newIndex =  calcIndex(obj->get_id(), newSize);
           if (newIndex < 0 || newIndex > newSize -1) {
                throw std::logic_error("Index is out of range even though that can't logically happen");
           }
           newArr[newIndex].add(obj); // Add to newArr
        }
    }

    // Make newArr our new arr
    delete[] arr;
    arr = newArr;
    size = newSize;

    Hash_Tests<T>::total_elem_correct(*this);
}

template<class T>
std::shared_ptr<T> Hash<T>::find(int id) const
{
    if (id <= 0) {
        return nullptr;
    }
    int index = calcIndex(id, this->size);
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

template<class T>
int Hash<T>::calcIndex(int id, int sizeArr) const
{
    return id%sizeArr;
}

#endif // HASH_H
