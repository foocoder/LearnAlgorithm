// ---- Program Info Start----
//FileName:     GreatestCommonDivisor.cpp
//
//Author:       Fuchen Duan
//
//Email:        slow295185031@gmail.com
//
//CreatedAt:    2016-07-15 16:52:43
// ---- Program Info End  ----

#include <iostream>

using namespace std;

int gcd(int p, int q){
    if( !q )
        return p;
    int r = p % q;
    cout<<"("<<p<<","<<q<<") ";
    return gcd( q, r );
}

int main(int argc, char *argv[])
{
    cout<<gcd(1234567,1111111)<<endl;
    return 0;
}
