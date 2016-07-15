// ---- Program Info Start----
//FileName:     BinarySearch.cpp
//
//Author:       Fuchen Duan
//
//Email:        slow295185031@gmail.com
//
//CreatedAt:    2016-07-15 15:37:11
// ---- Program Info End  ----

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

template<typename T>
int
BinarySearch(vector<T> & vec, int key){
    int low = 0, high = vec.size();
    while( low<=high ){
        int mid = ( low+high )/2;
        if(vec[mid] == key)
            return mid;
        else if(vec[mid] > key)
            high = mid-1;
        else if(vec[mid] < key)
            low = mid+1;
    }
    return -1;
}

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        cout<<"No Data!"<<endl;
        return 0;
    }
    ifstream inputFS( argv[1], std::ios::in );
    string lines;
    while(getline( inputFS, lines )){
        istringstream lineSS(lines);
        int num;
        vector<int> intVect;
        while(lineSS>>num)
        {
            intVect.push_back(num);
        }
        for(int i=0; i<10; ++i){
            int key = BinarySearch(intVect, i);
            if( key < 0 )
                cout<<i<<" is not found!"<<endl;
            else
                cout<<i<<" is at position "<<key<< " !"<<endl;
        }
    }

    return 0;
}
