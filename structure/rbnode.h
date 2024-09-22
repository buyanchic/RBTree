#ifndef _NODE_H
#define _NODE_H 1

class Tests;

enum MenuColor {
    red = 0,
    black = 1
};

class Node {
    friend Tests;
public:
    int key;
    Node *parent;
    Node *left;
    Node *right;
    MenuColor color;

public:
    explicit Node(const int &key) {
        this->key = key;
        this->parent = nullptr;
        this->left = nullptr;
        this->right = nullptr;
        this->color = red;
    }
};

#endif // _NODE_H