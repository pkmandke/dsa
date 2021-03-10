/* Implementation of BST methods */

#include <iostream>

#include "btrees.h"

using namespace btree;

// Constructors
Node::Node(int k, int v) { key = k; value = v; }
Node::Node(int k, int v, int c) : key(k), value(v), count(c) { }

BST::BST() { root = NULL; }
BST::BST(Node *r) { root = r; }

// Find the node corresponding to given key
int BST::_find(Node *r, int k){
    
    if(r == NULL) return -1;
    
    if(k == r->key) return r->value;

    if(k < r->key) return _find(r->left, k);
    else return _find(r->right, k);
}

// get value for key API
int BST::get(int k){

    return BST::_find(this->root, k);
}

// utility to put key value pair in the tree; rewrite node value if already exists
Node *BST::_put(Node *r, int k, int v){

    if ( r == NULL ) return new Node(k, v, 1);
    
    if( k == r->key) r->value = v;
    else if( k < r->key ){
        r->left = _put(r->left, k, v);
    }
    else{
        r->right = _put(r->right, k, v);
    }

    r->count++;
    return r;
}

// API to put key-value pair in tree
void BST::put(int k, int v){
    
    this->root = _put(this->root, k, v);
}

// utility to get largest key smaller than given key
int BST::_floor(Node *r, int k){
    
    if(r == NULL) return -1;

    if(r->key == k) return r->key;

    if(k < r->key) return _floor(r->left, k);
    else{
        
        if(r->right){
            if(k < r->right->key) return r->key;
            else return _floor(r->right, k);
        }
        else return r->key;
    }
}

// API to return largest key less than the given key
int BST::floor(int k){
    return _floor(this->root, k);
}

// utility to return the ceil of given key
int BST::_ceil(Node *r, int k){
    
    if(r == NULL) return -1;

    if(r->key == k) return k;

    if(k > r->key) return _ceil(r->right, k);
    else{
        if(r->left){
            if(k > r->left->key) return r->key;
            else return _ceil(r->left, k);
        }
        else return r->key;
    }
}

// API to return smallest key greater than the given key
int BST::ceil(int k){

    return _ceil(this->root, k);
}

// utility to compute rank of given key
int BST::_rank(Node *r, int k, int rank){
    
    if(r == NULL) return rank;

    if(k == r->key){
        if(r->left) return rank + r->left->count + 1;
        else return rank + 1;
    }

    if(k < r->key) return _rank(r->left, k, rank);
    else{
        if(r->left) rank += r->left->count;
        rank++;
        return _rank(r->right, k, rank);
    }

}

// rank of given key: # of keys less than given key
int BST::rank(int k){

    return _rank(this->root, k, 0);
}


// Delete min key
Node *BST::_delete_min(Node *r){
    
    if(r == NULL) return NULL;

    if(r->left == NULL){
        Node *t = r->right;
        this->minNode = r;
        return t;
    }
    else{
        r->left = _delete_min(r->left);
        r->count--;
        return r;
    } 
}

void BST::deleteMin(){
    
    this->minNode = NULL;
    this->root = _delete_min(this->root);
    if(this->minNode) delete this->minNode;
}

// Recursive hibbard deletion
Node *BST::_delete_node(Node *r, int k){
    
    if(r == NULL) return NULL;

    if(k < r->key) r->left = _delete_node(r->left, k);
    else if(k > r->key) r->right = _delete_node(r->right, k);
    else{ // if key is found, delete it
        
        if(r->left == NULL) return r->right;
        if(r->right == NULL) return r->left;

        r->right = _delete_min(r->right);
        if(this->minNode){
            Node *new_node = new Node(this->minNode->key, this->minNode->value);
            new_node->right = r->right;
            new_node->left = r->left;
            Node *temp = r;
            delete temp;
            delete this->minNode;
            r = new_node;
        }
    }
    r->count = 1;
    if(r->right) r->count += r->right->count;
    if(r->left) r->count += r->left->count;
    return r;
}

void BST::deleteNodeRecursive(int k){
    this->minNode = NULL;
    this->root = _delete_node(this->root, k);
}

// In order traversal
void BST::_inorder(Node *r){
    
    if(r){
        _inorder(r->left);
        std::cout << "(" << r->key << ", " << r->count << "), ";
        _inorder(r->right);
    }
}

void BST::inorder(){
    
    _inorder(this->root);
    std::cout << std::endl;
}
