// ---- Program Info Start----
//FileName:     KMP.cpp
//
//Author:       Fuchen Duan
//
//Email:        slow295185031@gmail.com
//
//CreatedAt:    2016-08-15 14:52:36
// ---- Program Info End  ----

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstring>

using namespace std;

typedef unordered_map<char, int> alphaBetMap;
alphaBetMap  getAlphabet( const string & txt, const string & pat ){
    alphaBetMap alphabet;
    alphaBetMap::iterator it;
    int cnt = 0;
    int n = txt.size(), m = pat.size();

    //Construct Alphabet
    for( int i=0; i<n; ++i ){
        it = alphabet.find( txt[i] );
        if( it == alphabet.end() ){
            alphabet.emplace( txt[i], cnt++ );
        }
    }
    for( int i=0; i<m; ++i ){
        it = alphabet.find( pat[i] );
        if( it == alphabet.end() ){
            alphabet.emplace( pat[i], cnt++ );
        }
    }
    return alphabet;
}

vector<vector<int> > getDFA( alphaBetMap & alphabet, const string & pat ){
    int r = alphabet.size(), m = pat.size();
    vector<vector<int>> DFA;
    DFA.reserve( m );

    //Initial DFA
    for( int i=0; i<m; ++i ){
        vector<int> tmp( r, 0 );
        DFA.push_back( tmp );
    }

    int X = 0;
    DFA[0][ alphabet[pat[0]] ] = 1;
    for( int i=1; i<m; ++i ){
        for( int j=0; j<r; ++j ){
            DFA[i][j] = DFA[X][j];
        }
        DFA[i][ alphabet[pat[i]] ] = i+1;
        X = DFA[X][ alphabet[pat[i]] ];
    }
    return DFA;
}

int KMPSearch( const string & txt, const string & pat ){
    alphaBetMap alphabet = getAlphabet( txt, pat );
    vector<vector<int>> dfa = getDFA( alphabet, pat );
    int n = txt.size(), m = pat.size();
    for( int i=0,j=0; i<n; ++i ){
        j = dfa[j][alphabet[txt[i]]];
        if( j==m )
            return i-m+1;
    }
    return n;
}

int main(int argc, char *argv[])
{
    string txt = "BBC ABCDAB ABCDABCDABDE";
    string pat = "ABCDABDF";

    cout<<txt<<endl;
    int sp = KMPSearch( txt, pat );
    for(int i=0; i<sp; ++i)
        cout<<" ";
    cout<<pat<<endl;

    return 0;
}
