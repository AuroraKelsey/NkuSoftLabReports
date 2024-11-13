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
//好后缀匹配  
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
    vector<int> bad_table(256, pLen);// 记录坏字符出现时，应该跳过的字符数，256是字符集字符数  
    vector<int> good_table(pLen, 0);// 获得好后缀数值的数组  
    for (int i = 0; i < pLen - 1; i++)  
        bad_table[pattern[i]] = pLen - 1 - i;  

    int lastPrefixPosition = pLen;//找到该位置后最长的能和模式串的前缀子串匹配的后缀子串,找不到先默认为plen  
    for (int i = pLen - 1; i >= 0; i--) {  
        if (isPrefix(pattern, i + 1)) {  
            lastPrefixPosition = i + 1;  
        }  
        good_table[pLen - 1 - i] = lastPrefixPosition - i + pLen - 1;//pLen-1-i是0~plen-1  
    }  
    //从右往左比，i是主串指针,j模式串指针  
    int comparisonCount = 0; // 字符比较次数计数器
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
