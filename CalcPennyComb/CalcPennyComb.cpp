// ---- Program Info Start----
//FileName:     CalcPennyComb.cpp
//
//Author:       Fuchen Duan
//
//Email:        slow295185031@gmail.com
//
//CreatedAt:    2016-09-02 10:06:33
// ---- Program Info End  ----

#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

int getSumVoilence( const vector<int> & penny, int idx, int aim ){
    int res = 0;
    if( idx >= penny.size() ){
        res = aim ? 0 : 1;
    }
    else
    {
        int m = aim/penny[idx];
        for( int i=0; i<=m; ++i ){
            res += getSumVoilence( penny, idx+1, aim-(i*penny[idx]) );
        }
    }
    return res;
}

int getSumMemorySearch( const vector<int> & penny, int idx, int aim, int ** dict){
    int res = dict[idx][aim];
    if( res != -1 )
        return res;
    res = 0;
    if( idx >=penny.size() ){
        res = aim ? 0 : 1;
    }
    else{
        int m = aim / penny[idx];
        for( int i=0; i<=m; ++i ){
            res += getSumMemorySearch( penny, idx+1, aim-(i*penny[idx]), dict );
        }
    }
    dict[idx][aim] = res;
    return res;
}

int getSumDP0( const vector<int> & penny, int aim ){
    int len = penny.size();
    int dp[len][aim+1];
    int p0 = penny[0];
    for( int i=1; i<=aim; ++i ){
        if( !(i % p0) ){
            dp[0][i] = 1;
        }
    }
    for( int i=0; i<len; ++i )
        dp[i][0] = 1;
    for( int i=1; i<len; ++i ){
        for( int j=1; j<=aim; ++j ){
            dp[i][j] = 0;
            p0 = penny[i];
            for( int k=j; k>=0; k-=p0 ){
                dp[i][j] += dp[i-1][k];
            }
        }
    }
    return dp[len-1][aim];
}

int getSumDP1( const vector<int> & penny, int aim ){
    int len = penny.size();
    int dp[len][aim+1];
    int p0 = penny[0];
    for( int i=1; i<=aim; ++i ){
        if( !(i % p0) ){
            dp[0][i] = 1;
        }
    }
    for( int i=0; i<len; ++i )
        dp[i][0] = 1;
    for( int i=1; i<len; ++i ){
        for( int j=1; j<=aim; ++j ){
            p0 = penny[i];
            dp[i][j] = j-p0>=0 ? dp[i-1][j]+dp[i][j-p0] : dp[i-1][j];
        }
    }
    return dp[len-1][aim];
}

int main(int argc, char *argv[])
{
    vector<int> penny{5,25,10,1};
    clock_t start, end;
    int aim = 1000;

    start = clock();
    cout<<getSumVoilence(penny, 0, aim);
    end = clock();
    cout<< " "<<(float)(end-start) / CLOCKS_PER_SEC<<endl;

    start = clock();
    int len = penny.size()+1;
    int ** dict = new int * [len];
    for( int i=0; i<len; ++i )
        dict[i] = new int [aim+1];
    for( int i=0 ; i<len; ++i ){
        for( int j=0; j<=aim; ++j ){
            dict[i][j] = -1;
        }
    }
    cout<<getSumMemorySearch(penny,0, aim, (int **)dict);
    end = clock();
    cout<< " "<<(float)(end-start) / CLOCKS_PER_SEC<<endl;
    for( int i=0; i<len; ++i )
        delete [] dict[i];
    delete[] dict;

    start = clock();
    cout<<getSumDP0(penny, aim);
    end = clock();
    cout<< " "<<(float)(end-start) / CLOCKS_PER_SEC<<endl;

    start = clock();
    cout<<getSumDP1(penny, aim);
    end = clock();
    cout<< " "<<(float)(end-start) / CLOCKS_PER_SEC<<endl;
    return 0;
}
