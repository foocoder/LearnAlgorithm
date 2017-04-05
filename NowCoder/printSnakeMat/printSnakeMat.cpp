// ---- Program Info Start----
//FileName:     printSnakeMat.cpp
//
//Author:       Fuchen Duan
//
//Email:        slow295185031@gmail.com
//
//CreatedAt:    2016-09-07 21:58:24
// ---- Program Info End  ----

#include<cstdio>
#include<iostream>
using namespace std;
void GetResult( int Num){
    int lr=0, lc=0, rr=0, rc=0;
    int **pResult = new int *[Num];
    for(int i=0; i<Num; ++i){
        pResult[i] = new int[Num];
    }
    int cnt = 0;
    for( int i=0; i<Num; ++i ){
        lr=i;
        rc=i;
        int r = lr, c = lc;
        while(r>=rr && c<=rc){
            pResult[r][c] = ++cnt;
            r--,c++;
        }
    }
    for( int i=0; i<Num; ++i ){
        int j;
        for( j=0; j<Num-i-1; ++j ){
            printf("%d ",pResult[i][j]);
        }
        printf("%d\n",pResult[i][j]);
    }
    for(int i=0; i<Num; ++i)
        delete [] pResult[i];
    delete[]pResult;
}
int main(){
    int n;
    while(~scanf("%d", &n)){
        GetResult(n);
    }
}
