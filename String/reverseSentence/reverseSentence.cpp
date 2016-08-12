// ---- Program Info Start----
//FileName:     reverseSentence.cpp
//
//Author:       Fuchen Duan
//
//Email:        slow295185031@gmail.com
//
//CreatedAt:    2016-08-12 10:12:15
// ---- Program Info End  ----

#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

void reverseStr( string & str, int start, int end ){
    end --;
    while( start<end ){
        char tmp = str[start];
        str[start++] = str[end];
        str[end--] = tmp;
    }
}

int getToken( const string & str, int start ){
    char a;
    while( ( a = str[start++]) != '\0' && a != ' ' );
    return start-1;
}

void reverseSentence( string & str ){
    int index = 0, end = str.size(), wordEnd;
    reverseStr( str, 0, end );
    while( (wordEnd = getToken(str, index)) != end ){
        reverseStr( str, index, wordEnd );
        index = wordEnd+1;
    }
    reverseStr( str, index, wordEnd );
}

int main(int argc, char *argv[])
{
    if( argc < 2 )
        return -1;
    ifstream infile( argv[1], ifstream::in );
    if( !infile ){
        cerr<< argv[1] <<" Can't Opend!"<<endl;
        return -1;
    }

    int n;
    string strLine;
    infile >> n;
    getline( infile, strLine );
    for( int i=0; i<n; ++i ){
        getline( infile, strLine );
        reverseSentence( strLine );
        cout << strLine << endl;
    }
    return 0;
}
