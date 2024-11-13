#include <bits/stdc++.h>
using namespace std;
int main(){
    for(int i=1;i<=10000;i++){
        system("build");
        system("KMP < in.txt > KMP.out");//my 和 std可替换成自己的程序名
        system("BM < in.txt > BM.out");
        if(system("fc KMP.out BM.out")){//windows下是fc,linux是diff
            puts("!!!!!!");
            while(1);
        }
    }
    return 0;
}
