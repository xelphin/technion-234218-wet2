#ifndef UNION_FIND_UNION_FIND_H
#define UNION_FIND_UNION_FIND_H

#include "Hash.h"
#include "Exception.h"
#include "wet2util.h"


template <class T>
class UnionFind{
public:
    class Node;
private:

    typename UnionFind<T>::Node *find_internal(int id);
    Node* get_root(Node* node);
    void compare_set_sizes(Node* buyer_set, Node* bought_set, Node** smaller_set, Node** larger_set);
    permutation_t path_compression_first_traversal_to_root(Node* node, Node** root);
    Node* path_compression_second_traversal_to_root(Node* node, const permutation_t& original_multiplier, Node* root);

    Hash<UnionFind<T>::Node> hash; //the hash contains UF nodes!
public:
    bool makeset(std::shared_ptr<UnionFind<T>::Node> new_node, Node *parent);
    bool unite(Node *buyer_node, Node *bought_node);
    T find(int id);
    bool exists(int id);
    permutation_t get_partial_spirit(int id);
};

template <class T>
class UnionFind<T>::Node{
private:
    T content;
    int size;
    permutation_t product;
    permutation_t parent_product;
    Node* parent;
public:
    explicit Node(T item, const permutation_t& permutation);

    T get_content();
    int get_id();

    Node* set_parent(Node* new_parent);
    Node* get_parent();
    int set_size(int new_size);
    int get_size();
    void set_product(const permutation_t& new_permutation);
    permutation_t get_product();
    void set_parent_product(const permutation_t& new_permutation);
    permutation_t get_parent_product();
};


template<class T>
typename UnionFind<T>::Node *UnionFind<T>::get_root(Node *node) {
    if (node == nullptr){
        throw;
    }
    Node* root;
    permutation_t multiplier = path_compression_first_traversal_to_root(node, &root);
    return path_compression_second_traversal_to_root(node, multiplier, root);
}

template<class T>
bool UnionFind<T>::makeset(std::shared_ptr<UnionFind<T>::Node> new_node, UnionFind::Node *parent) {
    hash.add(new_node);
    if (parent != nullptr)
    {
        unite(parent, new_node.get());
    }
//    root->set_product(root->get_product() * new_node->get_permutation()); // ABC -> ABC*D = ABCD
//    new_node->set_permutation(root->get_product()); // D -> ABCD
    return true;
}

template<class T>
bool UnionFind<T>::unite(Node* buyer_node, Node* bought_node) {
    //connects smaller set to larger, updates larger set's size.
    if (buyer_node == nullptr || bought_node == nullptr || buyer_node == bought_node){
        throw;
    }
    Node* buyer_set = get_root(buyer_node);
    Node* bought_set = get_root(bought_node);

    Node* larger_set; //A
    Node* smaller_set; //B
    compare_set_sizes(buyer_set, bought_set, &smaller_set, &larger_set);
    smaller_set->set_parent(larger_set);
    permutation_t root_final_product = buyer_node->get_product() * bought_node->get_product();
    bought_node->set_parent_product(buyer_node->get_product() * bought_node->get_parent_product()); // node 1 buys node2
    if(buyer_node == smaller_set){
        buyer_node->set_parent_product(bought_node->get_parent_product().inv() * buyer_node->get_parent_product());
        //this effectively makes the buyer node ignore the bought node when calculating partial_spirit.
        //in get_partial the returned value is parent*child. so having the child hold: child -> parent^-1 * child cancels perfectly.
    }
    larger_set->set_product(root_final_product);

    return true;
}


template<class T>
void UnionFind<T>::compare_set_sizes(Node *buyer_set, Node *bought_set, Node **smaller_set, Node **larger_set) {
    if(buyer_set->get_size() >= bought_set->get_size()){
        *larger_set = buyer_set;
        *smaller_set = bought_set;
    }
    else{
        *larger_set = bought_set;
        *smaller_set = buyer_set;
    }
}


template<class T>
typename UnionFind<T>::Node* UnionFind<T>::find_internal(int id) {
    Node* node = hash.find(id).get();
    return get_root(node);
}

template<class T>
T UnionFind<T>::find(int id) {
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

template<class T>
permutation_t UnionFind<T>::get_partial_spirit(int id) {
    Node* node = find_internal(id); // after this the path is compressed, and we are left only with the node and its parent.
    // they may both have parent products (e.g. if a small set buys a large set. one's parent_product is the inverse of the other's.)
    if (node == nullptr){
        throw ID_DOES_NOT_EXIST();
    }
    permutation_t return_value = node->get_parent_product(); // BC
    if (node->get_parent()){
        return_value = node->get_parent()->get_parent_product() * return_value; // A*BC
    }
    return return_value;
}

template<class T>
typename UnionFind<T>::Node *UnionFind<T>::path_compression_second_traversal_to_root(UnionFind::Node *node,
                                                                         const permutation_t& original_multiplier, Node* root) {
    permutation_t multiplier = original_multiplier;
    Node* current = node;
    while (current->get_parent() != nullptr){ //does not iterate on the root!
        permutation_t temp = current->get_parent_product();
        current->set_parent_product(multiplier);
        multiplier = multiplier * temp.inv(); // ABCDE * (DE)^-1 = ABCDE * E^-1 * E^-1 = ABC
        Node* current_parent = current->get_parent();
        current->set_parent(root);
        current = current_parent;
    }
    return current;
}

template<class T>
permutation_t UnionFind<T>::path_compression_first_traversal_to_root(Node* node, Node** root) {
    Node* current = node;
    permutation_t multiplier = permutation_t::neutral();
    while (current->get_parent() != nullptr){ //does not multiply by the root's parent_product!
        multiplier = current->get_parent_product() * multiplier;
        current = current->get_parent();
    }
    *root = current;
    return multiplier;
}


//---------------------------------------NODE FUNCTIONS---------------------------------//
template<class T>
UnionFind<T>::Node::Node(T item, const permutation_t& permutation) : content(item), parent(this), size(1),
product(permutation), parent_product(permutation)  //size immediately becomes 0 because we unite this with the parent.
{}
//---------------------------------------GETTERS AND SETTERS=---------------------------//
template<class T>
int UnionFind<T>::Node::get_id() {
    return content.get_id();
}

template<class T>
T UnionFind<T>::Node::get_content() {
    return content;
}

template<class T>
int UnionFind<T>::Node::set_size(int new_size) {
    size = new_size;
    return size;
}

template<class T>
int UnionFind<T>::Node::get_size() {
    return size;
}

template<class T>
permutation_t UnionFind<T>::Node::get_product() {
    return product;
}

template<class T>
void UnionFind<T>::Node::set_product(const permutation_t &new_permutation) {
    parent_product = new_permutation;
}

template<class T>
void UnionFind<T>::Node::set_parent_product(const permutation_t &new_permutation) {
    parent_product = new_permutation;
}

template<class T>
permutation_t UnionFind<T>::Node::get_parent_product() {
    return parent_product;
}

template<class T>
typename UnionFind<T>::Node *UnionFind<T>::Node::set_parent(Node* new_parent) {
    parent = new_parent;
    parent->set_size(parent->get_size() + get_size())  ;
    set_size(0);
    return parent;
}

template<class T>
typename UnionFind<T>::Node* UnionFind<T>::Node::get_parent() {
    return parent;
}


#endif //UNION_FIND_UNION_FIND_H
