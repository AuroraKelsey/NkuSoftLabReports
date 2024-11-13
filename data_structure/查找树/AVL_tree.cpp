#include <iostream>
#include <queue>
#include <ctime>
#include <fstream>

using namespace std;
const int N = 400000;

template<class T>
class AVLnode {
public:
    T key;
    int height;
    AVLnode *left;
    AVLnode *right;

    AVLnode(T value, AVLnode *l, AVLnode *r) : key(value), height(0), left(l), right(r) {}
};

template<class T>
class BST {
public:
    AVLnode<T> *root;

    BST() : root(NULL) {}

    ~BST() {
        destroy(root);
    }

    void destroy(AVLnode<T> *rt) {
        if (rt == NULL) return;
        if (rt->left != NULL) destroy(rt->left);
        if (rt->right != NULL) destroy(rt->right);
        delete rt;
    }

    int get_height(AVLnode<T> *rt) {
        if (rt != NULL) return rt->height;
        return 0;
    }

    AVLnode<T> *search(AVLnode<T> *rt, T key) {
        if (rt == NULL || rt->key == key) return rt;
        if (key < rt->key)
            return search(rt->left, key);
        else
            return search(rt->right, key);
    }

    AVLnode<T> *get_min(AVLnode<T> *rt) {
        if (rt == NULL) return NULL;
        while (rt->left != NULL)
            rt = rt->left;
        return rt;
    }

    AVLnode<T> *get_max(AVLnode<T> *rt) {
        if (rt == NULL) return NULL;
        while (rt->right != NULL)
            rt = rt->right;
        return rt;
    }

    AVLnode<T> *RightRotate(AVLnode<T> *rt) {
        if (rt == NULL || rt->left == NULL)
            return rt;
        AVLnode<T> *k = rt->left;
        if (k->right == NULL)
            return rt;
        rt->left = k->right;
        k->right = rt;
        rt->height = max(get_height(rt->left), get_height(rt->right)) + 1;
        k->height = max(get_height(k->left), get_height(k->right)) + 1;
        return k;
    }

    AVLnode<T> *LeftRotate(AVLnode<T> *rt) {
        if (rt == NULL || rt->right == NULL)
            return rt;
        AVLnode<T> *k = rt->right;
        if (k->left == NULL)
            return rt;
        rt->right = k->left;
        k->left = rt;
        rt->height = max(get_height(rt->left), get_height(rt->right)) + 1;
        k->height = max(get_height(k->left), get_height(k->right)) + 1;
        return k;
    }

    AVLnode<T> *LLrotate(AVLnode<T> *rt) {
        return RightRotate(rt);
    }

    AVLnode<T> *LRrotate(AVLnode<T> *rt) {
        rt->left = LeftRotate(rt->left);
        return RightRotate(rt);
    }

    AVLnode<T> *RLrotate(AVLnode<T> *rt) {
        rt->right = RightRotate(rt->right);
        return LeftRotate(rt);
    }

    AVLnode<T> *RRrotate(AVLnode<T> *rt) {
        return LeftRotate(rt);
    }

    AVLnode<T> *insert(AVLnode<T> *rt, T key) {
        if (rt == NULL)
            rt = new AVLnode<T>(key, NULL, NULL);
        else if (key < rt->key) {
            rt->left = insert(rt->left, key);
            if (get_height(rt->left) - get_height(rt->right) > 1) {
                if (key < rt->left->key) //LL  
                    rt = LLrotate(rt);
                else
                    rt = LRrotate(rt);
            }
        } else {
            rt->right = insert(rt->right, key);
            if (get_height(rt->right) - get_height(rt->left) > 1) {
                if (key < rt->right->key)
                    rt = RLrotate(rt);
                else
                    rt = RRrotate(rt);
            }
        }
        rt->height = max(get_height(rt->left), get_height(rt->right)) + 1;
        return rt;
    }

    AVLnode<T> *remove(AVLnode<T> *rt, AVLnode<T> *k) {
        if (rt == NULL || k == NULL) return NULL;
        if (k->key < rt->key) {
            rt->left = remove(rt->left, k);
            if (get_height(rt->right) - get_height(rt->left) > 1) {
                AVLnode<T> *r = rt->right;
                if (get_height(r->left) > get_height(r->right))
                    rt = RLrotate(rt);
                else
                    rt = RRrotate(rt);
            }
        } else if (k->key > rt->key) {
            rt->right = remove(rt->right, k);
            if (get_height(rt->left) - get_height(rt->right) > 1) {
                AVLnode<T> *r = rt->left;
                if (get_height(r->left) > get_height(r->right))
                    rt = LLrotate(rt);
                else
                    rt = LRrotate(rt);
            }
        } else {
            if (rt->left != NULL && rt->right != NULL) {
                if (get_height(rt->left) > get_height(rt->right)) {
                    AVLnode<T> *mx = get_max(rt->left);
                    rt->key = mx->key;
                    rt->left = remove(rt->left, mx);
                } else {
                    AVLnode<T> *mi = get_min(rt->right);
                    rt->key = mi->key;
                    rt->right = remove(rt->right, mi);
                }
            } else {
                AVLnode<T> *tmp = rt;
                rt = (rt->left != NULL) ? rt->left : rt->right;
                delete tmp;
            }
        }
        return rt;
    }

    AVLnode<T> *remove(AVLnode<T> *rt, T key) {
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
    ofs << "AVL " << (double) (ed - st) / CLOCKS_PER_SEC << endl;
    ofs.close();
    /*
    int x;
    for (int i = 1; i <= 1000; i++) {
        cin >> x;
        tree.search(tree.root,x);
    }
    */

    return 0;
}