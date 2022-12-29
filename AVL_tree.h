#ifndef AVL_TREE_H
#define AVL_TREE_H

#include "stdexcept"
#include "iostream"
#include "Exception.h"

#define SORT_BY_SCORE true
#define SORT_BY_ID false
#define UNBALANCED 2
#define SCORE >>=
#define ID ~
#define I_OUT_OF_RANGE -1

template<class T>
class AVL_testing;

//-------------------------------AVL TREE CLASS---------------------------------------//

template <class T>
class AVL_tree {
public:
    class Node;


    explicit AVL_tree(bool sort_by_score); // O(1)
    ~AVL_tree(); // O(n[amount nodes])
    AVL_tree(const AVL_tree &) = delete; //cant copy trees
    AVL_tree &operator=(AVL_tree &other) = delete;

    AVL_tree<T>::Node* add(T item);
    bool remove(int id);
    bool remove_by_item(const T& item);
    bool remove_internal(AVL_tree<T>::Node* node);

    int get_amount();
    AVL_tree<T>::Node* find(const T& item);
    AVL_tree<T>::Node* find_id(int id);
    AVL_tree<T>::Node* find_rightmost(AVL_tree<T>::Node* node);
    int find_ith_rank_id(int i);

    T get_content(int id);
    T get_biggest_in_tree();

    template<class F>
    void in_order_traversal_wrapper(F functor); // used to iterate on all the nodes.


    // TESTS AND DEBUGGING FUNCTIONS
    //TODO: comment out
    std::string debugging_printTree();
    std::string debugging_printTree_new();
    static void print_node(AVL_tree<T>::Node* node);
    void find_test_wrapper(int id);
private:
    const bool sort_by_score;
    AVL_tree<T>::Node *root;
    int amount;

    AVL_tree<T>::Node* find_designated_parent(AVL_tree<T>::Node* new_leaf);
    void climb_up_and_rebalance_tree(AVL_tree<T>::Node* leaf);
    void post_order_delete();
    AVL_tree<T>::Node* find_next_in_order(AVL_tree<T>::Node* node);
    void replace_nodes(AVL_tree<T>::Node* node, AVL_tree<T>::Node* replacement);
    static int get_weight(AVL_tree<T>::Node* node);
    int select(Node *sub_tree_root, int i);

    template<class F>
    void in_order_traversal(AVL_tree<T>::Node* node, F* functor);


    // TESTS AND DEBUGGING FUNCTIONS
    //TODO: comment out
    void debugging_printTree(const std::string& prefix, const AVL_tree::Node* node, bool isLeft, std::string& str);
    void debugging_printTree(const AVL_tree::Node* node, std::string& str);
    void debugging_printTree_new(const std::string& prefix, const AVL_tree::Node* node, bool isLeft, std::string& str);
    void debugging_printTree_new(const AVL_tree::Node* node, std::string& str);
};


//--------------------------------NODE CLASS------------------------------------------//

//Nodes will be used in the AVL tree, and will allocate memory for an actual item.
template <class T>
class AVL_tree<T>::Node{
public:
    AVL_tree<T> *tree;
    AVL_tree<T>::Node *parent;
    AVL_tree<T>::Node *left;
    AVL_tree<T>::Node *right;
    T content; //T is always a type of pointer.
    int balance_factor; //to manage the sorting of the AVL tree.
    int height;
    int weight;

    explicit Node(T);
    Node(const AVL_tree &) = delete; //cant copy nodes. make new ones.
    Node &operator=(AVL_tree &other) = delete;
    ~Node() = default;

    int get_comparison(const AVL_tree<T>::Node &other);

    //tree sorting functions:
    int set_balance_factor();
    int set_height();
    int get_height(AVL_tree<T>::Node* node);
    void choose_roll();

    void update_parent(AVL_tree<T>::Node* replacement);

private:
    void roll_right();
    void roll_left();
    void LL_roll();
    void LR_roll();
    void RR_roll();
    void RL_roll();
};



//---------------------------PUBLIC FUNCTION DEFINITIONS------------------------------//

template<class T>
AVL_tree<T>::AVL_tree(bool sort_by_score) :
sort_by_score(sort_by_score),
root(nullptr),
amount(0)
{

}

template<class T>
AVL_tree<T>::~AVL_tree() {
    post_order_delete();
}


template<class T>
AVL_tree<T>::Node::Node(T new_item) 
: tree(nullptr),
  parent(nullptr),
  left(nullptr),
  right(nullptr),
  content(nullptr),
  balance_factor(0),
  height(0),
  weight(1)
{
    content = new_item;
}


template<class T>
typename AVL_tree<T>::Node* AVL_tree<T>::add(T item) {
    // returns a pointer to the node holding the pointer to the item. we need that
    // in order to store the list of nodes in the object, so we can delete all the nodes when
    // the object is deleted.
    //

    AVL_tree<T>::Node* leaf(new Node(item));
    try {
        leaf->tree = this;
        AVL_tree<T>::Node *parent = find_designated_parent(leaf);
        if (parent == nullptr) {
            root = leaf;
            leaf->tree = this;
            this->amount++;
            return leaf;
        }
        if ((*leaf).get_comparison(*parent) > 0) {
            parent->right = leaf;
        } else if ((*leaf).get_comparison(*parent) < 0) {
            parent->left = leaf;
        } else {
            delete leaf;
            throw ID_ALREADY_EXISTS();
        }
        leaf->parent = parent;
        leaf->tree = this;
        climb_up_and_rebalance_tree(leaf);
        this->amount++;
    }
    catch (std::bad_alloc const&){
        delete leaf;
        throw std::bad_alloc();
    }
    return leaf;
}


template<class T>
bool AVL_tree<T>::remove_by_item(const T& item) {
    // true if the node was removed. false otherwise.
    // time complexity: O(log(nodes))
    AVL_tree<T>::Node* node = find(item);
    if (node == nullptr){
        return false;
    }
    else{
        return remove_internal(node);
    }
}

template<class T>
typename AVL_tree<T>::Node *AVL_tree<T>::find(const T& item) {
    //item acts like "this->content"
    AVL_tree<T>::Node* current = root;
    if (!current){
        return nullptr;
    }

    while(true){ //while true loop ok because in every case we either return or go down tree.
        int difference = ((*current->content).get_id()) - item->get_id();
        if (difference == 0){
            return current;
        }

        if (sort_by_score == SORT_BY_SCORE){
            difference = *(current->content) SCORE (*(item));

        }
        else
        {
            difference = ID(*(current->content)) - ID(*(item));
        }
        if ( difference < 0)  { //proceed to right branch. current id smaller than wanted id.
            if (current->right != nullptr){
                //std::cout << "check right" << std::endl;
                current = current->right;
            }
            else{ //no right child
                return nullptr; //search failed
            }
        }
        else{ //proceed to left branch
            if (current->left != nullptr){
                current = current->left;
            }
            else{
                return nullptr;
            }
        }
    }
}

template<class T>
typename AVL_tree<T>::Node *AVL_tree<T>::find_rightmost(AVL_tree<T>::Node* node) {
    if (node == nullptr){
        return nullptr;
    }
    Node* current = node->right;
    if (current == nullptr){ //no nodes to the right of this node
        return nullptr;
    }

    while(true){ //while true loop ok because in every case we either return or go down tree.
        if (current->right != nullptr){
            current = current->right;
        }
        else{
            return current; //returns when there is no right child
        }
    }
}

template<class T>
bool AVL_tree<T>::remove(int id) {
    // true if the node was removed. false otherwise.
    // time complexity: O(log(nodes))
    AVL_tree<T>::Node* node = find_id(id);
    if (node == nullptr){
        return false;
    }
    else{
        return remove_internal(node);
    }

}

template<class T>
bool AVL_tree<T>::remove_internal(AVL_tree<T>::Node* node) {
    //needs to be O(log(n)), where n is either players or teams in system, depending on calling function.
    AVL_tree<T>::Node* next_unbalanced_node = nullptr;
    AVL_tree<T>::Node* replacement = nullptr;
    // updates parent and children before deletion
    if (node->left == nullptr && node->right == nullptr) //if leaf
    {
        next_unbalanced_node = node->parent;
        node->update_parent(nullptr);
    }
    else if (node->left != nullptr && node->right == nullptr){ // only left child
        next_unbalanced_node = node->left;
        node->update_parent(node->left);
    }
    else if (node->left == nullptr && node->right != nullptr){ // only right child
        next_unbalanced_node = node->right;
        node->update_parent(node->right);
    }
    else { // 2 children
        replacement = find_next_in_order(node->right); // replacement does not have a left child this way.

        if (replacement == nullptr){
            throw std::invalid_argument("next in order activated on nullptr");
        }

        if (replacement->left != nullptr){
            throw std::logic_error("not supposed to have left son");
        }
        else if (replacement->right != nullptr){ // if it has a right child
            next_unbalanced_node = replacement->right;
            // his right cant have a child node because that makes replacement have a BF of -2.
        }
        else if (replacement != node->right) //replacement has no children, and is not the right child of the removed node.
        {
            next_unbalanced_node = replacement->parent;
        }
        else
        { // replacement is the right child of the removed node.
            next_unbalanced_node = replacement;
        }


        if (replacement != node->right){
            replacement->update_parent(replacement->right); // update parent should work even on nullptr
        }
        replace_nodes(node, replacement);
    }

    // found next unbalanced, replaced if necessary.
    climb_up_and_rebalance_tree(next_unbalanced_node);

    delete node;
    this->amount--;
    return true;
}

template<class T>
typename AVL_tree<T>::Node *AVL_tree<T>::find_id(int id) {
    AVL_tree<T>::Node* current = root;
    if (current == nullptr){
        return nullptr;
    }

    while(true){ //while true loop ok because in every case we either return or go down tree.
        int difference = ((*current->content).get_id()) - id;
        if (difference == 0){
            return current;
        }
        else if ( difference < 0)  { //proceed to right branch. current id smaller than wanted id.
            if (current->right != nullptr){
                //std::cout << "check right" << std::endl;
                current = current->right;
            }
            else{ //no right child
                return nullptr; //search failed
            }
        }
        else{ //proceed to left branch
            if (current->left != nullptr){
                current = current->left;
            }
            else{
                return nullptr;
            }
        }
    }
}

template<class T>
T AVL_tree<T>::get_content(int id) {
    AVL_tree<T>::Node* node = find_id(id);
    if (node){
        return node->content;
    }
    else
    {
        return nullptr;
    }
}

template<class T>
T AVL_tree<T>::get_biggest_in_tree() {
    AVL_tree<T>::Node* node = find_rightmost(root);
    if (node != nullptr){
        T value = node->content;
        return value;
    }
    else if (root){
        return root->content;
    }
    else{
        return nullptr;
    }
}

template<class T>
template<class F>
void AVL_tree<T>::in_order_traversal_wrapper(F functor) {
    in_order_traversal(root, &functor);
}

//-----------------------------PRIVATE TREE FUNCTIONS-----------------------------//

template<class T>
void AVL_tree<T>::post_order_delete() {
    // called in tree destructor so may be called during an exception.
    if (root == nullptr){
        return;
    }
    AVL_tree<T>::Node* current = root;
    AVL_tree<T>::Node* temp = root;
    // while not in root or root has children:
    while (current->parent || (current == root && (root->left || root->right))){
        if (current->left != nullptr)
            current = current->left;
        else if (current->right){
            current = current->right;
        }
        else{ //its a leaf
            if (current->parent->left == current){ //if leaf is a left child
                current->parent->left = nullptr;
            } else{
                current->parent->right = nullptr;
            }
            temp = current->parent;
            delete current;
            current = temp;
        }
    }

    //finished deleting the tree. the root has no children.
    delete root;
    root = nullptr;
}


template<class T>
template<class F>
void AVL_tree<T>::in_order_traversal(AVL_tree::Node *node, F *functor) {
    //receives a function, and activates it on every node in the tree in order.
    //takes O(nodes_in_tree) time, O(log(nodes)) memory.
    if (node == nullptr){
        return;
    }

    in_order_traversal(node->left, functor);
    (*functor)(node->content);
    in_order_traversal(node->right, functor);
}

//template<typename T, typename P>
//void transform(Queue<T> &queue, P function) {
//    //can't use range based for loop because it needs *it and not it.
//    for (typename Queue<T>::Iterator it = queue.begin(); it != queue.end(); ++it)
//    {
//        function(*it);
//    }
//}


template<class T>
typename AVL_tree<T>::Node *AVL_tree<T>::find_next_in_order(AVL_tree::Node *node) {
    // used only in remove. this is called on the right child, and then we go as left as possible.
    if (node == nullptr){
        throw std::invalid_argument("next in order activated on nullptr");
    }
    AVL_tree<T>::Node* current = node;
    while(current->left != nullptr) // while left child
    {
        current = current->left;
    }
    return current;
}


template<class T>
void AVL_tree<T>::replace_nodes(AVL_tree::Node *node, AVL_tree::Node *replacement) {
    // to be used ONLY in remove().
    // this function is called only when node has 2 children.
    // after this function, no pointers should point at node.
    replacement->left = node->left;
    node->left->parent = replacement;
    if (node->right != replacement){ // sometimes the replacement is the right child. delicate edge case.
        replacement->right = node->right;
        node->right->parent = replacement;
    }
    node->update_parent(replacement);
}


template<class T>
typename AVL_tree<T>::Node* AVL_tree<T>::find_designated_parent(AVL_tree::Node* new_leaf) {
    //I THINK DOCUMENTATION IN THIS FUNCTION IS WRONG.
    AVL_tree<T>::Node* current = root;
    if (!current){
        return nullptr;
    }
    
    while(true){ //while true loop ok because in every case we either return or go down tree.

        if (new_leaf->content->get_id() == current->content->get_id()){
            return current;}

        if (new_leaf->get_comparison(*current)>0)  { //proceed to right branch.
            if (current->right != nullptr){
                current = current->right;
            }
            else{ //no right child
                return current;
            }
        }
        else{ //proceed to left branch
            if (current->left != nullptr){
                current = current->left;
            }
            else{
                return current;
            }
        }
    }
}


template <class T>
int AVL_tree<T>::Node::get_comparison(const AVL_tree<T>::Node &other) {
    // since its unknown if the tree is sorted by id or by score, we need this function to work on both.
    // '!' operator is for score. '~' operator is for id.
    // the comparison is done between the dereferences of the pointers the nodes holds.
    
    if (tree == nullptr ) {
        //std::cout << "tree is a nullptr!" << std::endl;
        return 0;
    }
    if (tree->sort_by_score == SORT_BY_SCORE){
        return *(this->content) SCORE *(other.content);

    }
    else
    {
        return ID(*(this->content)) - ID(*other.content);
    }
    
   return 0;
}

template <class T>
int AVL_tree<T>::get_amount() {
    return amount;
}


//----------------------------TREE SORTING FUNCTIONS------------------------------//


template<class T>
int AVL_tree<T>::get_weight(AVL_tree<T>::Node *node) {
    if (node == nullptr){
        return 0;
    }
    else{
        return node->weight;
    }
}


template<class T>
int AVL_tree<T>::Node::set_height() {

    int left_height = get_height(left);
    int right_height = get_height(right);
    height = left_height > right_height ? left_height + 1 : right_height + 1; //max

    weight = get_weight(left) + get_weight(right) + 1;

    return height;
}

template<class T>
int AVL_tree<T>::Node::get_height(AVL_tree<T>::Node *node) {
    if (node == nullptr){
        return -1; //leaf child is 0, non-existent child is -1
    }
    else{
        return node->height;
    }
}

template<class T>
int AVL_tree<T>::Node::set_balance_factor() {
    if(left != nullptr){
        left->set_height();
    }
    if(right != nullptr){
        right->set_height();
    }
    set_height();
    int height_difference = get_height(left) - get_height(right);
    balance_factor = height_difference;
    return height_difference;
}

template<class T>
void AVL_tree<T>::climb_up_and_rebalance_tree(AVL_tree<T>::Node *leaf) {
    AVL_tree<T>::Node* current = leaf; //not node.parent, so it also updates the height of the node to 0 if it's a leaf.

    while (current != nullptr){ //climbs up tree. stops after iterating on root.
        current->set_balance_factor();
        if (abs(current->balance_factor) == UNBALANCED){
            current->choose_roll(); //because roll switches parent and child, we will still get to the new parent.
        }
        current->set_height();
        current = current->parent;
    }
}

template<class T>
void AVL_tree<T>::Node::update_parent(AVL_tree<T>::Node* replacement) {
    //updates the parent after a roll to point to the replacement of the old child.
    if (parent) {
        if (parent->left == this) {
            parent->left = replacement;
        }
        else if (parent->right == this){
            parent->right = replacement;
        }
    } else { // no parent implies this is the root
        tree->root = replacement;
    }
    if (replacement){
        replacement->parent = parent;
    }
    parent = replacement;
}

template<class T>
void AVL_tree<T>::Node::choose_roll() {
    //if this function is called, it means the BF of this node is ±2, and it should roll.
    //the numbers are according to the chart in the slides.
    // std::cout << "the tree is unbalanced -> do roll" << std::endl;
    set_balance_factor();
    if (balance_factor == 2){
        if (left->set_balance_factor() >= 0){
            //std::cout << "roll: LL" << std::endl;
            this->LL_roll();
        }
        else if (left->set_balance_factor() == -1){
            //std::cout << "roll: LR" << std::endl;
            this->LR_roll();
        }
        else throw std::invalid_argument("bad balance factor");
    }
    else if (balance_factor == -2){
        if (right->set_balance_factor() <= 0){
            //std::cout << "roll: RR" << std::endl;
            this->RR_roll();
        }
        else if (right->set_balance_factor() == 1){
            //std::cout << "roll: RL" << std::endl;
            this->RL_roll();
        }
        else throw std::invalid_argument("bad balance factor");
    }
    else throw std::invalid_argument("bad balance factor");
}

template<class T>
void AVL_tree<T>::Node::roll_left() {
    AVL_tree<T>::Node* original_right = right;
    if (right->left){
    right->left->parent = this;
    }
    right = right->left;
    original_right->left = this;
    update_parent(original_right);
    set_balance_factor();
}

template<class T>
void AVL_tree<T>::Node::roll_right() {
    AVL_tree<T>::Node* original_left = left;
    if(left->right){
        left->right->parent = this;
    }
    left = left->right;
    original_left->right = this;
    update_parent(original_left);
    set_balance_factor();
}

template<class T>
void AVL_tree<T>::Node::LL_roll() {
    this->roll_right();
}

template<class T>
void AVL_tree<T>::Node::LR_roll() {
    left->roll_left();
    roll_right();
}

template<class T>
void AVL_tree<T>::Node::RR_roll() {
    this->roll_left();
}

template<class T>
void AVL_tree<T>::Node::RL_roll() {
    right->roll_right();
    roll_left();
}

//------------------------------------------OLD DEBUG FUNCTIONS FOR TESTS TO WORK-----------------//
//-------------------------------------------DEBUGGING-------------------------------------------//
// ONLY FOR DEBUGGING - ERASE LATER
template<class T>
void AVL_tree<T>::debugging_printTree_new(const std::string& prefix, const AVL_tree::Node* node, bool isLeft, std::string& str)
{
   if( node != nullptr )
   {
       str += prefix;

       str += (isLeft ? "└──" : "├──" );

       // print the value of the node
       str += std::to_string((*(node->content)).get_id());
       str += "\n";

       // enter the next tree level - left and right branch
       AVL_tree<T>::debugging_printTree_new( prefix + (isLeft ? "    " : "│   "), node->right, false, str);
       AVL_tree<T>::debugging_printTree_new( prefix + (isLeft ? "    " : "│   "), node->left, true, str);
   }
}

template<class T>
void AVL_tree<T>::debugging_printTree_new(const AVL_tree::Node* node, std::string& str)
{
   debugging_printTree_new("", node, true, str);
}

template<class T>
std::string AVL_tree<T>::debugging_printTree_new()
{
   std::string tree = "";
   debugging_printTree_new(root, tree);
   return tree;
}
template<class T>
void AVL_tree<T>::debugging_printTree(const std::string& prefix, const AVL_tree::Node* node, bool isLeft, std::string& str)
{
   if( node != nullptr )
   {
       str += prefix;

       str += (isLeft ? "├──" : "└──" );

       // print the value of the node
       str += std::to_string((*(node->content)).get_id());
       str += "\n";

       // enter the next tree level - left and right branch
       AVL_tree<T>::debugging_printTree( prefix + (isLeft ? "│   " : "    "), node->left, true, str);
       AVL_tree<T>::debugging_printTree( prefix + (isLeft ? "│   " : "    "), node->right, false, str);
   }
}

template<class T>
void AVL_tree<T>::debugging_printTree(const AVL_tree::Node* node, std::string& str)
{
   debugging_printTree("", node, false, str);
}

template<class T>
std::string AVL_tree<T>::debugging_printTree()
{
   std::string tree = "";
   debugging_printTree(root, tree);
   return tree;
}



template<class T>
void AVL_tree<T>::find_test_wrapper(int id) {
   print_node(find_id(id));
}

template<class T>
void AVL_tree<T>::print_node(AVL_tree<T>::Node* node){
   //the format is: self, parent, left, right
   if (node == nullptr){
//        std::cout << "NULL\n";
       return;
   }
   //std::cout << (*(node->content)).get_id() << " " <<
   //        ((node->parent) ? (*(node->parent->content)).get_id() : 0 ) << " " <<
   //        ((node->left) ? (*(node->left->content)).get_id() : 0 ) << " " <<
   //        ((node->right) ? (*(node->right->content)).get_id() : 0 ) <<std::endl;
   if (node->left){
       if ((node->left && node->left->parent != node) || (node->right && node->right->parent != node)){
           throw std::invalid_argument("parent and child dont point at each other");
       }
   }
}

template<class T>
int AVL_tree<T>::find_ith_rank_id(int i) {
    if (i < 1 || i > get_amount()){ //e.g. tree has 1 node ⇒ amount = 1, node's rank is 1. so i=1 is the only valid number.
        return I_OUT_OF_RANGE;
    }
    return select(root, i) - 1; //segel asked for index, starting from 0. while rank starts from 1. so we subtract 1.
}

template<class T>
int AVL_tree<T>::select(Node* node, int i) {
    if (sort_by_score != SORT_BY_SCORE){
        throw std::logic_error("getting rank from the id tree. wrong tree.");
    }
    if (node == nullptr){
        throw std::logic_error("nullptr in rank finding. rank outside of tree range or tree not sorted well");
    }
    if (i < 1){
        throw std::logic_error("looking for too small rank");
    }

    //code copied from find()
    while(true){ //while true loop ok because in every case we either return or go down tree.
        int difference = get_weight(node->left) - (i - 1);
        if (difference == 0){
            return node->content->get_id();
        }
        if (difference > 0)  { //proceed to left branch.
            return find_ith_rank_id(node->left, i);
        }
        else{ //proceed to right branch
            return find_ith_rank_id(node->right, i - get_weight(node->left) - 1);
        }
    }
}

// ----------------------------------



#endif // AVL_TREE_H