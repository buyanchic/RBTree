#ifndef RBT_TESTS_H
#define RBT_TESTS_H 1

#include <iostream>
#include <random>
#include <array>
#include <stack>
#include <vector>

#include "structure/rbtree.h"

using namespace std;

class Tests {
public:

    static RBTree *create_random_tree_layout(int count = 100000, int maxKey = 100000) {
        RBTree *t = new RBTree();

        for (int i = 0; i < count; i++) {
            t->put(rand() % maxKey + 1);
        };
        return t;
    }

    static bool root_is_black(RBTree *t) {
        return (t->root->color == black);
    }

    static bool twice_red(RBTree *t) {
        auto st = stack<Node *>();
        if (t->root)
            st.push(t->root);
        while (!st.empty()) {
            Node *top = st.top();
            st.pop();
            if (top->parent)
                if (top->color == red && top->parent->color == red)
                    return false;
            if (top->right) {
                st.push(top->right);
            }
            if (top->left)
                st.push(top->left);
        }
        return true;
    }

    static bool black_height(RBTree *t) {
        int fixed_height = 0;
        bool isFixed = false;
        auto st = stack<pair<Node *, int>>();
        if (t->root)
            st.emplace(t->root, 0);
        while (!st.empty()) {
            auto top = st.top();
            st.pop();
            // создал указатель для сокращения (часто используется)
            Node *nd = top.first;
            // проверяем текущий узел
            bool bl = (nd->color == black);
            int my_height = top.second + bl;
            // если отсутствуют дети
            if (!nd->left && !nd->right) {
                // попали в лист в первый раз - фиксируем значение
                if (!isFixed) {
                    isFixed = true;
                    fixed_height = my_height;
                } else {
                    // если попали не в первый раз
                    if (my_height != fixed_height)
                        return false;
                }
            }
            // добавляем детей (если есть)
            if (nd->left) st.emplace(nd->left, my_height);
            if (nd->right) st.emplace(nd->right, my_height);
        }
        return true;
    }

    static bool test_random_tree(RBTree *t) {
        try {
            t->left_rotation(t->root, t->root->right);
        } catch (const std::exception &e) {
            return false;
        }
        delete t;
        return true;
    }

    static RBTree *create_basic_tree_layout() {
        RBTree *t = new RBTree();
        int vals[] = {2, 1, 4, 3, 7, 6, 9, 2};
        for (const auto &v: vals) {
            t->put(v);
        };
        return t;
    }

    static bool test_right_rotation(RBTree *t) {
        try {
            t->show();
            std::cout << "---------------------------------" << std::endl;
            t->right_rotation(t->root, t->root->left);
            t->show();
        } catch (const std::exception &e) {
            return false;
        }
        delete t;
        return true;
    }

    static bool test_left_rotation(RBTree *t) {
        try {
            t->show();
            std::cout << "---------------------------------" << std::endl;
            t->left_rotation(t->root, t->root->right);
            t->show();
        } catch (const std::exception &e) {
            return false;
        }
        delete t;
        return true;
    }

    static bool test_put(RBTree *t) {
        //t->show();
        delete t;
        return true;
    }

    static bool test_remove(RBTree *t, int key) {
        //t->show();
        t->remove(key);
        //t->show();
        delete t;
        return true;
    }

    static bool test_random_remove(RBTree *t) {

        for (int i = 0; i < 10000; i++) {
            int q = rand() % 10000;
            //std::cout<<"***\n"<<  q <<"\n***\n";
            t->remove(q );
            //t->show();
        };
//        t->show();

        delete t;
        return true;
    }
};


#endif //RBT_TESTS_H
