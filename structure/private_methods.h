#ifndef RB_TREE_PRIVATE_METHODS_H
#define RB_TREE_PRIVATE_METHODS_H 1

#include <stdexcept>

#include "rbtree.h"

void RBTree::_show(Node *p, int level) {
    if (!p) return;
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
            if (n->left)
                n = n->left;
            else
                return nullptr;
        } else {
            if (n->right)
                n = n->right;
            else
                return nullptr;
        }
    }
}

Node *&RBTree::find_pos_to_default_put(const int &key, Node *&parent) {
    if (!root) {
        parent = nullptr;
        return root;
    }
    Node *n = root;
    while (true)
        if (key < n->key) {
            if (n->left)
                n = n->left;
            else {
                parent = n;
                return n->left;
            }
        } else {
            if (n->right)
                n = n->right;
            else {
                parent = n;
                return n->right;
            }
        }
}

Node *RBTree::get_brother(Node *nd) {
    if (!nd->parent)
        return nullptr;
    if (nd == nd->parent->left)
        return nd->parent->right;
    return nd->parent->left;
}

bool RBTree::is_left(Node *nd) {
    if (nd == nd->parent->left)
        return true;
    return false;
}

bool RBTree::is_right(Node *nd) {
    if (nd == nd->parent->right)
        return true;
    return false;
}

void RBTree::left_rotation(Node *top, Node *bottom) {
    if (!top || !bottom)
        throw std::exception();
    if (bottom->left) {
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
    if (bottom->right) {
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
    if (!node->right)
        throw std::runtime_error("нет узла со следующим значением!");
    Node *nn = node->right;
    if (!nn->left)
        return nn;
    while (nn->left)
        nn = nn->left;
    return nn;
}

bool RBTree::not_red_sons(Node *nd) {
    if (nd->left && nd->right)
        if (nd->right->color == black && nd->left->color == black)
            return true;
    if (nd->left && !nd->right)
        if (nd->left->color == black)
            return true;
    if (nd->right && !nd->left)
        if (nd->right->color == black)
            return true;
    if (!nd->left && !nd->right)
        return true;
    return false;
}

void RBTree::fixup_after_deletion(Node *nd) {
    if (nd->parent == nullptr)
        return;
    Node *bro = get_brother(nd);
    if (bro && bro->color == red) {
        fixup_brother_red(nd, bro);
        return;
    }
    if (!bro || (bro && bro->color == black && not_red_sons(bro))) {
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
        throw "error in fixup_after_deletion";
}

void RBTree::fixup_brother_red(Node *tb, Node *br) {
    if (is_left(tb))
        left_rotation(tb->parent, br);
    else
        right_rotation(tb->parent, br);
    tb->parent->parent->color = black;
    tb->parent->color = red;
    fixup_after_deletion(tb);
}

void RBTree::fixup_brother_and_sons_black(Node *tb, Node *br) {
    if (br)
        br->color = red;
    if (tb->parent->color == red) {
        tb->parent->color = black;
        return;
    } else {
        fixup_after_deletion(tb->parent);
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
    fixup_after_deletion(tb);
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
        if ((br->color == black && is_left(br) && br->right->color == red) && (!br->left || br->left->color == black))
            return true;
    return false;
    // throw "error in check_brother_black_internal_son_red";
}

bool RBTree::check_brother_black_external_son_red(Node *br) {
    if (br->color == black && is_right(br) && br->right->color == red)
        return true;
    if (br->color == black && is_left(br) && br->left->color == red)
        return true;
    return false;
    // throw "error in check_brother_black_internal_son_red";
}

void RBTree::_remove(Node *nd) {
    if (nd->left && nd->right)
        _remove_2_descendants(nd);
    if (nd->left || nd->right)
        _remove_1_descendant(nd);
    if (!nd->left && !nd->right)
        _remove_0_descendant(nd);
    else
        throw "error in _remove";
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
        fixup_after_deletion(nd);
        if (nd->parent && nd->parent->left == nd) {
            nd->parent->left = nullptr;
        } else if (nd->parent && nd->parent->right == nd) {
            nd->parent->right = nullptr;
        }
    }
    delete nd;
}

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
        if (!uncle || (uncle->color == black)) {
            check_side_uncle(nd, uncle);
        } else {
            nd->parent->color = black;
            uncle->color = black;
            if (uncle->parent != root) {
                uncle->parent->color = red;
                nd = nd->parent->parent;
                continue;
            }
        }
    }
}

void RBTree::check_side_uncle(Node *nd, Node *uncle) {
    Node *ex_grandpa = nd->parent->parent;
    if (is_left(nd->parent)) {
        (ex_grandpa->color == red) ? (ex_grandpa->color = black) : (ex_grandpa->color = red);
        if (is_right(nd))
            left_rotation(nd->parent, nd);
        right_rotation(ex_grandpa, ex_grandpa->left);
        (ex_grandpa->parent->color == red) ? (ex_grandpa->parent->color = black) : (ex_grandpa->parent->color = red);
    } else {
        (ex_grandpa->color == red) ? (ex_grandpa->color = black) : (ex_grandpa->color = red);
        if (is_left(nd))
            right_rotation(nd->parent, nd);
        left_rotation(ex_grandpa, ex_grandpa->right);
        (ex_grandpa->parent->color == red) ? (ex_grandpa->parent->color = black) : (ex_grandpa->parent->color = red);
    }
}

#endif // RB_TREE_PRIVATE_METHODS_H