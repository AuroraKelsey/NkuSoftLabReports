[构建最大二叉树](http://10.134.1.2/nkuoj/#/problem/484100)

```c fold
#include <cstdio>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
int getmax(vector<int> &ve) {
    int x = 0;
    for (int i = 1; i < ve.size(); i++)
        if (ve[i] > ve[x])
            x = i;
    return x;
}
TreeNode *solve(vector<int> &nums) {
    if (nums.empty()) return nullptr;
    int id = getmax(nums);
    TreeNode *root = new TreeNode(nums[id]);
    vector<int> numsl(nums.begin(), nums.begin() + id);
    vector<int> numsr(nums.begin() + id + 1, nums.end());
    root->left = solve(numsl);
    root->right = solve(numsr);
    numsl.clear();
    numsr.clear();
    return root;
}
vector<int> ans;
void traversal(TreeNode *p) {
    queue<TreeNode *> q;
    q.push(p);
    while (!q.empty()) {
        TreeNode *x = q.front();
        q.pop();
        if (x == nullptr) continue;
        ans.emplace_back(x->val);
        if (x->left)
            q.push(x->left);
        if (x->right)
            q.push(x->right);
    }
}
int main() {
    string line;
    getline(cin, line);
    stringstream ss1(line);
    int num;
    vector<int> a;
    while (ss1 >> num) {
        a.emplace_back(num);
    }   
    traversal(solve(a));
    for (int i = 0; i < ans.size() - 1; i++)
        printf("%d ", ans[i]);
    printf("%d", ans.back());
    return 0;
}

```
[逆序交易对](http://10.134.1.2/nkuoj/#/problem/483274)

```c fold
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
const int N = 1e5 + 5;//这里不能开太大，否则会显示运行错误

template<typename T>
inline T read() {
    T x = 0;
    bool f = 0;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') f = 1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return f ? -x : x;
}
int n, a[N];
int tmp[N];
int ans;
void merge(int l, int r) {
    int mid = (l + r) >> 1;
    if (l == r) return;
    merge(l, mid);
    merge(mid + 1, r);
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r) {
        if (a[i] > a[j]) {
            tmp[k++] = a[j++];
            ans += mid - i + 1;
        } else
            tmp[k++] = a[i++];
    }
    while (i <= mid) tmp[k++] = a[i++];
    while (j <= r) tmp[k++] = a[j++];
    for (int k = l; k <= r; k++)
        a[k] = tmp[k];
}
int main() {
    n = read<int>();
    for (int i = 1; i <= n; i++)
        a[i] = read<int>();
    merge(1, n);
    printf("%d", ans);
    return 0;
}
```