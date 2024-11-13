#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime>
#include <fstream>

using namespace std;
const int N = 400000;

struct RBNode {
    int key;  // 键值
    bool color;  // 颜色，true为红色，false为黑色
    RBNode *left;  // 左子节点指针
    RBNode *right;  // 右子节点指针
    RBNode *parent;  // 父节点指针

    // 构造函数
    RBNode(int k, bool c, RBNode *l, RBNode *r, RBNode *p)
            : key(k), color(c), left(l), right(r), parent(p) {}
};

class RBTree {
public:
    // 构造函数
    RBTree() : root(nullptr) {}

    // 插入节点
    void insert(int key) {
        RBNode *node = new RBNode(key, true, nullptr, nullptr, nullptr);
        root = insert_helper(root, node);
        fix_insert(node);
    }

    // 查找节点
    bool find(int key) {
        return find_helper(root, key);
    }

    // 删除节点
    void remove(int key) {
        RBNode *node = find_node(root, key);
        if (node != nullptr) {
            remove_helper(node);
        }
    }

private:
    RBNode *root;  // 根节点指针

    // 左旋
    void rotate_left(RBNode *node) {
        RBNode *right = node->right;
        node->right = right->left;
        if (right->left != nullptr) {
            right->left->parent = node;
        }
        right->parent = node->parent;
        if (node == root) {
            root = right;
        } else if (node == node->parent->left) {
            node->parent->left = right;
        } else {
            node->parent->right = right;
        }
        right->left = node;
        node->parent = right;
    }

    // 右旋
    void rotate_right(RBNode *node) {
        RBNode *left = node->left;
        node->left = left->right;
        if (left->right != nullptr) {
            left->right->parent = node;
        }
        left->parent = node->parent;
        if (node == root) {
            root = left;
        } else if (node == node->parent->left) {
            node->parent->left = left;
        } else {
            node->parent->right = left;
        }
        left->right = node;
        node->parent = left;
    }

    // 插入节点辅助函数
    RBNode *insert_helper(RBNode *root, RBNode *node) {
        if (root == nullptr) {
            return node;
        }
        if (node->key < root->key) {
            root->left = insert_helper(root->left, node);
            root->left->parent = root;
        } else if (node->key > root->key) {
            root->right = insert_helper(root->right, node);
            root->right->parent = root;
        }
        return root;
    }

    // 查找节点辅助函数
    bool find_helper(RBNode *root, int key) {
        if (root == nullptr) {
            return false;
        }
        if (root->key == key) {
            return true;
        } else if (root->key > key) {
            return find_helper(root->left, key);
        } else {
            return find_helper(root->right, key);
        }
    }

    // 查找节点
    RBNode *find_node(RBNode *root, int key) {
        while (root != nullptr) {
            if (root->key == key) {
                return root;
            } else if (root->key > key) {
                root = root->left;
            } else {
                root = root->right;
            }
        }
        return nullptr;
    }

    // 删除节点辅助函数
    void remove_helper(RBNode *node) {
        RBNode *child = nullptr;
        RBNode *parent = nullptr;
        bool color;

        if (node->left != nullptr && node->right != nullptr) {
            RBNode *replace = node->right;
            while (replace->left != nullptr) {
                replace = replace->left;
            }
            if (node->parent != nullptr) {
                if (node == node->parent->left) {
                    node->parent->left = replace;
                } else {
                    node->parent->right = replace;
                }
            } else {
                root = replace;
            }
            child = replace->right;
            parent = replace->parent;
            color = replace->color;
            if (parent == node) {
                parent = replace;
            } else {
                if (child != nullptr) {
                    child->parent = parent;
                }
                parent->left = child;
                replace->right = node->right;
                node->right->parent = replace;
            }
            replace->parent = node->parent;
            replace->color = node->color;
            replace->left = node->left;
            node->left->parent = replace;
            delete node;
            node = nullptr;
        } else {
            if (node->left != nullptr) {
                child = node->left;
            } else {
                child = node->right;
            }
            parent = node->parent;
            color = node->color;
            if (child != nullptr) {
                child->parent = parent;
            }
            if (parent != nullptr) {
                if (node == parent->left) {
                    parent->left = child;
                } else {
                    parent->right = child;
                }
            } else {
                root = child;
            }
            delete node;
            node = nullptr;
        }
        if (color == false) {
            fix_remove(child, parent);
        }
    }

    // 插入后修复红黑树
    void fix_insert(RBNode *node) {
        while (node != root && node->parent->color == true) {
            if (node->parent == node->parent->parent->left) {
                RBNode *uncle = node->parent->parent->right;
                if (uncle != nullptr && uncle->color == true) {
                    node->parent->color = false;
                    uncle->color = false;
                    node->parent->parent->color = true;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotate_left(node);
                    }
                    node->parent->color = false;
                    node->parent->parent->color = true;
                    rotate_right(node->parent->parent);
                }
            } else {
                RBNode *uncle = node->parent->parent->left;
                if (uncle != nullptr && uncle->color == true) {
                    node->parent->color = false;
                    uncle->color = false;
                    node->parent->parent->color = true;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotate_right(node);
                    }
                    node->parent->color = false;
                    node->parent->parent->color = true;
                    rotate_left(node->parent->parent);
                }
            }
        }
        root->color = false;
    }

    // 删除后修复红黑树
    void fix_remove(RBNode *node, RBNode *parent) {
        RBNode *other;
        while ((node == nullptr || node->color == false) && node != root) {
            if (parent->left == node) {
                other = parent->right;
                if (other->color == true) {
                    other->color = false;
                    parent->color = true;
                    rotate_left(parent);
                    other = parent->right;
                }
                if ((other->left == nullptr || other->left->color == false) &&
                    (other->right == nullptr || other->right->color == false)) {
                    other->color = true;
                    node = parent;
                    parent = node->parent;
                } else {
                    if (other->right == nullptr || other->right->color == false) {
                        if (other->left != nullptr) {
                            other->left->color = false;
                        }
                        other->color = true;
                        rotate_right(other);
                        other = parent->right;
                    }
                    other->color = parent->color;
                    parent->color = false;
                    if (other->right != nullptr) {
                        other->right->color = false;
                    }
                    rotate_left(parent);
                    node = root;
                    break;
                }
            } else {
                other = parent->left;
                if (other->color == true) {
                    other->color = false;
                    parent->color = true;
                    rotate_right(parent);
                    other = parent->left;
                }
                if ((other->left == nullptr || other->left->color == false) &&
                    (other->right == nullptr || other->right->color == false)) {
                    other->color = true;
                    node = parent;
                    parent = node->parent;
                } else {
                    if (other->left == nullptr || other->left->color == false) {
                        if (other->right != nullptr) {
                            other->right->color = false;
                        }
                        other->color = true;
                        rotate_left(other);
                        other = parent->left;
                    }
                    other->color = parent->color;
                    parent->color = false;
                    if (other->left != nullptr) {
                        other->left->color = false;
                    }
                    rotate_right(parent);
                    node = root;
                    break;
                }
            }
        }
        if (node != nullptr) {
            node->color = false;
        }
    }
};

int main() {
    // clock_t st = clock();
    freopen("test.txt", "r", stdin);
    RBTree rbtree;
    int n;
    cin >> n;
    // 插入
    int a[N];
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        rbtree.insert(a[i]);
    }
    clock_t st = clock();
    int x;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        rbtree.remove(x);
    }
    // for (int i = n; i>0; i--) 
    //     rbtree.remove(a[i]);
    clock_t ed = clock();
    ofstream ofs;
    ofs.open("ans.txt", ios::out | ios::app);
    ofs << "RBtree " << (double) (ed - st) / CLOCKS_PER_SEC << endl;
    ofs << endl;
    ofs.close();
    // 随机查找几个数字
    // int x;
    // for (int i = 1; i <= 2; i++) {
    //     cin >> x;
    //     if(rbtree.find(x)) cout<<"找到"<<x<<endl;
    //     else cout<<"找不到"<<x<<endl;
    // }

    // 按顺序删除这些数字

    // for (int i = 1; i <= n; i++){
    //     rbtree.remove(a[i]);

    // }

    return 0;
}
