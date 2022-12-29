#ifndef UNION_FIND_UNION_FIND_H
#define UNION_FIND_UNION_FIND_H

#include "Hash.h"
#include "wet2util.h"

template <class T>
class UnionFind{
public:
    class Node;
private:

    typename UnionFind<T>::Node *find_internal(int id);
    void set_root_parent(Node* child, Node* parent);
    Node* get_root(Node* node);
    void compare_set_sizes(Node* set1, Node* set2, Node** smaller_set, Node** larger_set);

    Hash<UnionFind<T>::Node> hash; //the hash contains UF nodes!
public:
    bool makeset(std::shared_ptr<UnionFind<T>::Node> new_node);
    bool unite(Node *node1, Node *node2);
    T* find(int id); //TODO: make sure pointer architecture works
    bool exists(int id);
};

template <class T>
class UnionFind<T>::Node{
private:
    Node* parent;
    T content;
    int size;
    permutation_t permutation; //TODO: permutation functions
public:
    explicit Node(T item);

    T* get_content();
    int get_id();

    int set_size(int new_size);
    int get_size();
    void set_permutation(const permutation_t& new_permutation);
    permutation_t* get_permutation();
};


template<class T>
typename UnionFind<T>::Node *UnionFind<T>::get_root(Node *node) {
    if (node == nullptr){
        throw;
    }
    if(node->parent){
        Node* root = get_root(node->parent); // after end of recursion, this returns the root.
        node->parent = root;
        return root;
    }
    else{
        return node;
    }
}

template<class T>
bool UnionFind<T>::makeset(std::shared_ptr<Node> new_node) {
    hash.add(new_node);
    return true;
}

template<class T>
bool UnionFind<T>::unite(Node *node1, Node *node2) {
    //connects smaller set to larger, updates larger set's size.
    if (node1 == nullptr || node2 == nullptr || node1 == node2){
        throw;
    }
    Node* set1 = node1->get_root();
    Node* set2 = node2->get_root();

    Node* smaller_set, larger_set;
    compare_set_sizes(set1, set2, smaller_set, larger_set);
    set_root_parent(smaller_set, larger_set);

    return true;
}


template<class T>
void UnionFind<T>::compare_set_sizes(Node *set1, Node *set2, Node **smaller_set, Node **larger_set) {
    if(get_size(set1) > get_size(set2)){
        *larger_set = set1;
        *smaller_set = set2;
    }
    else{
        *larger_set = set2;
        *smaller_set = set1;
    }
}

template<class T>
void UnionFind<T>::set_root_parent(Node *child, Node *parent) {
    child->parent = parent;
    parent->set_size(parent->get_size() + child->get_size())  ;
    child->set_size(0);
}

template<class T>
typename UnionFind<T>::Node * UnionFind<T>::find_internal(int id) {
    Node node = hash.find(id);
    return node->get_root();
}

template<class T>
T *UnionFind<T>::find(int id) {
    Node* container = find_internal(id);
    if(container){
        return container->get_content();
    }
    else{
        return nullptr;
    }
}

template<class T>
bool UnionFind<T>::exists(int id) {
    return hash.find(id) != nullptr;
}


//---------------------------------------NODE FUNCTIONS---------------------------------//
template<class T>
UnionFind<T>::Node::Node(T item) : content(item), parent(nullptr), size(1)
{}

template<class T>
int UnionFind<T>::Node::get_id() {
    return content.get_id();
}

template<class T>
T *UnionFind<T>::Node::get_content() {
    return content;
}

template<class T>
int UnionFind<T>::Node::set_size(int new_size) {
    size = new_size;
}

template<class T>
int UnionFind<T>::Node::get_size() {
    return size;
}

template<class T>
void UnionFind<T>::Node::set_permutation(const permutation_t& new_permutation) {
    permutation = new_permutation;
}

template<class T>
permutation_t *UnionFind<T>::Node::get_permutation() {
    return &permutation;
}


#endif //UNION_FIND_UNION_FIND_H
