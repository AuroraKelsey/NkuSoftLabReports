#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

// 随机生成字符串
string generateRandomString(int length, char start, char end) {
    string s = "";
    srand(time(0));
    for (int i = 0; i < length; ++i) {
        char c = start + rand() % (end - start + 1);
        s += c;
    }
    return s;
}

int main() {
    int mainStringLength = 1000;
    int patternLength = 10;
    int patternPosition = 3;
    int patternType = 3;
//    freopen("in.txt", "r", stdin);
//  	cout << "请输入主串长度：";
//    cin >> mainStringLength;
//  	cout << "请输入模式串长度：";
//    cin >> patternLength;
// 	cout << "请输入模式串在主串中的位置 (1-前，2-中，3-后)：";
//    cin >> patternPosition;
//    cout << "请输入模式串类型 (1-数字，2-字母，3-ASCII 32-126)：";
//    cin >> patternType;


    // 随机生成模式串
    string pattern;
    switch (patternPosition) {
        case 1:
            pattern = generateRandomString(patternLength, '0', '9');
            break;
        case 2:
            pattern = generateRandomString(patternLength, 'a', 'z');
            break;
        case 3:
            pattern = generateRandomString(patternLength, 33, 126);
            break;
    }
    // 确定模式串在主串中的位置
    int before = mainStringLength / 3;
    int pos;
    string half1, half2;//主串前半部分和后半部分 
    switch (patternPosition) {
        case 1:
            pos = rand() % before;
            break;
        case 2:
            pos = rand() % before + before;
            break;
        case 3:
            pos = rand() % before + before * 2;
            break;
    }
    freopen("test.txt", "w", stdout);
    half1 = generateRandomString(pos - 1, 48, 122);
    half2 = generateRandomString(mainStringLength - patternLength - pos + 1, 48, 122);
    //主串
    cout << half1 << pattern << half2 << endl;
    //模式串
    cout << pattern << endl;
    return 0;
}
