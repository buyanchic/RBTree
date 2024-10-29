#ifndef RB_TREE_PRIVATE_METHODS_H
#define RB_TREE_PRIVATE_METHODS_H 1

#include <stdexcept>

#include "rbtree.h"

void RBTree::_show(Node *p, int level) {
    if (p == NIL) return;
    _show(p->right, level + 1);
    for (int i = 0; i < level; i++)
        std::cout << "\t";
    p->color == black ? (std::cout << p->key) : (std::cout << "\033[31m" << p->key << "\033[0m");
    std::cout << "\n";
    _show(p->left, level + 1);
}

Node *RBTree::search(const int &key) {
    if (!root)
        return nullptr;
    Node *n = root;
    while (true) {
        if (key == n->key)
            return n;
        else if (key < n->key) {
            if (n->left != NIL)
                n = n->left;
            else
                return nullptr;
        } else {
            if (n->right != NIL)
                n = n->right;
            else
                return nullptr;
        }
    }
}

Node *&RBTree::find_pos_to_put(const int &key, Node *&parent) {
    if (!root) {
        parent = nullptr;
        return root;
    }
    Node *n = root;
    while (true)
        if (key < n->key) {
            if (n->left != NIL)
                n = n->left;
            else {
                parent = n;
                return n->left;
            }
        } else {
            if (n->right != NIL)
                n = n->right;
            else {
                parent = n;
                return n->right;
            }
        }
}

Node *RBTree::get_brother(Node *nd) {
    if (!nd->parent)
        throw runtime_error("нет бати");
    if (nd == nd->parent->left)
        return nd->parent->right;
    return nd->parent->left;
}

bool RBTree::is_left(Node *nd, Node *parent) {
//    if (!(is_nil(nd)) || !nd->parent)
//        throw runtime_error("нет бати");
    if (nd == parent->left)
        return true;
    return false;
}

bool RBTree::is_right(Node *nd) {
    return !is_left(nd, nd->parent);
}

bool RBTree::is_nil(Node *nd) {
    return (nd == NIL);
}

void RBTree::left_rotation(Node *top, Node *bottom) {
    if (!top || !bottom)
        throw runtime_error("Not enough nodes to rotation");
    if (bottom->left != NIL) {
        bottom->left->parent = top;
    }
    top->right = bottom->left;
    bottom->parent = top->parent;
    bottom->left = top;
    if (top->parent) {
        if (top->parent->left == top)
            bottom->parent->left = bottom;
        else
            bottom->parent->right = bottom;
    } else
        root = bottom;
    top->parent = bottom;
}

void RBTree::right_rotation(Node *top, Node *bottom) {
    if (!top || !bottom)
        throw std::exception();
    if (bottom->right != NIL) {
        bottom->right->parent = top;
    }
    top->left = bottom->right;
    bottom->parent = top->parent;
    bottom->right = top;
    if (top->parent) {
        if (top->parent->left == top)
            bottom->parent->left = bottom;
        else
            bottom->parent->right = bottom;
    } else
        root = bottom;
    top->parent = bottom;
}


Node *RBTree::get_node_with_next_key(Node *node) {
    if (node->right == NIL)
        throw std::runtime_error("нет узла со следующим значением!");
    Node *nn = node->right;
    if (!nn->left)
        return nn;
    while (nn->left)
        nn = nn->left;
    return nn;
}

bool RBTree::have_red_sons(Node *nd) {
    if (nd->left->color == red || nd->right->color == red)
        return true;
    return false;
}

#endif // RB_TREE_PRIVATE_METHODS_H