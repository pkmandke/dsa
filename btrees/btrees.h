#ifndef BTREES_H_
#define BTREES_H_

namespace btree{

class Node{

    public:
        int key, value, count = 0;
        Node *left = NULL, *right = NULL;
        
        Node(int, int);
        Node(int, int, int);
};

class BST{
    
    private:
        Node *root, *minNode = NULL;
        
        static int _find(Node *, int );
        static Node *_put(Node *, int, int);
        static int _floor(Node *, int);
        static int _ceil(Node *, int);
        static void _inorder(Node *);
        static int _rank(Node *, int, int);

    public:
        BST();
        BST(Node *);
        int get(int);
        void put(int , int );
        void inorder();
        int floor(int);
        int ceil(int);
        int rank(int);
        void deleteMin();
        Node *_delete_min(Node *);
        void deleteNodeRecursive(int);
        Node *_delete_node(Node *, int);
};

}
#endif
