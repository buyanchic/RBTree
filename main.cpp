#include <iostream>
#include "tests.h"

using namespace std;

int main() {
    auto t = Tests::create_random_tree_layout(10000000, 10000000);
    cout << "root_is_black " << (Tests::root_is_black(t)) << endl;
    cout << "twice_red " << (Tests::twice_red(t)) << endl;
    cout << "black_height " << (Tests::black_height(t)) << endl;
//    Tests::test_random_remove(t, 2000000, 1000000);
//    cout << (Tests::root_is_black(t) && Tests::twice_red(t) && Tests::black_height(t)) << endl;
    return 0;
}