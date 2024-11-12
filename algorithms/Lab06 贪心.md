# 外卖员送货
dij最短路
注意是单向边！
```c fold
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>
#include <vector>

using namespace std;
#define LL long long
const int N = 1e5;

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
int hd[N], nxt[N], to[N], w[N];
int cnt;
void add(int x, int y, int z) {
    to[++cnt] = y;
    w[cnt] = z;
    nxt[cnt] = hd[x];
    hd[x] = cnt;
}
struct node {
    int d, u;
    node(int u_, int d_) : u(u_), d(d_) {}
    bool operator<(const node &x) const {
        return d > x.d;
    }
};
bool vis[N];
int d[N];
void dij() {
    priority_queue<node> q;
    q.push(node(1, 0));
    memset(d,127,sizeof(d));
    d[1] = 0;
    while (!q.empty()) {
        int x = q.top().u;
        q.pop();
        if (vis[x]) continue;
        vis[x] = 1;
        for (int i = hd[x]; i; i = nxt[i]) {
            if (d[to[i]] > d[x] + w[i]) {
                d[to[i]] = d[x] + w[i];
                if(!vis[to[i]])
                    q.push(node(to[i],d[to[i]]));
            }
        }
    }
}
int main() {
    int n = read<int>();
    int m = read<int>();
    for (int i = 1; i <= m; i++) {
        int x, y, z;
        x = read<int>()+1;
        y = read<int>()+1;
        z = read<int>();
        add(x, y, z);
        // add(y, x, z);
    }
    dij();
    int ans=0;
    for(int i=2;i<=n;i++) {
        // cout<<d[i]<<" ";
        ans+=d[i];
    }
    cout<<ans;
    return 0;
}
```

# 会议室预定
vector记录会议室，会议室按照结束时间从小到大排序，
会议按照开始时间从小到大排
贪心：新会议先排到结束时间早的会议室中
```c fold
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
const int N=100000;
struct node{
    int st,ed;
    bool operator < (const node &x) const{
        return st<x.st;
    }
}a[N];
int main() {
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%d %d",&a[i].st,&a[i].ed);
    }
    sort(a+1,a+1+n);
    vector<int>ve;
    for(int i=1;i<=n;i++) {
        if(ve.empty()) {
            ve.emplace_back(a[i].ed);
        }else {
            bool flag=false;
            for(int j=0;j<ve.size();j++) {
                if(a[i].st>=ve[j]) {//能开
                    flag=true;
                    ve[j]=a[i].ed;
                    break;
                }
            }
            if(!flag) {
                ve.emplace_back(a[i].ed);
            }
        }
        sort(ve.begin(),ve.end());
    }
    printf("%lu",ve.size());
    return 0;
}
```