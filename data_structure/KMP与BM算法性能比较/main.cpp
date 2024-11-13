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
    //������������ļ� 
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
    ofs << "KMP�㷨��ʱ��" << tim1 << endl;
    ofs << "KMP�㷨ƽ���Ƚϴ�����" << cnt1 / n << endl;
    ofs << "BM�㷨��ʱ��" << tim2 << endl;
    ofs << "BM�㷨ƽ���Ƚϴ�����" << cnt2 / n << endl;
    ofs << endl;
   	ofs.close();
   
    return 0;
}
