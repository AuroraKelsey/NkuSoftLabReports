# [最长有效括号长度](http://10.134.1.2/nkuoj/#/problem/458690)

https://leetcode.cn/problems/longest-valid-parentheses/description/
很好理解
但`str[i-dp[i-1]-1]=='('`很难想到
```c
#include <iostream>  
#include <cstdio>  
#include <string>  
#include <sstream>  
#include <stack>  
  
using namespace std;  
const int N = 10005;  
  
int ans = 0;  
int dp[N];  
int main() {  
    string str;  
    getline(cin, str);  
  
    int maxs = 0;  
    for(int i=1;i<str.length();i++) {  
        if(str[i]=='(') dp[i]=0;  
        else {  
            if(str[i-1]=='(') dp[i]=(i>=2?dp[i-2]:0)+2;  
            else if(i - dp[i - 1] > 0 && str[i-dp[i-1]-1]=='(')  
                dp[i]=(i>=1?dp[i-1]:0)+2+ ((i - dp[i - 1]) >= 2 ? dp[i - dp[i - 1] - 2] : 0) ;  
        }  
        ans=max(ans,dp[i]);  
    }  
  
    printf("%d\n", ans);  
    return 0;  
}
```

# [最大子段和](http://10.134.1.2/nkuoj/#/problem/468826)
很简单的dp

```c
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <stack>

using namespace std;
const int N = 10005;

int dp[N][2];//0 不要
int a[N];
int main() {
    int n;
    scanf("%d",&n);
    int ans=-10000000;
    for(int i=1;i<=n;i++) {
        scanf("%d", &a[i]);
        ans = max(ans, a[i]);
    }

    for(int i=1;i<=n;i++) {
        dp[i][0]=0;
        dp[i][1]=max(dp[i-1][0],dp[i-1][1])+a[i];
        ans=max(ans,dp[i][1]);
    }
    printf("%d\n", ans);
    return 0;
}


```