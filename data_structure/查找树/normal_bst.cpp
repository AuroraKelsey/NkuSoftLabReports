#include <iostream>
#include <queue>
#include <ctime>
#include <fstream>

using namespace std;
const int N = 400000;

template<class T>
class node {
public:
    T key;
    node *left;
    node *right;

    node(T value, node *l, node *r) : key(value), left(l), right(r) {}
};

template<class T>
class BST {
public:
    node<T> *root;

    BST() : root(NULL) {}

    ~BST() {
        destroy(root);
    }

    void destroy(node<T> *rt) {
        if (rt == NULL) return;
        if (rt->left != NULL) destroy(rt->left);
        if (rt->right != NULL) destroy(rt->right);
        delete rt;
    }

    node<T> *search(node<T> *rt, T key) {
        if (rt == NULL || rt->key == key) return rt;
        if (key < rt->key)
            return search(rt->left, key);
        else
            return search(rt->right, key);
    }

    node<T> *get_min(node<T> *rt) {
        if (rt == NULL) return NULL;
        while (rt->left != NULL)
            rt = rt->left;
        return rt;
    }

    node<T> *get_max(node<T> *rt) {
        if (rt == NULL) return NULL;
        while (rt->right != NULL)
            rt = rt->right;
        return rt;
    }

    node<T> *insert(node<T> *rt, T key) {
        if (rt == NULL)
            rt = new node<T>(key, NULL, NULL);
        else if (key < rt->key) {
            rt->left = insert(rt->left, key);
        } else {
            rt->right = insert(rt->right, key);
        }
        return rt;
    }

    node<T> *remove(node<T> *rt, node<T> *k) {
        if (rt == NULL || k == NULL) return NULL;
        if (k->key < rt->key) {
            rt->left = remove(rt->left, k);
        } else if (k->key > rt->key) {
            rt->right = remove(rt->right, k);
        } else {
            if (rt->left != NULL && rt->right != NULL) {
                node<T> *mx = get_max(rt->left);
                rt->key = mx->key;
                rt->left = remove(rt->left, mx);
            } else {
                node<T> *tmp = rt;
                rt = (rt->left != NULL) ? rt->left : rt->right;
                delete tmp;
            }
        }
        return rt;
    }

    node<T> *remove(node<T> *rt, T key) {
        return remove(rt, search(rt, key));
    }

};

int main() {
    freopen("test.txt", "r", stdin);
    // clock_t st = clock();
    int n;
    cin >> n;
    int a[N];
    BST<int> tree;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        tree.root = tree.insert(tree.root, a[i]);
    }
    clock_t st = clock();
    int x;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        tree.root = tree.remove(tree.root, x);
    }
    clock_t ed = clock();
    ofstream ofs;
    ofs.open("ans.txt", ios::out | ios::app);
    ofs << "bst " << (double) (ed - st) / CLOCKS_PER_SEC << endl;
    ofs.close();
    return 0;
}