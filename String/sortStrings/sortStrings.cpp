// ---- Program Info Start----
//FileName:     sortStrings.cpp
//
//Author:       Fuchen Duan
//
//Email:        slow295185031@gmail.com
//
//CreatedAt:    2016-08-12 13:56:36
// ---- Program Info End  ----

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

template<class T>
bool lessthan( const T & lhs, const T & rhs){
    return lhs < rhs;
}

template<>
bool lessthan<string>( const string & lhs, const string & rhs ){
    string str1(lhs), str2(rhs);
    str1 += rhs;
    str2 += lhs;
    return strcmp( str1.c_str(), str2.c_str() ) < 0;
}

template< class T>
int partition( T num[], int lo, int hi ){
    int i = lo, j = hi+1;
    T v = num[lo];
    while( true ){
        while( lessthan( num[++i], v ) && i < hi );
        while( lessthan( v, num[--j] ) && j > lo );
        if( i >= j ) break;
        swap( num[i], num[j] );
    }
    swap( num[lo], num[j] );
    return j;
}

template<class T>
void sort( T num[], int lo, int hi ){
    if( lo >= hi )
        return;
    int j = partition( num, lo, hi );
    sort( num, lo, j-1 );
    sort( num, j+1, hi );
}

template<class T>
void quicksort( T num[], int size ){
    sort( num, 0, size-1 );
}

int main(int argc, char *argv[])
{
    string num[] = {
        "tcp",
        "ip",
        "network",
        "cpp",
        "csharp",
        "pearson",
        "computer",
        "algorithm",
        "templates",
        "class",
        "offer",
        "ping",
        "masters",
        "traps",
        "structures",
        "interpretations",
        "java",
        "python",
        "matlab",
        "database",
        "dataset",
        "ba",
        "b",
        "trace",
        "route",
        "t",
        "tune",
    };
    int cnt = 0;
    for( auto i:num ) {
        cout<<i<<" ";
        cnt ++ ;
    }
    cout<<endl;

    quicksort( num, cnt );

    for( auto i:num )
        cout<<i<<" ";
    cout<<endl;

    return 0;
}
