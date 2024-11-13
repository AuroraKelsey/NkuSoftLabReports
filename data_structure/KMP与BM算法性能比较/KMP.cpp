#include <iostream>
#include <ctime>
#include <fstream>

#define N 1000005

using namespace std;
int Next[N];

void getnext(string p) {
    int i, j = 0;
    Next[0] = 0;
    for (i = 1; i < p.length(); i++) {
        while (p[i] != p[j] && j > 0)
            j = Next[j - 1];
        if (p[i] == p[j])
            Next[i] = ++j;
    }
}

int kmp(string t, string p) {
    getnext(p);
    int count = 0; // 字符比较次数
    for (int i = 0, j = 0; i < t.length(); i++) {
        while (t[i] != p[j] && j > 0) {
            j = Next[j - 1];
            count++; 
        }
        if (t[i] == p[j]) {
            j++;
            count++; 
        }
        if (j == p.length()) {
            return count;
        }
    }
    return count;
}

int main() {
    freopen("test.txt", "r", stdin);
    double st = clock();
    string pattern, s;
    cin >> s;
    cin >> pattern;
    int cnt = kmp(s, pattern);
    
    double ed = clock();
    ofstream ofs;
    ofs.open("KMP.txt", ios::out | ios::app);
    ofs << (ed - st) / CLOCKS_PER_SEC << endl;
    ofs << cnt << endl;
    ofs.close();
    return 0;
}
