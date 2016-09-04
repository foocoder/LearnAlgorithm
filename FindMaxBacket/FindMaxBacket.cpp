// ---- Program Info Start----
//FileName:     FindMaxBacket.cpp
//
//Author:       Fuchen Duan
//
//Email:        slow295185031@gmail.com
//
//CreatedAt:    2016-09-03 20:00:13
// ---- Program Info End  ----

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

int FindMaxBacketVoilence( const vector<int> & w, const vector<int> & v, int idx, int n, int cap, vector<int> &vec ){
    if( idx == n || cap==0 ){
        int val = 0;
        for( auto i : vec ){
            val += v[i];
        }
        return val;
    }
    int v1 = 0, v2 = 0;
    if( w[idx] <= cap )
    {
        vec.push_back( idx );
        v1 = FindMaxBacketVoilence(w,v,idx+1,n,cap-w[idx],vec);
        vec.pop_back();
    }
    v2 = FindMaxBacketVoilence(w,v,idx+1,n,cap,vec);
    return v1 > v2 ? v1 : v2;
}

int FindMaxBacketDP( const vector<int> & w, const vector<int> & v, int n, int cap ){
    int dp[n][cap+1];
    for( int i=0;i<n; ++i ){
        dp[i][0] = 0;
    }
    bool flag = false;
    int w0 = w[0], v0 = v[0];
    for( int i=1; i<w0; ++i ){
        dp[0][i] = 0;
    }
    for( int i=w0; i<=cap; ++i ){
        dp[0][i] = v0;
    }

    for( int i=1; i<n; ++i ){
        int wi = w[i], vi = v[i];
        for( int j=1; j<=cap; ++j ){
            int add = j>=wi ? dp[i-1][j-wi]+vi : 0;
            int em = dp[i-1][j];
            dp[i][j] = add > em ? add : em;
        }
    }
    return dp[n-1][cap];
}

int main(int argc, char *argv[])
{
    vector<int> w{42,25,30,35,42,21,26,28};
    vector<int> v{261,247,419,133,391,456,374,591};
    vector<int> vec;
    clock_t start, end;
    start = clock();
    cout<<FindMaxBacketVoilence(w,v,0,w.size(),297,vec)<<" ";
    end = clock();
    cout<<(double)(end-start) / CLOCKS_PER_SEC<<endl;

    start = clock();
    cout<<FindMaxBacketDP(w,v,w.size(),297)<<" ";
    end = clock();
    cout<<(double)(end-start) / CLOCKS_PER_SEC<<endl;
    return 0;
}
