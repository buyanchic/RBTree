#include <iostream>
#include "tests.h"

using namespace std;

int main() {
    //Tests::test_put(Tests::create_random_tree_layout());
    auto t = Tests::create_random_tree_layout(1000000, 1000000);
    cout << (Tests::root_is_black(t) && Tests::twice_red(t) && Tests::black_height(t)) << endl;
    Tests::test_random_remove(t);
    cout << (Tests::root_is_black(t) && Tests::twice_red(t) && Tests::black_height(t)) << endl;
    return 0;
    //Tests::test_random_remove(Tests::create_random_tree_layout());
}