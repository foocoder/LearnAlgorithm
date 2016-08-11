// ---- Program Info Start----
//FileName:     BinaryTree.cpp
//
//Author:       Fuchen Duan
//
//Email:        slow295185031@gmail.com
//
//CreatedAt:    2016-08-10 19:13:36
// ---- Program Info End  ----

#include <iostream>
#include "BinaryTree.h"
using namespace std;

int main(int argc, char *argv[])
{
    ifstream infile( argv[1], ifstream::in );
    if( !infile ){
        cerr<< " Open files error!" <<endl;
        return -1;
    }
    BinaryTree test;
    pTreeNode root;
    root = test.readBiTree( infile );
    if( !root )
    {
        infile.close();
        return -1;
    }
    test.traverseBiTree( root, cout, PREORDER);
    test.traverseBiTree( root, cout, INORDER);
    test.traverseBiTree( root, cout, POSTORDER);
    test.traverseBiTree( root, cout, BFSORDER);
    test.traverseBiTree( root, cout, BFSLAYER);
    test.writeBiTree( root, cout, PREORDER );
    test.writeBiTree( root, cout, INORDER );
    test.writeBiTree( root, cout, POSTORDER );
    test.writeBiTree( root, cout, BFSORDER );
    test.destroyBiTree( root );
    infile.close();
    return 0;
}
