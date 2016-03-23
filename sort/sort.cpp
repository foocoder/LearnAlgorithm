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

class Solution{
    vector<int> sequence;
    public:
    Solution():sequence({8,34,3,13,1,21,5,2}){};
    void BubbleSort(){
        int sizeOfSeq = sequence.size();
        for(int ix=0; ix<sizeOfSeq; ix++){
            for(int jx=ix+1; jx<sizeOfSeq; jx++){
                if(sequence[ix] > sequence[jx]){
                    Swap(sequence[ix], sequence[jx]);
                }
            }
        }
    }
    void Swap(int & a, int & b){
        int tmp = a;
        a = b;
        b = tmp;
    }
    void Display(){
        for(auto i:sequence)
            cout<<i<<",";
        cout<<"\b "<<endl;
    }
};

int main(int argc, char *argv[])
{
    Solution test;
    cout<<"Original Sequence:";
    test.Display();
    test.BubbleSort();
    cout<<" Sorted Sequence :";
    test.Display();
    return 0;
}
