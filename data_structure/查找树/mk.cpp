#include <iostream>
#include <vector>
#include <random>
#include <fstream>

using namespace std;

int main() {
    freopen("in.txt", "r", stdin);
    int n;
    cin >> n;
    freopen("test.txt", "w", stdout);
    // 创建包含1到n的序列
    vector<int> sequence(n);
    for (int i = 0; i < n; ++i)
        sequence[i] = i + 1;
    cout << n << endl;
    //要插入的数
    random_device rd;
    mt19937 gen(rd());
    shuffle(sequence.begin(), sequence.end(), gen);
    for (int i = 0; i < n - 1; i++)
        cout << sequence[i] << " ";
    cout << sequence[n - 1] << endl;

    //随机测试1000个
    // int x;
    // for(int i=1;i<=1000;i++) {
    //     x=rand()%n+1;
    //     cout<<x<<" ";
    // }
    //删除
    random_device rd1;
    mt19937 gen1(rd1());
    shuffle(sequence.begin(), sequence.end(), gen1);
    for (int i = 0; i < n - 1; i++)
        cout << sequence[i] << " ";
    cout << sequence[n - 1] << endl;
    ofstream ofs;
    ofs.open("ans.txt", ios::out | ios::app);
    ofs << "n " << n << endl;
    ofs.close();

    return 0;
}
