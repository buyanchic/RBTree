#ifndef RB_TREE_PUBLIC_METHODS_H
#define RB_TREE_PUBLIC_METHODS_H 1

#include <stdexcept>
#include <iostream>
#include <cassert>
#include <stack>

#include "rbtree.h"

using namespace std;

RBTree::RBTree() {
    root = nullptr;
}

RBTree::~RBTree() {
    auto st = stack<Node*>();
    if (root)
        st.push(root);
    while (!st.empty()) {
        Node *top = st.top();
        st.pop();
        if (top->right)
            st.push(top->right);
        if (top->left)
            st.push(top->left);
        delete top;
    }
}

void RBTree::show() {
    _show(root, 0);
    std::cout << "\n\n\n" << std::endl;
}

void RBTree::put(const int &key) {
    if (contains(key))
        return;
    Node *parent = nullptr;
    Node *nd = new Node(key);
    Node *&insertion_place = find_pos_to_default_put(key, parent);
    insertion_place = nd;
    nd->parent = parent;

    fixup_after_insertion(nd);
}


void RBTree::remove(const int &key) {
    Node *nd = search(key);
    if (nd)
        _remove(nd);
}

bool RBTree::contains(const int &key) {
    return (bool) search(key);
}

int RBTree::min() {
    assert(root);
    Node *n = root;
    while (n->left)
        n = n->left;
    return n->key;
}

int RBTree::max() {
    assert(root);
    Node *n = root;
    while (n->right)
        n = n->right;
    return n->key;
}

#endif // RB_TREE_PUBLIC_METHODS_H