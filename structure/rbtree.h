#ifndef RB_TREE_H
#define RB_TREE_H 1

class Tests;

#include "rbnode.h"

class RBTree {
    friend Tests;
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
    /* Заебись */
    ///
    void _remove(Node *nd);

    /// Вывести дерево
    void _show(Node *p, int level); // название странное

    /// Поиск узла в дереве по ключу
    Node *search(const int &key);

    /// Поиск позиции для вставки
    Node *&find_pos_to_default_put(const int &key, Node *&parent); // почему дифолт

    /// Левое вращение
    void left_rotation(Node *top, Node *bottom);

    /// Правое вращение
    void right_rotation(Node *top, Node *bottom);

    /// Получить брата
    static Node *get_brother(Node *nd);

    /// Получить true, если узел - левый
    static bool is_left(Node *nd);

    /// Получить true, если узел - правый
    static bool is_right(Node *nd);

    /// Получить узел со следующим значением
    static Node *get_node_with_next_key(Node *node);

    /// Балансировка после вставки
    void fixup_after_insertion(Node *nd);

    /// Балансировка после удаления
    void fixup_after_deletion(Node *nd);

    ///
    void _remove_2_descendants(Node *nd);

    ///
    void _remove_0_descendant(Node *nd);

    ///
    void _remove_1_descendant(Node *nd);

    /* Хуева */
    /// Проверить конкретного дядю
    void check_side_uncle(Node *nd, Node *uncle);

    /// Есть ли красные дети
    static bool not_red_sons(Node *nd);

    ///
    static bool check_brother_black_internal_son_red(Node *br);

    ///
    void fixup_brother_red(Node *tb, Node *br);

    ///
    void fixup_brother_and_sons_black(Node *tb, Node *br);

    ///
    void fixup_brother_black_internal_son_red(Node *tb, Node *br);

    ///
    void fixup_external_son_red(Node *tb, Node *br);

    ///
    bool check_brother_black_external_son_red(Node *br);
};

#include "public_methods.h"
#include "private_methods.h"
#endif // RB_TREE_H