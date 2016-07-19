// ---- Program Info Start----
//FileName:     sort.cpp
//
//Author:       Fuchen Duan
//
//Email:        slow295185031@gmail.com
//
//CreatedAt:    2016-03-21 13:28:43
// ---- Program Info End  ----

#include <iostream>
#include <vector>

using namespace std;

class MySort{
    public:
        template<class T>
        void
        BubbleSort( T & num, int size ){
            bool flag;
            for(int i=0; i<size && !flag; ++i) {
                flag = true;
                for(int j=0; j<size-i; ++j)
                    if( num[j]>num[j+1] ) {
                        Swap( num[j], num[j+1] );
                        flag = false;
                    }
            }
        }

        template<class T>
        void
        SelectionSort( T & num, int size ){
            int min;
            for(int i=0; i<size ; ++i) {
                min = i;
                for(int j=i; j<size; ++j)
                    if( num[min] > num[j])
                        min = j;
                Swap( num[min], num[i] );
            }
        }

        template<class T>
        void
        InsertionSort( T & num, int size ){
            for( int i=1; i<size; ++i )
                for( int j=i; j>=1 && num[j] < num[j-1]; --j )
                    Swap( num[j], num[j-1] );
        }

        template<class T>
        void
        ShellSort( T & num, int size ){
            int h=1;
            while( h < size/3 )
                h = 3*h + 1;
            while( h >= 1 ){
                for( int i=h; i<size; ++i ){
                    for( int j=i; j>=h && num[j] < num[j-h]; j-=h )
                        Swap( num[j], num[j-h] );
                }
                h = h/3;
            }
        }

        template<class T>
        void
        Swap(T & a, T & b){
            if( &a == &b )
                return;
            a = a^b;
            b = a^b;
            a = a^b;
        }

        template<class T>
        void
        Display( T & num ){
            for( auto i:num )
                cout<<i<<" ";
            cout<<endl;
        }
};

int main(int argc, char *argv[])
{
    vector<int> seq = { 8, 2,4,1,5,7,3,6,9,0 };
    MySort test;
    test.Display( seq );
    test.ShellSort( seq, seq.size() );
    test.Display( seq );
    return 0;
}
