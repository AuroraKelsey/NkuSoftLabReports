#include <iostream>  
#include <string>  
#include <vector>  
#include <ctime>
#include <fstream>
using namespace std;  
  
bool isPrefix(const string &pattern, int pos) {  
    unsigned int plen = pattern.length();  
    for (int i = pos, j = 0; i < plen; i++, j++) {  
        if (pattern[i] != pattern[j]) {  
            return false;  
        }  
    }  
    return true;  
}  
//�ú�׺ƥ��  
int suffixLength(const string &pattern, int pos) {  
    int pLen = pattern.length();  
    int len = 0;  
    for (int i = pos, j = pLen - 1; i >= 0 && pattern[i] == pattern[j]; i--, j--) {  
        len += 1;  
    }  
    return len;  
}  
  
int fun(const string &pattern, const string &target) {  
    int tLen = target.length();  
    int pLen = pattern.length();  
    if (pLen > tLen) {  
        return -1;  
    }  
    vector<int> bad_table(256, pLen);// ��¼���ַ�����ʱ��Ӧ���������ַ�����256���ַ����ַ���  
    vector<int> good_table(pLen, 0);// ��úú�׺��ֵ������  
    for (int i = 0; i < pLen - 1; i++)  
        bad_table[pattern[i]] = pLen - 1 - i;  

    int lastPrefixPosition = pLen;//�ҵ���λ�ú�����ܺ�ģʽ����ǰ׺�Ӵ�ƥ��ĺ�׺�Ӵ�,�Ҳ�����Ĭ��Ϊplen  
    for (int i = pLen - 1; i >= 0; i--) {  
        if (isPrefix(pattern, i + 1)) {  
            lastPrefixPosition = i + 1;  
        }  
        good_table[pLen - 1 - i] = lastPrefixPosition - i + pLen - 1;//pLen-1-i��0~plen-1  
    }  
    //��������ȣ�i������ָ��,jģʽ��ָ��  
    int comparisonCount = 0; // �ַ��Ƚϴ���������
    for(int i=0;i<pLen;i++)
		printf("%d ",good_table[i]);
    for (int i = pLen - 1, j; i < tLen;) {  
        for (j = pLen - 1; target[i] == pattern[j]; i--, j--) {  
            if (j == 0)  
                return comparisonCount;  
            comparisonCount++; 
        }  
        i += max(good_table[pLen - j - 1], bad_table[target[i]]);
        comparisonCount++;
    }  
    return comparisonCount;  
}  

int main() {  
	freopen("test.txt","r",stdin); 
	double st=clock();
    string pattern, target;  
    cin >> target >> pattern;  
    int cnt = fun(pattern, target);  
	double ed=clock();
	ofstream ofs;
	ofs.open("BM.txt",ios::out|ios::app);
	ofs<<(ed-st)/CLOCKS_PER_SEC<<endl;
	ofs<<cnt<<endl;
	ofs.close();
    return 0;  
}
