# 最长公共子序列
```c
#include <iostream>
#include <cstdio>
#include <string>

using namespace std;
const int N = 3e3 + 5;


int f[N][N];
//str1到i，str2到j的最长公共子序列
int main() {
    string str1, str2;
    getline(cin, str1);
    getline(cin, str2);
    int n = str1.length(), m = str2.length();
    str1=" "+str1;
    str2=" "+str2;


    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if (str1[i] == str2[j]) {
                f[i][j]=f[i-1][j-1]+1;
            } else {
                f[i][j]=max(f[i][j-1],f[i-1][j]);
            }
        }
    printf("%d",f[n][m]);

    return 0;
}


```

