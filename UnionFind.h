#ifndef UNION_FIND_UNION_FIND_H
#define UNION_FIND_UNION_FIND_H

#include "Hash.h"
#include "Exception.h"
#include "wet2util.h"


template <class T>
class UnionFind{
public:
    class Node;
    bool makeset(std::shared_ptr<UnionFind<T>::Node> new_node, Node *parent);
    Node * unite(Node *buyer_node, Node *bought_node);
    Node* find_set_of_id(int id);
    T get_content(int id);
    bool id_is_in_data(int id); //returns true if the item with the id i
    permutation_t get_partial_spirit(int id);
private:
    Hash<UnionFind<T>::Node> hash; //the hash contains UF nodes!

    typename UnionFind<T>::Node *find_node(int id);
    void compare_set_sizes(Node* buyer_set, Node* bought_set, Node** smaller_set, Node** larger_set);
    void update_permutations(Node* buyer_set, Node* bought_set, Node* smaller_set, Node* larger_set);
    Node* get_set_and_compress_path(Node* node);
    permutation_t path_compression_first_traversal_to_root(Node* node, Node** root);
    Node* path_compression_second_traversal_to_root(Node* node, const permutation_t& original_multiplier, Node* root);
};

template <class T>
class UnionFind<T>::Node{
private:
    friend UnionFind;
    Node* parent;
    T content;
    int size;
    permutation_t team_product;
    permutation_t seniors_product;
    bool removed;

    T get_content();
    
    //getters and setters
    Node* set_parent(Node* new_parent);
    Node* get_parent();
    int set_size(int new_size);
    int get_size();
    void set_team_product(const permutation_t& new_permutation);
    void set_seniors_product(const permutation_t& new_permutation);
    permutation_t get_seniors_product();

public:
    explicit Node(T item, const permutation_t& permutation);
    
    int get_id(); //to be used in nodelist
    permutation_t get_team_product();
    bool is_removed();
    void remove();
};



template<class T>
bool UnionFind<T>::makeset(std::shared_ptr<UnionFind<T>::Node> new_node, UnionFind::Node *parent) {
    hash.add(new_node);
    if (parent != nullptr)
    {
        unite(parent, new_node.get());
    }
    return true;
}

template<class T>
typename UnionFind<T>::Node* UnionFind<T>::unite(Node* buyer_node, Node* bought_node) {
    //connects smaller set to larger, updates larger set's size.
    if (buyer_node == nullptr) {
        return bought_node;}
    if (bought_node == nullptr){
        return buyer_node;
    }
    if(buyer_node == bought_node){
    throw BAD_INPUT();
    }
    //these 2 lines should theoretically not be relevant, but i think sometimes we may want to unite 2 nodes without knowing who their root is.
    Node* buyer_set = get_set_and_compress_path(buyer_node);
    Node* bought_set = get_set_and_compress_path(bought_node);

    Node* larger_set;
    Node* smaller_set;
    compare_set_sizes(buyer_set, bought_set, &smaller_set, &larger_set);
    smaller_set->set_parent(larger_set);
    update_permutations(buyer_set, bought_set, smaller_set, larger_set);

    larger_set;
}

template<class T>
typename UnionFind<T>::Node* UnionFind<T>::find_node(int id) {
    Node* node = hash.find(id).get();
    return node;
}

template<class T>
T UnionFind<T>::get_content(int id) {
    Node* container = find_node(id);
    if(container){
        return container->get_content();
    }
    throw std::logic_error("no item with that id");
}

template<class T>
typename UnionFind<T>::Node* UnionFind<T>::find_set_of_id(int id) {
    return get_set_and_compress_path(find_node(id));
}


template<class T>
typename UnionFind<T>::Node *UnionFind<T>::get_set_and_compress_path(Node *node) {
    if (node == nullptr){
        return nullptr;
    }
    Node* root;
    permutation_t multiplier = path_compression_first_traversal_to_root(node, &root);
    return path_compression_second_traversal_to_root(node, multiplier, root);
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
bool UnionFind<T>::id_is_in_data(int id) {
    return hash.find(id) != nullptr;
}

template<class T>
permutation_t UnionFind<T>::get_partial_spirit(int id) {
    Node* node = find_node(id);
    if (node == nullptr || get_set_and_compress_path(node)->is_removed()){
        return permutation_t::invalid();
    }
    // after this the path is compressed, and we are left only with the node and its parent.
    permutation_t return_value = node->get_seniors_product();
    if (node->get_parent()){
        return_value = node->get_parent()->get_seniors_product() * return_value;
    }
    return return_value;
}

template<class T>
void UnionFind<T>::update_permutations(Node* buyer_set, Node* bought_set, Node* smaller_set, Node* larger_set) {
    //this is called only in unite().
    permutation_t team_final_product = buyer_set->get_team_product() * bought_set->get_team_product();
    bought_set->set_seniors_product(buyer_set->get_team_product() * bought_set->get_seniors_product()); // node 1 buys node2
    if(buyer_set == smaller_set){
        buyer_set->set_seniors_product(bought_set->get_seniors_product().inv() * buyer_set->get_seniors_product());
        //this effectively makes the buyer node ignore the bought node when calculating partial_spirit.
        //in get_partial the returned value is parent*child. so having the child hold: child -> parent^-1 * child cancels perfectly.
    }
    else if (bought_set == smaller_set){
        bought_set->set_seniors_product(buyer_set->get_seniors_product().inv() * bought_set->get_team_product());
        //so as to not count the larger set's seniors_product twice, since it is already represented in its team_product.
    }
    larger_set->set_team_product(team_final_product);
}

template<class T>
permutation_t UnionFind<T>::path_compression_first_traversal_to_root(Node* node, Node** root) {
    Node* current = node;
    permutation_t multiplier = permutation_t::neutral();
    while (current->get_parent() != nullptr){ //does not multiply by the root's seniors_product!
        multiplier = current->get_seniors_product() * multiplier;
        current = current->get_parent();
    }
    *root = current;
    return multiplier;
}

template<class T>
typename UnionFind<T>::Node *UnionFind<T>::path_compression_second_traversal_to_root(UnionFind::Node *node,
                                                                         const permutation_t& original_multiplier, Node* root) {
    permutation_t multiplier = original_multiplier;
    Node* current = node;
    while (current->get_parent() != nullptr){ //does not iterate on the root!
        permutation_t temp = current->get_seniors_product();
        current->set_seniors_product(multiplier);
        multiplier = multiplier * temp.inv(); // ABCDE * (DE)^-1 = ABCDE * E^-1 * E^-1 = ABC
        Node* current_parent = current->get_parent();
        current->set_parent(root);
        current = current_parent;
    }
    return current;
}



//---------------------------------------NODE FUNCTIONS---------------------------------//
template<class T>
UnionFind<T>::Node::Node(T item, const permutation_t& permutation) : content(item), parent(nullptr), size(1),
team_product(permutation), seniors_product(permutation), removed(false)  //size immediately becomes 0 because we unite this with the parent.
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
permutation_t UnionFind<T>::Node::get_team_product() {
    return team_product;
}

template<class T>
void UnionFind<T>::Node::set_team_product(const permutation_t &new_permutation) {
    team_product = new_permutation;
}

template<class T>
void UnionFind<T>::Node::set_seniors_product(const permutation_t &new_permutation) {
    seniors_product = new_permutation;
}

template<class T>
permutation_t UnionFind<T>::Node::get_seniors_product() {
    return seniors_product;
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

template<class T>
bool UnionFind<T>::Node::is_removed() {
    return removed;
}

template<class T>
void UnionFind<T>::Node::remove() {
    removed = true;
}


#endif //UNION_FIND_UNION_FIND_H
