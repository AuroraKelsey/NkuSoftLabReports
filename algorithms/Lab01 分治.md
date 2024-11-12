## 二分
```c fold
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> a;
int main() {
    while(1) {
        int x = 0;
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
        a.emplace_back(f?-x:x);
        if(ch=='\n') break;
    } 
    int target;
    scanf("%d",&target);
    int n=a.size();
    int l=0,r=n-1;
    int ans=-1;
    while(l<=r) {
        int mid=(l+r)>>1;
        if(a[mid]==target) {
            ans=mid;
            break;
        }
        else if(a[mid]<target) 
            l=mid+1;
        else r=mid-1;
    }
    printf("%d",ans);
    return 0;
}
```
## 找到数组中第k小的数
类似快排的思想

首先随便指定一个数star（第一个），将数组中其他的数与star进行比较，比star小的放在左边，大的放在右边，如果randK左边的元素个数为k-1个，说明findK就是你所要找的元素，如果左边的元素个数>k-1，说明你要找的元素在左边的数中，继续使用相同的方法在左边的数中进行查找，如果左边的元素的个数<k-1,说明你要找的元素在右边的数中，则继续使用相同的办法在右边的数中进行查找
复杂度$O(nlogn)$，只有80分
```c fold
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

vector<int> a;
int solve(vector<int>&v,int k) {
    vector<int>L;
    vector<int>R;
    int star=v[0];
    int cnt=0;
    for(int i=0;i<v.size();i++) {
        if(star>v[i]) L.emplace_back(v[i]);
        else if(star<v[i]) R.emplace_back(v[i]);
        else if(star==v[i]) cnt++;
    }
    if(k>L.size()&&L.size()+cnt>=k) return star;
    else if(L.size()<k-1) return solve(R,k-L.size()-1);
    else return solve(L,k);
}
int main() {
    while(1) {
        int x = 0;
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
        a.emplace_back(f?-x:x);
        if(ch=='\n') break;
    } 
    int k;
    scanf("%d",&k);
    int n=a.size();
    printf("%d",solve(a,k));
    return 0;
}
```

正解
![[assets/20240419160445.png]]![[assets/20240419160455.png]]
![[assets/20240419160505.png]]

注意要用stringstream读入，否则超时 
```c
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
vector<int> v;

inline int solve(vector<int> &ve, int k) {
    sort(ve.begin(), ve.end());
    return ve[k];
}

map<int, int> mp;
void select(vector<int> &v, int k) {
    int n = v.size();
    vector<vector<int>> a(n / 5 + 2, vector<int>());
    for (int i = 0; i < n; i++) {
        a[i / 5].emplace_back(v[i]);
    }
    vector<int> M;
    int len = ceil((double) n / 5);
    for (int i = 0; i < len; i++) {
        if (a[i].size() == 0) continue;
        int val = solve(a[i], a[i].size() / 2);
        M.emplace_back(val);
        mp[val]=i;
    }
    vector<int> tmp(M);
    int m_star = solve(tmp, tmp.size() / 2);

    //划分为四个集合
    vector<int> A, B, C, D;
    for (int i = 0; i < M.size(); i++) {
        len = a[i].size();
        if (M[i] < m_star) {

            for (int j = 0; j < len; j++) {
                if (j <= len / 2) C.emplace_back(a[i][j]);
                else if (j > len / 2)
                    A.emplace_back(a[i][j]);
            }
        } else if (M[i] >= m_star && i != mp[m_star]) {
            for (int j = 0; j < len; j++) {
                if (j < len / 2) D.emplace_back(a[i][j]);
                else if (j >= len / 2)
                    B.emplace_back(a[i][j]);
            }
        } else {
            for (int j = 0; j < len; j++) {
                if (j < len / 2) C.emplace_back(a[i][j]);
                else if (j > len / 2)
                    B.emplace_back(a[i][j]);
            }
        }
    }
    for (auto x: A) {
        if (x < m_star) C.emplace_back(x);
        if (x >= m_star) B.emplace_back(x);
    }
    for (auto x: D) {
        if (x < m_star) C.emplace_back(x);
        if (x >= m_star) B.emplace_back(x);
    }
    if (k == C.size() + 1) {
        printf("%d", m_star);
        return;
    } else if (k <= C.size()) {
        select(C, k);
    } else {
        select(B, k - C.size() - 1);
    }
}
int main() {
    string line;
    getline(cin, line);
    stringstream ss1(line);
    int num;
    while (ss1 >> num) {
        v.emplace_back(num);
        if (ss1.peek() == '\n' || ss1.peek() == '\r') {
            break;
        }
        ss1.ignore();  // 跳过空格
    }
    int k;
    scanf("%d", &k);
    select(v, k);
    return 0;
}
/*
2 4 6 10 12 15 1 5 9 13 14 16 17 11 7 3 8
3

2 2 5 1 1 4 3 6 3
2
*/

```

