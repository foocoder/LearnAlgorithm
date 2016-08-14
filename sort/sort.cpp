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
        //Bubble Sort
        //Stable
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

        //Selection Sort
        //Non-Stable
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

        //Insertion Sort
        //Stable
        template<class T>
        void
        InsertionSort( T & num, int size ){
            for( int i=1; i<size; ++i )
                for( int j=i; j>=1 && num[j] < num[j-1]; --j )
                    Swap( num[j], num[j-1] );
        }

        //Shell Sort
        //Non-Stable
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

        //Merge Sort 1
        //Stable
        template<class T>
        void
        UpDownMergeSort( T & num, int size ){
            aux = static_cast<type *>(malloc( size * sizeof(num[0]) ));
            MergeSort( num, 0, size-1 );
            free(aux);
        }

        //Merge Sort 2
        //Stable
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

        //Quick Sort
        //Non-Stable
        template<class T>
        void
        QuickSort( T & num, int size ){
            PrivateQuickSort( num, 0, size-1 );
        }

        //3-Way Quick Sort
        //Non-Stable
        template<class T>
        void
        TriDirectQuickSort( T & num, int size ){
            PrivateQuickSortTriDirectQuickSort( num, 0, size-1 );
        }

        //Heap Sort
        template<class T>
        void
        HeapSort( T & num, int size ){
            for( int i=size/2; i>=1; i-- )
                sink( num, i, size );
            while( size > 1 ){
                Swap( num[0], num[size-1] );
                sink( num, 1, --size );
            }
        }

        //ScaleSort
        template<class T>
        void
        ScaleSort(T & num, int size, int k) {
            // write code here
            for(int i=k/2; i>=1; i--)
                sink(num, i, k);
            T B;
            for(int i=0; i<size-k; ++i){
                B.push_back(num[0]);
                Swap(num[0],num[k+i]);
                sink(num,1,k);
            }
            while( k >= 1){
                B.push_back(num[0]);
                Swap(num[0], num[k-1] );
                sink(num,1,--k);
            }
            num = B;
        }

        //Function to Display Array
        template<class T>
        void
        Display( T & num ){
            for( auto i:num )
                cout<<i<<" ";
            cout<<endl;
        }

    private:
        //Utilities Function
        template<class T>
        void
        Swap(T & a, T & b){
            if( &a == &b )
                return;
            a = a^b;
            b = a^b;
            a = a^b;
        }

        //Function for Merge Sort
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

        //Function for Merge Sort
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

        //Function for Quick Sort
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

        //Function for Quick Sort
        template<class T>
        void
        PrivateQuickSort( T & num, int low, int high ){
            if( low >= high )
                return;
            int mid = Partition( num, low, high );
            PrivateQuickSort( num, low, mid-1 );
            PrivateQuickSort( num, mid+1, high );
        }

        //Function for 3-Way Quick Sort
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

        //Function for Heap Sort
        //Little Heap
        template<class T>
        void
        sink( T & num, int index, int size ){
            while( 2*index <= size ){
                int child = 2*index;
                if( child<size && num[child - 1]>num[child] )
                    child += 1;
                if( num[index-1] <= num[child-1] )
                    break;
                Swap( num[index-1], num[child-1] );
                index = child;
            }
        }

        //Function for Heap Sort
        template<class T>
        void
        swim( T & num, int index ){
            while( index>1 && num[index-1]>num[index/2-1] ) {
                Swap( num[index-1], num[index/2-1] );
                index /= 2;
            }
        }

        //Auxiliary Array for Merge Sort
        type * aux;
};

int main(int argc, char *argv[])
{
    vector<int> seq = { 2,1,3,6,5,4,8,7,9,10,11,12 };
    //vector<int> seq = { 1,2,3,4,3,2,1,5,2,1,3,1,4,2,2,5,3,2,1 };
    MySort<int> test;
    test.Display( seq );
    test.ScaleSort( seq, seq.size(),3 );
    test.Display( seq );
    return 0;
}
