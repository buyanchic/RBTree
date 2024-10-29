#ifndef RB_TREE_H
#define RB_TREE_H 1

class Tests;

#include "rbnode.h"

class RBTree {
    friend Tests;
    Node *root;
    Node *NIL;

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
    Node *&find_pos_to_put(const int &key, Node *&parent);

    /// Левое вращение
    void left_rotation(Node *top, Node *bottom);

    /// Правое вращение
    void right_rotation(Node *top, Node *bottom);

    /// Получить брата
    static Node *get_brother(Node *nd);

    /// Получить true, если узел - левый
    static bool is_left(Node *nd, Node *parent);

    /// Получить true, если узел - правый
    static bool is_right(Node *nd);

    bool is_nil(Node *nd);

    /// Получить узел со следующим значением
    Node *get_node_with_next_key(Node *node);

    /// Балансировка после вставки
    void fixup_after_insertion(Node *nd);

    static void fixup_case1_red_uncle(Node *&nd, Node *uncle);

    void fixup_case2_black_uncle(Node *nd, Node *uncle);

    /// Балансировка после удаления
    void fixup_after_remove(Node *nd);

    ///
    void _remove_2_descendants(Node *nd);

    ///
    void _remove_0_descendant(Node *nd);

    ///
    void _remove_1_descendant(Node *nd);

    /* Хуева */

    /// Есть ли красные дети
    static bool have_red_sons(Node *nd);

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
    static bool check_brother_black_external_son_red(Node *br);


};

#include "public_methods.h"
// #include "private_methods.h"
#include "private_methods_remove.h"
#include "private_methods_insert.h"
#endif // RB_TREE_H