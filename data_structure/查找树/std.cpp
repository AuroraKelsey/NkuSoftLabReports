#include <iostream>

using namespace std;

int main() {
    for (int i = 20000; i <= 400000; i += 20000) {
        freopen("in.txt", "w", stdout);
        cout << i << endl;
        system("./mk");
        system("./normal_bst");
        system("./AVL_tree");
        system("./Btree");
        system("./RBtree");
    }

    return 0;
}