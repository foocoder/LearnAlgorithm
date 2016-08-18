// ---- Program Info Start----
//FileName:     repalceSpace.cpp
//
//Author:       Fuchen Duan
//
//Email:        slow295185031@gmail.com
//
//CreatedAt:    2016-08-18 14:47:21
// ---- Program Info End  ----

#include <iostream>
#include <cstring>
using namespace std;

string replaceSpace(string iniString, int length) {
    // write code here
    int cnt = 0;
    for( int i = 0; i<length; ++i ){
        if( iniString[i] == ' ' )
            cnt ++;
    }
    int n = length + cnt * 2;
    iniString.resize( n );
    for( int i=n, j=length; i>=0 && j>=0; --j ){
        if( iniString[j] != ' ' ){
            iniString[i--] = iniString[j];
        }
        else{
            iniString[i--] = '0';
            iniString[i--] = '2';
            iniString[i--] = '%';
        }
    }
    return iniString;
}

int main(int argc, char *argv[])
{
    string str;
    getline( cin, str );
    str = replaceSpace( str, str.size() );
    cout<<str;
    return 0;
}
