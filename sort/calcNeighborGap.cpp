// ---- Program Info Start----
//FileName:     calcNeighborGap.cpp
//
//Author:       Fuchen Duan
//
//Email:        slow295185031@gmail.com
//
//CreatedAt:    2016-08-14 15:50:42
// ---- Program Info End  ----

#include <iostream>
#include <vector>

using namespace std;

class Gap {
public:
    int maxGap(vector<int> & A, int n) {
        // write code here
        int min, max;
        getMinMax( A, n, min, max );
        double gap =static_cast<double> (max - min) / n;

        //初始化Buckets
        vector<vector<int> > bucket;
        bucket.reserve( n+1 );
        for( int i=0; i<=n; ++i ){
            vector<int> tmp;
            tmp.reserve(2);
            bucket.push_back(tmp);
        }

        //将数组扔进Buckets 中
        for( int i = 0; i<n; ++i){
            int index =  static_cast<int> ( (A[i]-min)/gap );
            cout<<index<<endl;
            if( bucket[index].empty() ){
                bucket[index].push_back( A[i] );
                bucket[index].push_back( A[i] );
            }
            else if( A[i] < bucket[index][0] )
                bucket[index][0] = A[i];
            else if( A[i] > bucket[index][1] )
                bucket[index][1] = A[i];
        }

        //依次计算相隔桶中差值
        int maxVal = 0, lastMax = min-1;
        for( int i=0; i<=n; ++i ){

            if( !bucket[i].empty() ){
                if( lastMax >= min ){
                	int curVal = bucket[i][0] - lastMax;
                	maxVal = curVal > maxVal ? curVal : maxVal;
                	lastMax = bucket[i][1];
                }
                else
                    lastMax = bucket[i][1];
            }
        }
        return maxVal;
    }
    void getMinMax( const vector<int> & A, int n, int & min, int & max ){
        min = max = A[0];
        for( int i=1; i<n; ++i){
            if( A[i] > max )
                max = A[i];
            else if (A[i] < min)
                min = A[i];
        }
    }
};

int main(int argc, char *argv[])
{
    Gap t;
    vector<int> A = { 1,2,5,4,6,10 };
    cout<< t.maxGap( A, A.size() );
    return 0;
}
