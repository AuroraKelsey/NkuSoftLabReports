#include <bits/stdc++.h>

using namespace std;

inline int read() {
    int x = 0;
    char ch = getchar();
    while (!isdigit(ch))ch = getchar();
    while (isdigit(ch)) {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    return x;
}

int main() {
    //用于清空两个文件 
    ofstream ofs;
    ofs.open("KMP.txt", ios::out);
    ofs <<"";
    ofs.close();
    ofs.open("BM.txt", ios::out);
    ofs <<"";
    ofs.close();
    
    int n = 100;
    for (int i = 1; i <= n; i++) {
        system("build");
        system("KMP");
        system("BM");
    }

    freopen("KMP.txt", "r", stdin);
    double tim1 = 0, tim2 = 0, x;
    long long cnt1 = 0, cnt2 = 0;
    for (int i = 1; i <= n; i++) {
        scanf("%lf",&x);
        tim1 += x;
        cnt1 += read();
    }

    freopen("BM.txt", "r", stdin);
    for (int i = 1; i <= n; i++) {
        scanf("%lf",&x);
        tim2 += x;
        cnt2 += read();
    }
    ofs.open("conclusion.txt", ios::out|ios::app);
    ofs <<"";
    ofs << "KMP算法用时：" << tim1 << endl;
    ofs << "KMP算法平均比较次数：" << cnt1 / n << endl;
    ofs << "BM算法用时：" << tim2 << endl;
    ofs << "BM算法平均比较次数：" << cnt2 / n << endl;
    ofs << endl;
   	ofs.close();
   
    return 0;
}
