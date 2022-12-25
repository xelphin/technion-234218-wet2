#include "Hash.h"

Hash::Hash(int m) : arr(new NodeList_Players[(2^m)-1]), total_elem(0), m(m)
{}

Hash::~Hash()
{
    delete[] arr;
}