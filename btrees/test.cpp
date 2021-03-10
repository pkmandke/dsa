/* Test cases for BST methods */

#include <iostream>
#include <cassert>

#include "btrees.h"

using namespace btree;

void test_hibbard_delete(){

    Node *n = new Node(5, 4, 1);
    BST b(n);

    int a[] = {3, 7, 1, 4, 9, 6};

    for(auto i = 0; i < 6; i++) b.put(a[i], 10);
    b.inorder();

    b.deleteNodeRecursive(5);
    b.inorder();
}

void test_deletion(){

    Node *n = new Node(5, 4, 1);
    BST b(n);

    int a[] = {3, 7, 1, 4, 9, 6};

    for(auto i = 0; i < 6; i++) b.put(a[i], 10);
    b.inorder();

    b.deleteMin();
    b.deleteMin();
    b.deleteMin();
    b.deleteMin();
    b.inorder();
    b.deleteMin();
    b.inorder();
    b.deleteMin();
    b.inorder();
    b.deleteMin();
    b.inorder();
    b.deleteMin();
    b.inorder();

}

void test_rank(){

    Node n(5, 4, 1);
    BST b(&n);

    int a[] = {3, 7, 1, 4, 9, 6};

    for(auto i = 0; i < 6; i++) b.put(a[i], 10);
    b.inorder();
    std::cout << b.rank(9) << std::endl;
    assert(b.rank(100) == 7);
    assert(b.rank(9) == 7);
    assert(b.rank(5) == 4);
    assert(b.rank(4) == 3);
    assert(b.rank(6) == 5);
    assert(b.rank(8) == 6);
}


void test_floor_ceil(){

    Node n(5, 4, 1);
    BST b(&n);

    int a[] = {3, 7, 1, 4, 9, 6};

    for(auto i = 0; i < 6; i++) b.put(a[i], 10);
    b.inorder();
    // std::cout << "Floor of 7 = " << b.floor(8) << std::endl;
    assert(b.floor(8) == 7);
    assert(b.ceil(100) == -1);
    assert(b.ceil(2) == 3);
    assert(b.ceil(7) == 7);
    assert(b.ceil(8) == 9);
}

void test_create_object(){
    
    Node n(3, 4, 1);
    BST b(&n);

    b.put(1, 3);
    std::cout << "Value = " << b.get(3) << std::endl;
}

int main(int argc, char *argv[]){
    
    // test_create_object();
    // test_floor_ceil();
    // test_rank();
    // test_deletion();
    test_hibbard_delete();
    return 0;
}
