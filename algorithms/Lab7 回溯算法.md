# n皇后
```c fold
#include <iostream>  
  
using namespace std;  
int n;  
int ans;  
bool lie[20];  
bool g[20][20];  
  
//检查斜线  
bool check() {  
    //主对角  
    for (int i = 1; i <= n; i++) {  
        int x = 1, y = i, cnt = 0;  
        while (x <= n && y <= n) {  
            if (g[x][y]) cnt++;  
            x++;  
            y++;  
        }  
        if (cnt > 1) return false;  
    }  
    for (int i = 1; i <= n; i++) {  
        int x = i, y = 1, cnt = 0;  
        while (x <= n && y <= n) {  
            if (g[x][y]) cnt++;  
            x++;  
            y++;  
        }  
        if (cnt > 1) return false;  
    }  
    //副对角  
    for (int i = 1; i <= n; i++) {  
        int x = 1, y = i, cnt = 0;  
        while (x <= n && y >=1) {  
            if (g[x][y]) cnt++;  
            x++;  
            y--;  
        }  
        if (cnt > 1) return false;  
    }  
    for (int i = 1; i <= n; i++) {  
        int x = i, y = n, cnt = 0;  
        while (x <= n && y >=1) {  
            if (g[x][y]) cnt++;  
            x++;  
            y--;  
        }  
        if (cnt > 1) return false;  
    }  
    return true;  
}  
  
void dfs(int row, int cnt) {  
    if (row == n + 1) {  
        if (cnt == n && check()) {  
//            for(int i=1;i<=n;i++,cout<<endl)  
//                for(int j=1;j<=n;j++)  
//                    cout<<g[i][j];  
            ans++;  
        }  
        return;  
    }  
    for (int i = 1; i <= n; i++) {//枚举列  
        if (!lie[i]) {  
            g[row][i] = 1;  
            lie[i] = 1;  
            dfs(row + 1, cnt + 1);  
            lie[i] = 0;  
            g[row][i] = 0;  
        }  
    }  
}  
  
int main() {  
    cin >> n;  
    dfs(1,0);  
    cout << ans;  
    return 0;  
}
```

# 所有可能的路径
```c fold
#include <iostream>  
#include <string>  
#include <vector>  
  
using namespace std;  
const int N = 30;  
int n;  
bool g[N][N];  
  
void dfs(int x, vector<int> &v) {  
    if (x == n) {  
        cout<<"0 ";  
        for(auto x:v)  
            cout<<x-1<<" ";  
        cout<<endl;  
        return;  
    }  
    for(int i=1;i<=n;i++)  
        if(g[x][i]) {  
            v.emplace_back(i);  
            dfs(i,v);  
            v.pop_back();  
        }  
}  
  
int main() {  
    cin >> n;  
    char c;  
    c = getchar();  
    for (int i = 1; i <= n; i++) {  
        int x = 0;  
        while (1) {  
            c = getchar();  
            if (c == '\n') {  
                if (x != 0)  
                    g[i][x + 1] = 1;  
                break;  
            }  
            if (c == ' ') {  
                g[i][x + 1] = 1;  
                x = 0;  
            } else {  
                x = x * 10 + c - '0';  
            }  
        }  
    }  
    vector<int> v;  
    dfs(1, v);  
    return 0;  
}
```