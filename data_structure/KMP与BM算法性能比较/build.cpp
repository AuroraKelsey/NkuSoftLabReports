#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

// ��������ַ���
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
//  	cout << "�������������ȣ�";
//    cin >> mainStringLength;
//  	cout << "������ģʽ�����ȣ�";
//    cin >> patternLength;
// 	cout << "������ģʽ���������е�λ�� (1-ǰ��2-�У�3-��)��";
//    cin >> patternPosition;
//    cout << "������ģʽ������ (1-���֣�2-��ĸ��3-ASCII 32-126)��";
//    cin >> patternType;


    // �������ģʽ��
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
    // ȷ��ģʽ���������е�λ��
    int before = mainStringLength / 3;
    int pos;
    string half1, half2;//����ǰ�벿�ֺͺ�벿�� 
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
    //����
    cout << half1 << pattern << half2 << endl;
    //ģʽ��
    cout << pattern << endl;
    return 0;
}
