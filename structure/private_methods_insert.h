#ifndef RBT_PRIVATE_METHODS_INSERT_H
#define RBT_PRIVATE_METHODS_INSERT_H

#include <stdexcept>

#include "private_methods.h"

void RBTree::fixup_after_insertion(Node *nd) {
    while (true) {
        // Узел корень
        if (nd == root) {
            nd->color = black;
            return;
        }
        // Батя черный (может быть корнем)
        if (nd->parent->color == black)
            return;
        Node *uncle = get_brother(nd->parent);
        // Случаи с дядей
        if (uncle->color == red)
            fixup_case1_red_uncle(nd, uncle);
        else
            return fixup_case2_black_uncle(nd, uncle);
    }
}

void RBTree::fixup_case1_red_uncle(Node *&nd, Node *uncle) {
    nd->parent->color = black;
    uncle->color = black;
    nd->parent->parent->color = red;
    nd = nd->parent->parent;
}

void RBTree::fixup_case2_black_uncle(Node *nd, Node *uncle) {
    bool nd_is_left = is_left(nd, nd->parent);
    bool uncle_is_left = is_left(uncle, nd->parent->parent);
    bool nd_is_inner = (nd_is_left == uncle_is_left);
    // доп вращение (если узел внутренний)
    if (nd_is_inner) {
        if (nd_is_left) {
            right_rotation(nd->parent, nd);
            nd = nd->right;
        } else {
            left_rotation(nd->parent, nd);
            nd = nd->left;
        }
    }
    // безусловная перекраска
    nd->parent->color = black;
    nd->parent->parent->color = red;
    // безусловный поворот
    if (uncle_is_left)
        left_rotation(nd->parent->parent, nd->parent);
    else
        right_rotation(nd->parent->parent, nd->parent);
}

#endif //RBT_PRIVATE_METHODS_INSERT_H
