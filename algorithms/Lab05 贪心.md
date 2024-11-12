# 用最少数量的箭引爆气球
```c
#include <iostream>
#include <algorithm>
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
    int mxR=-101,ans=0;
    for(int i=1;i<=n;i++) {
        if(a[i].st>mxR) {
            ans++;
            mxR=max(mxR,a[i].ed);
        }
    }
    printf("%d",ans);
    return 0;
}
```


# 最小延迟调度
```c
#include <iostream>
#include <algorithm>
using namespace std;
const int N=100000;
struct node{
    int t,d;
    bool operator < (const node &x) const{
        return d<x.d;
    }
}a[N];
int main() {
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%d %d",&a[i].t,&a[i].d);
    }
    sort(a+1,a+1+n);
    int ans=0;
    int tim=0;
    for(int i=1;i<=n;i++) {
        tim+=a[i].t;
        ans=max(tim-a[i].d,ans);
    }
    printf("%d",ans);
    return 0;
}
```