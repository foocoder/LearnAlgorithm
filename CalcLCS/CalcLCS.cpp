// ---- Program Info Start----
//FileName:     CalcLCS.cpp
//
//Author:       Fuchen Duan
//
//Email:        slow295185031@gmail.com
//
//CreatedAt:    2016-09-03 16:01:28
// ---- Program Info End  ----

#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int calcLCSDP( const string & str1, const string & str2 ){
    int n1 = str1.size(), n2 = str2.size();
    int dp[n1][n2];
    char p = str2[0];
    bool flag = false;
    for( int i=0; i<n1; ++i ){
        if( !flag && p != str1[i] ){
            dp[i][0] = 0;
        }
        else{
            dp[i][0] = 1;
            flag = true;
        }
    }
    p = str1[0];
    flag = false;
    for( int i=0; i<n2; ++i ){
        if( !flag && p!=str2[i] ){
            dp[0][i] = 0;
        }
        else{
            dp[0][i] = 1;
            flag = true;
        }
    }
    for( int i=1; i<n1; ++i ){
        for( int j=1; j<n2; ++j ){
            int left = dp[i][j-1], up = dp[i-1][j];
            int max = left>up ? left : up;
            if(str1[i] == str2[j])
            {
                int last = dp[i-1][j-1]+1;
                max = max > last ? max : last;
            }
            dp[i][j] = max;
        }
    }
    return dp[n1-1][n2-1];
}


