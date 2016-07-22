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
#include <cstdlib>
#include <vector>

using namespace std;

template<class type>
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
        UpDownMergeSort( T & num, int size ){
            aux = static_cast<type *>(malloc( size * sizeof(num[0]) ));
            MergeSort( num, 0, size-1 );
            free(aux);
        }

        template<class T>
        void
        DownUpMergeSort( T & num, int size ){
            aux = static_cast<type *>(malloc( size * sizeof(num[0]) ));
            for( int sz=1; sz < size; sz *= 2 ){
                for( int lo=0; lo < size-sz; lo+=sz+sz )
                    Merge( num, lo, lo+sz-1, lo+sz+sz-1 > size-1 ? size-1 : lo+sz+sz-1 );
            }
            free(aux);
        }

        template<class T>
        void
        QuickSort( T & num, int size ){
            PrivateQuickSort( num, 0, size-1 );
        }

        template<class T>
        void
        TriDirectQuickSort( T & num, int size ){
            PrivateQuickSortTriDirectQuickSort( num, 0, size-1 );
        }

        template<class T>
        void
        Display( T & num ){
            for( auto i:num )
                cout<<i<<" ";
            cout<<endl;
        }
    private:
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
        Merge( T & num, int low, int mid, int high ){
            int left = low, right = mid+1;
            for( int i=low; i<=high; ++i )
                aux[i] = num[i];
            for( int i=low; i<=high; ++i )
                if( left > mid )
                    num[i] = aux[right++];
                else if( right > high )
                    num[i] = aux[left++];
                else if( aux[left]<=aux[right] )
                    num[i] = aux[left++];
                else
                    num[i] = aux[right++];
        }

        template<class T>
        void
        MergeSort( T & num, int low, int high ){
            if( low >= high )
                return;
            int mid = low + (high-low) / 2;
            MergeSort( num, low, mid );
            MergeSort( num, mid+1, high );
            Merge( num, low, mid, high );
        }

        template<class T>
        int
        Partition( T & num, int low, int high ){
            int left = low, right = high+1;
            int v = num[low];
            while(true){
                while( num[++left] < v && left < high );
                while( num[--right] > v && right > low );
                if( left >= right )
                    break;
                Swap( num[left], num[right] );
            }
            Swap( num[low], num[right] );
            return right;
        }

        template<class T>
        void
        PrivateQuickSort( T & num, int low, int high ){
            if( low >= high )
                return;
            int mid = Partition( num, low, high );
            PrivateQuickSort( num, low, mid-1 );
            PrivateQuickSort( num, mid+1, high );
        }

        template<class T>
        void
        PrivateQuickSortTriDirectQuickSort( T & num, int low, int high ){
            if( low >= high )
                return;
            int lt = low, i = low+1, gt = high;
            int v = num[low];
            while( i<=gt ){
                if( num[i] < v )
                    Swap( num[i++], num[lt++] );
                else if( num[i] > v )
                    Swap( num[i], num[gt--] );
                else
                    ++i;
            }
            PrivateQuickSortTriDirectQuickSort( num, low, lt-1 );
            PrivateQuickSortTriDirectQuickSort( num, gt+1, high );
        }

        type * aux;
};

int main(int argc, char *argv[])
{
    //vector<int> seq = { 8, 2,4,1,5,7,3,6,9,0 };
    vector<int> seq = { 1,2,3,4,3,2,1,5,2,1,3,1,4,2,2,5,3,2,1 };
    MySort<int> test;
    test.Display( seq );
    test.QuickSort( seq, seq.size() );
    test.Display( seq );
    return 0;
}
