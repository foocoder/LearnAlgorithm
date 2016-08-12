// ---- Program Info Start----
//FileName:     reverseString.cpp
//
//Author:       Fuchen Duan
//
//Email:        slow295185031@gmail.com
//
//CreatedAt:    2016-08-12 11:02:12
// ---- Program Info End  ----

#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;

void reverseStr( string & str, int start, int end ){
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

void reverseString( string & str, int index ){
    int end = str.size();
    reverseStr( str, 0, index );
    reverseStr( str, index+1, end-1 );
    reverseStr( str, 0, end-1 );
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
    getline( infile, strLine );
    istringstream ssLine( strLine );
    ssLine >> n;

    for( int i=0; i<n; ++i ){
        getline( infile, strLine );
        ssLine.str( strLine );

        string word;
        int index;
        ssLine.clear();
        ssLine >> word >> index;

        cout << word << index <<endl;
        reverseString( word, index );
        cout << word << endl;
    }
    return 0;
}
