#include <bits/stdc++.h>
using namespace std;
int main(){
    for(int i=1;i<=10000;i++){
        system("build");
        system("KMP < in.txt > KMP.out");//my �� std���滻���Լ��ĳ�����
        system("BM < in.txt > BM.out");
        if(system("fc KMP.out BM.out")){//windows����fc,linux��diff
            puts("!!!!!!");
            while(1);
        }
    }
    return 0;
}
