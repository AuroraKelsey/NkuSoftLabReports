#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;
const int MAX_KEYS = 512; // 每个节点最多存储的键值对数目
const int N = 400000;

struct BTreeNode {
    int numKeys; // 当前节点中的键值对数目
    int keys[MAX_KEYS]; // 键值数组
    BTreeNode *children[MAX_KEYS + 1]; // 子节点指针数组
    bool leaf; // 是否为叶子节点

    // 构造函数
    BTreeNode(bool isLeaf) {
        numKeys = 0;
        leaf = isLeaf;
        for (int i = 0; i < MAX_KEYS + 1; i++) {
            children[i] = nullptr;
        }
    }
};

void splitChild(BTreeNode *parent, int index, BTreeNode *child) {
    BTreeNode *newNode = new BTreeNode(child->leaf);
    newNode->numKeys = MAX_KEYS / 2;

    for (int i = 0; i < MAX_KEYS / 2; i++) {
        newNode->keys[i] = child->keys[i + MAX_KEYS / 2];
    }

    if (!child->leaf) {
        for (int i = 0; i < MAX_KEYS / 2 + 1; i++) {
            newNode->children[i] = child->children[i + MAX_KEYS / 2];
        }
    }

    child->numKeys = MAX_KEYS / 2;

    for (int i = parent->numKeys; i > index; i--) {
        parent->children[i + 1] = parent->children[i];
    }

    parent->children[index + 1] = newNode;

    for (int i = parent->numKeys - 1; i >= index; i--) {
        parent->keys[i + 1] = parent->keys[i];
    }

    parent->keys[index] = child->keys[MAX_KEYS / 2];
    parent->numKeys++;
}

void insertNonFull(BTreeNode *node, int key) {
    int i = node->numKeys - 1;
    if (node->leaf) {
        while (i >= 0 && key < node->keys[i]) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }
        node->keys[i + 1] = key;
        node->numKeys++;
    } else {
        while (i >= 0 && key < node->keys[i]) {
            i--;
        }
        i++;
        if (node->children[i]->numKeys == MAX_KEYS) {
            splitChild(node, i, node->children[i]);
            if (key > node->keys[i]) {
                i++;
            }
        }
        insertNonFull(node->children[i], key);
    }
}

void insert(BTreeNode *&root, int key) {
    if (root == nullptr) {
        root = new BTreeNode(true);
        root->keys[0] = key;
        root->numKeys = 1;
    } else {
        if (root->numKeys == MAX_KEYS) {
            BTreeNode *newRoot = new BTreeNode(false);
            newRoot->children[0] = root;
            splitChild(newRoot, 0, root);
            insertNonFull(newRoot, key);
            root = newRoot;
        } else {
            insertNonFull(root, key);
        }
    }
}

bool search(BTreeNode *node, int key) {
    if (node == nullptr) {
        return false;
    } else {
        int i = 0;
        while (i < node->numKeys && key > node->keys[i]) {
            i++;
        }
        if (i < node->numKeys && key == node->keys[i]) {
            return true;
        } else if (node->leaf) {
            return false;
        } else {
            return search(node->children[i], key);
        }
    }
}

int getPredecessor(BTreeNode *node) {
    while (!node->leaf) {
        node = node->children[node->numKeys];
    }
    return node->keys[node->numKeys - 1];
}

int getSuccessor(BTreeNode *node) {
    while (!node->leaf) {
        node = node->children[0];
    }
    return node->keys[0];
}

void borrowFromLeft(BTreeNode *parent, int index, BTreeNode *child, BTreeNode *leftSibling) {
    for (int i = child->numKeys; i > 0; i--) {
        child->keys[i] = child->keys[i - 1];
    }
    if (!child->leaf) {
        for (int i = child->numKeys + 1; i > 0; i--) {
            child->children[i] = child->children[i - 1];
        }
    }
    child->keys[0] = parent->keys[index - 1];
    parent->keys[index - 1] = leftSibling->keys[leftSibling->numKeys - 1];
    if (!leftSibling->leaf) {
        child->children[0] = leftSibling->children[leftSibling->numKeys];
    }
    child->numKeys++;
    leftSibling->numKeys--;
}

void borrowFromRight(BTreeNode *parent, int index, BTreeNode *child, BTreeNode *rightSibling) {
    child->keys[child->numKeys] = parent->keys[index];
    parent->keys[index] = rightSibling->keys[0];
    if (!rightSibling->leaf) {
        child->children[child->numKeys + 1] = rightSibling->children[0];
    }
    for (int i = 0; i < rightSibling->numKeys - 1; i++) {
        rightSibling->keys[i] = rightSibling->keys[i + 1];
    }
    if (!rightSibling->leaf) {
        for (int i = 0; i < rightSibling->numKeys; i++) {
            rightSibling->children[i] = rightSibling->children[i + 1];
        }
    }
    child->numKeys++;
    rightSibling->numKeys--;
}

void mergeChildren(BTreeNode *parent, int index, BTreeNode *leftChild, BTreeNode *rightChild) {
    leftChild->keys[leftChild->numKeys] = parent->keys[index];
    for (int i = 0; i < rightChild->numKeys; i++) {
        leftChild->keys[leftChild->numKeys + 1 + i] = rightChild->keys[i];
    }
    if (!leftChild->leaf) {
        for (int i = 0; i <= rightChild->numKeys; i++) {
            leftChild->children[leftChild->numKeys + 1 + i] = rightChild->children[i];
        }
    }
    leftChild->numKeys += rightChild->numKeys + 1;
    delete rightChild;
    for (int i = index; i < parent->numKeys - 1; i++) {
        parent->keys[i] = parent->keys[i + 1];
    }
    for (int i = index + 1; i < parent->numKeys; i++) {
        parent->children[i] = parent->children[i + 1];
    }
    parent->numKeys--;
}

void remove(BTreeNode *&root, int key) {
    if (root == nullptr) {
        return;
    }

    root->numKeys--;
    int i = 0;
    while (i < root->numKeys && key > root->keys[i]) {
        i++;
    }

    if (root->leaf) {
        if (root->keys[i] == key) {
            for (int j = i; j < root->numKeys; j++) {
                root->keys[j] = root->keys[j + 1];
            }
            return;
        }
    } else {
        if (i < root->numKeys && key == root->keys[i]) {
            BTreeNode *leftChild = root->children[i];
            BTreeNode *rightChild = root->children[i + 1];
            if (leftChild->numKeys >= MAX_KEYS / 2 + 1) {
                int predecessor = getPredecessor(leftChild);
                root->keys[i] = predecessor;
                remove(leftChild, predecessor);
            } else if (rightChild->numKeys >= MAX_KEYS / 2 + 1) {
                int successor = getSuccessor(rightChild);
                root->keys[i] = successor;
                remove(rightChild, successor);
            } else {
                mergeChildren(root, i, leftChild, rightChild);
                remove(leftChild, key);
            }
        } else {
            BTreeNode *child = root->children[i];
            if (child->numKeys == MAX_KEYS / 2) {
                BTreeNode *leftSibling = nullptr;
                BTreeNode *rightSibling = nullptr;
                int leftIndex = i - 1;
                int rightIndex = i + 1;
                if (leftIndex >= 0) {
                    leftSibling = root->children[leftIndex];
                }
                if (rightIndex <= root->numKeys) {
                    rightSibling = root->children[rightIndex];
                }
                if (leftSibling && leftSibling->numKeys >= MAX_KEYS / 2 + 1) {
                    borrowFromLeft(root, i, child, leftSibling);
                } else if (rightSibling && rightSibling->numKeys >= MAX_KEYS / 2 + 1) {
                    borrowFromRight(root, i, child, rightSibling);
                } else if (leftSibling) {
                    mergeChildren(root, leftIndex, leftSibling, child);
                    child = leftSibling;
                } else if (rightSibling) {
                    mergeChildren(root, i, child, rightSibling);
                }
            }
            remove(child, key);
        }
    }
}


int main() {
    // clock_t st = clock();
    freopen("test.txt", "r", stdin);
    BTreeNode *root = new BTreeNode(true);
    int n;
    cin >> n;
    int a[N];
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        insert(root, a[i]);
    }
    clock_t st = clock();
    int x;
    for (int i = 1; i <= n; i++) {
        cin >> x;
        remove(root, x);
    }
    // clock_t st = clock();
    // for(int i=n;i>0;i--)
    // remove(root,a[i]);
    clock_t ed = clock();
    ofstream ofs;
    ofs.open("ans.txt", ios::out | ios::app);
    ofs << "Btree " << (double) (ed - st) / CLOCKS_PER_SEC << endl;
    ofs.close();
    /*
    int x;
    for (int i = 1; i <= 1000; i++) {
        cin >> x;
        search(root,x);
    }
    //删除
    remove(root, x);
*/
    return 0;
}