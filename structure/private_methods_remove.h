#ifndef RBT_PRIVATE_METHODS_REMOVE_H
#define RBT_PRIVATE_METHODS_REMOVE_H

#include <stdexcept>

#include "rbtree.h"

void RBTree::fixup_after_remove(Node *nd) {
    if (nd->parent == nullptr)
        return;
    Node *bro = get_brother(nd);
    if (bro && bro->color == red) {
        fixup_brother_red(nd, bro);
        return;
    }
    if (!bro || (bro->color == black && !have_red_sons(bro))) {
        fixup_brother_and_sons_black(nd, bro);
        return;
    }
    if (check_brother_black_internal_son_red(bro)) {
        fixup_brother_black_internal_son_red(nd, bro);
        return;
    }
    if (check_brother_black_external_son_red(bro)) {
        fixup_external_son_red(nd, bro);
        return;
    } else
        throw runtime_error("error in fixup_after_remove");
}

void RBTree::fixup_brother_red(Node *tb, Node *br) {
    if (is_left(tb, tb->parent))
        left_rotation(tb->parent, br);
    else
        right_rotation(tb->parent, br);
    tb->parent->parent->color = black;
    tb->parent->color = red;
    fixup_after_remove(tb);
}

void RBTree::fixup_brother_and_sons_black(Node *tb, Node *br) {
    if (br)
        br->color = red;
    if (tb->parent->color == red) {
        tb->parent->color = black;
        return;
    } else {
        fixup_after_remove(tb->parent);
        return;
    }
}

void RBTree::fixup_brother_black_internal_son_red(Node *tb, Node *br) {
    br->color = red;
    if (is_right(br))
        right_rotation(br, br->left);
    else
        left_rotation(br, br->right);
    br->parent->color = black;
    fixup_after_remove(tb);
}

void RBTree::fixup_external_son_red(Node *tb, Node *br) {
    tb->parent->color == black ? br->color = black : br->color = red;
    tb->parent->color = black;
    if (is_right(br)) {
        left_rotation(br->parent, br);
        br->right->color = black;
    } else {
        right_rotation(br->parent, br);
        br->right->color = black;
    }
}

bool RBTree::check_brother_black_internal_son_red(Node *br) {
    if (br->left)
        if (br->color == black && is_right(br) && br->left->color == red && (!br->right || br->right->color == black))
            return true;
    if (br->right)
        if ((br->color == black && is_left(br, br->parent) && br->right->color == red) && (!br->left || br->left->color == black))
            return true;
    return false;
    // throw "error in check_brother_black_internal_son_red";
}

bool RBTree::check_brother_black_external_son_red(Node *br) {
    if (br->color == black && is_right(br) && br->right->color == red)
        return true;
    if (br->color == black && is_left(br, br->parent) && br->left->color == red)
        return true;
    return false;
    // throw "error in check_brother_black_internal_son_red";
}

void RBTree::_remove(Node *nd) {
    if (nd->left != NIL && nd->right != NIL)
        _remove_2_descendants(nd);
    if (nd->left != NIL || nd->right != NIL)
        _remove_1_descendant(nd);
    if (nd->left == NIL && nd->right == NIL)
        _remove_0_descendant(nd);
    else
        throw runtime_error("error in _remove");
}

void RBTree::_remove_2_descendants(Node *nd) {
    Node *nn = get_node_with_next_key(nd);
    nd->key = nn->key;
}

void RBTree::_remove_1_descendant(Node *nd) {
    Node *son = (nd->left) ? nd->left : nd->right;
    if (nd == this->root) {
        this->root = son;
        son->color = black;
        son->parent = nullptr;
        delete son;
    } else {
        nd->key = son->key;
    }
}

void RBTree::_remove_0_descendant(Node *nd) {
    if (!nd->parent)
        this->root = nullptr;
    if (nd->color == red) {
        if (nd->parent->left == nd)
            nd->parent->left = nullptr;
        else
            nd->parent->right = nullptr;
    } else {
        fixup_after_remove(nd);
        if (nd->parent && nd->parent->left == nd) {
            nd->parent->left = nullptr;
        } else if (nd->parent && nd->parent->right == nd) {
            nd->parent->right = nullptr;
        }
    }
    delete nd;
}


#endif //RBT_PRIVATE_METHODS_REMOVE_H
