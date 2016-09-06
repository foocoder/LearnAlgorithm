// ---- Program Info Start----
//FileName:     findMaxCircle.cpp
//
//Author:       Fuchen Duan
//
//Email:        slow295185031@gmail.com
//
//CreatedAt:    2016-09-06 13:20:05
// ---- Program Info End  ----

#include <iostream>
#include <cstring>
#include <ctime>

using namespace std;

bool checkCircle( const string & str, int lo, int hi){
    for(int i=lo, j=hi; i<j; ++i, --j){
        if( str[i] != str[j]) return false;
    }
    return true;
}
int findMaxCircleVoilence( const string &  str ){
    int n = str.size();
    for( int i=n; i>0; i--){
        for( int j=0; j<i; ++j ){
            if( checkCircle(str, j, j+i-1))
                return i;
        }
    }
    return 0;
}

int findMaxCircleVoilence1( const string & str ){
    int n = str.size();
    int max = 1;
    string str1( 2*n+1, '#');
    for( int i=0; i<n; ++i ){
        str1[2*i+1] = str[i];
    }
    int m = 2*n+1;
    for( int i=0; i<m; ++i ){
        int j;
        for( j=1; i-j>=0 && i+j<m; ++j ){
            if( str1[i-j] != str1[i+j] ) break;
        }
        if( max < j-1 )
            max = j-1;
    }
    return max;
}

int findMaxCircleDP( const string & str ){
    int n = str.size();
    bool dp[n][n];
    dp[0][0] = true;
    for( int i=1; i<n; ++i ){
        dp[i][i] = true;
        //考虑长度为2的情况
        dp[i][i-1] = true;
    }
    int max = 1;
    for( int i=2; i<=n; ++i ){
        for( int j=0; j<=n-i; ++j ){
            if( str[j] == str[j+i-1] && dp[j+1][j+i-2]){
                dp[j][j+i-1] = true;
                if( i > max ) max = i;
            }
            else
                dp[j][j+i-1] = false;
        }
    }
    return max;
}

int findMaxCircleManacher( const string & str ){
    const int n = str.size();
    const int m = 2*n+1;

    string str1( 2*n+1, '#');
    for( int i=0; i<n; ++i ){
        str1[2*i+1] = str[i];
    }

    int idx =0, pRight = 1;
    int pArr[m];
    int max=1;
    pArr[0] = 1;
    for( int i=1; i<m; ++i ){
        if( i>=pRight){
            int j;
            for( j=1; i-j>=0 && i+j <m && str1[i+j]==str1[i-j]; ++j );
            pArr[i] = j-1;
            if( max < j-1 ) max = j-1;
            idx = i;
            pRight = i+j;
        }
        else if( i<pRight ){
            int li = 2 * idx - i;
            int lpr = 2 * idx - pRight;

            if( li - pArr[li] > lpr )
                pArr[i] = pArr[li];
            else if( li - pArr[li] < lpr )
            {
                pArr[i] = li-lpr;
                if( max < li-lpr ) max = li-lpr;
            }
            else{
                int j;
                for( j=pRight-i; i-j>=0 && i+j <m && str1[i+j]==str1[i-j]; ++j );
                pArr[i] = j-1;
                if( max < j-1 ) max = j-1;
                idx = i;
                pRight = i+j;
            }
        }
    }
    return max;
}

int main(int argc, char *argv[])
{
    string str;
    getline( cin, str);
    clock_t start, end;

    start = clock();
    cout<<findMaxCircleVoilence( str )<<endl;
    end = clock();
    cout<<"Violence time is "<<(double)(end-start)/ CLOCKS_PER_SEC<<endl;

    start = clock();
    cout<<findMaxCircleVoilence1( str )<<endl;
    end = clock();
    cout<<"Violence1 time is "<<(double)(end-start)/ CLOCKS_PER_SEC<<endl;

    start = clock();
    cout<<findMaxCircleDP( str )<<endl;
    end = clock();
    cout<<"DP time is "<<(double)(end-start)/ CLOCKS_PER_SEC<<endl;

    start = clock();
    cout<<findMaxCircleManacher( str )<<endl;
    end = clock();
    cout<<"Manacher time is "<<(double)(end-start)/ CLOCKS_PER_SEC<<endl;
    return 0;
}
