#ifndef RB_TREE_H
#define RB_TREE_H 1

class Tests;

#include "rbnode.h"

class RBTree {
    friend Tests;
private:
    Node *root;

public:
    RBTree();
    ~RBTree();

    /// Показать дерево
    void show();

    /// Вставить узел с ключом key
    void put(const int &key);

    /// Удалить узел с ключом key
    void remove(const int &key);

    /// Проверить содержание ключа в дереве
    bool contains(const int &key);

    // Экстремумы ключей
    int min();
    int max();

private:
    void _remove(Node *nd);

    /// показать дерево
    void _show(Node *p, int level);

    /// Поиск узла в дереве по ключу
    Node *search(const int &key);

    /// Проверить отца
    void checking_father(Node *nd);

    /// Проверить дядю
    void check_uncle(Node *nd, Node *parent);

    /// Проверить конкретного дядю
    void check_which_uncle(Node *nd, Node *uncle);

    /// Поиск позиции для вставки
    Node *&find_pos_to_default_put(const int &key, Node *&parent);

    /// Левое вращение
    void left_rotation(Node *top, Node *bottom);

    /// Правое вращение
    void right_rotation(Node *top, Node *bottom);

    /// Получить брата
    static Node *ptr_to_brother(Node *nd);

    /// Получить true, если узел - левый
    static bool is_left(Node *&nd);

    /// Получить true, если узел - правый
    static bool is_right(Node *nd);

    /// Получить ближайшего соседа справа
    static Node *get_nearest_neighbour(Node *node);

    /// Перекраска
    void repaint(Node *tb);

    /// Есть ли красные дети
    static bool red_childs(Node *nd);

    static bool case4_in_repaint(Node *br);
};

#include "public_methods.h"
#include "private_methods.h"
#endif // RB_TREE_H