//#include "rbtree.h"

void RBTree::_show(Node *p, int level) {
    if (p) {
        _show(p->right, level + 1);
        for (int i = 0; i < level; i++) {
            std::cout << "\t";
        }
        p->color == black ? (std::cout << p->key) : (std::cout << "\033[31m" << p->key << "\033[0m");
        std::cout << "\n";
        _show(p->left, level + 1);
    }
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

void RBTree::checking_father(Node *nd) {
    if (!nd->parent || nd->parent->color == black) {
        return;
    } else {
        check_uncle(nd, nd->parent);
    }
}

void RBTree::check_which_uncle(Node *nd, Node *uncle) {
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


void RBTree::check_uncle(Node *nd, Node *parent) {
    Node *uncle = ptr_to_brother(nd->parent);
    if (!uncle || (uncle->color == black)) {
        check_which_uncle(nd, uncle);
    } else {
        parent->color = black,
        uncle->color = black;
        if (uncle->parent != root) {
            uncle->parent->color = red;
            checking_father(nd->parent->parent);
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

Node *RBTree::ptr_to_brother(Node *nd) {
    if (!nd->parent)
        return nullptr;
    if (nd == nd->parent->left)
        return nd->parent->right;
    return nd->parent->left;
}

bool RBTree::is_left(Node *&nd) {
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


Node *RBTree::get_nearest_neighbour(Node *node) {
    if (!node->right)
        std::cout << "Нет ближайшего соседа!" << std::endl;
    Node *nn = node->right;
    if (!nn->left)
        return nn;
    while (nn->left)
        nn = nn->left;
    return nn;
}

bool RBTree::red_childs(Node *nd) {
    if (nd->left && nd->left->color == red || nd->right && nd->right->color == red)
        return true;
    return false;
}


void RBTree::repaint(Node *tb) {
    if (tb->parent== nullptr)
        return;
    Node *br = ptr_to_brother(tb);
    if (br && br->color == red) {
        if (is_left(tb))
            left_rotation(tb->parent, br);
        else
            right_rotation(tb->parent, br);
        tb->parent->parent->color = black;
        tb->parent->color = red;
        repaint(tb);
        return;
    }
    if (!br || (br && br->color == black && !red_childs(br))) {
        if (br)
            br->color = red;
        if (tb->parent->color == red) {
            tb->parent->color = black;
            return;
        } else {
            repaint(tb->parent);
            return;
        }
    }
    if (case4_in_repaint(br) ) {
        if (is_right(br)) {
            br->color = red;
            right_rotation(br, br->left);
            br->parent->color = black;
            repaint(tb);
        }
        else {
            right_rotation(br->parent, br);
        }
        return;
    }
    if ((!br || br->color == black) && br->right->color == red) {
        left_rotation(br->parent, br);
        tb->parent->color == black ? br->color = black : br->color = red;
        tb->parent->color = black;
        br->right->color = black;
        return;
    }
}

bool RBTree::case4_in_repaint(Node *br) {
    if (!br || !br->left)
        return false;
    if ((br->color == black && br->left->color == red) &&
    (!br->right || br->right->color == black))
        return true;
    return false;
}

void RBTree::_remove(Node *nd) {
    if (!nd)
        return;
    // 2 descendants
    if (nd->left && nd->right) {
        Node *nn = get_nearest_neighbour(nd);
        nd->key = nn->key;
        _remove(nn);
        return;
    }
    // 0 descendants
    if (!nd->left && !nd->right) {
        if (!nd->parent)
            this->root = nullptr;
        if (nd->color == red)
        {
            if (nd->parent->left == nd)
                nd->parent->left = nullptr;
            else
                nd->parent->right = nullptr;
        }
        else {
            repaint(nd);
            if (nd->parent && nd->parent->left == nd)
                nd->parent->left = nullptr;
            else if (nd->parent && nd->parent->right == nd)
                nd->parent->right = nullptr;
        }
        delete nd;
        return;
    }
    // 1 descendant
    Node *son = (nd->left) ? nd->left : nd->right;
    if (nd == this->root) {
        this->root = son;
        son->color = black;
        son->parent = nullptr;
    } else {
        nd->key = son->key;
        _remove(son);
    }
}