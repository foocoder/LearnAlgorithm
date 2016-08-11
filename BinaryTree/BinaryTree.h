// ---- Program Info Start----
//FileName:     BinaryTree.h
//
//Author:       Fuchen Duan
//
//Email:        slow295185031@gmail.com
//
//CreatedAt:    2016-08-10 15:38:21
// ---- Program Info End  ----

#include <cstring>
#include <fstream>
#include <iostream>
#include <stack>
#include <queue>

#define ARR_MAX_LEN 100
#define PREORDER 0
#define INORDER 1
#define POSTORDER 2
#define BFSORDER 3
#define BFSLAYER 4

typedef
struct TreeNode{
    int  val;
    struct TreeNode * left;
    struct TreeNode * right;
    TreeNode(int x):
        val(x), left(NULL), right(NULL){}
} * pTreeNode;

class BinaryTree{
    public:
        BinaryTree(){}
        BinaryTree( const BinaryTree & ){}
        BinaryTree operator=( const BinaryTree & ){}
        ~BinaryTree(){}

        pTreeNode readBiTree( std::ifstream & infile, std::ostream & outfile = std::cerr ){
            pTreeNode root;
            std::string strHead, strData;
            std::getline( infile, strHead );
            std::getline( infile, strData );
            if( strcmp( strHead.c_str(), "PREORDER" ) == 0 ){
                int index = 0;
                root = loadBinaryTreePreOrder( strData, index );
            }
            else if( strcmp( strHead.c_str(), "INORDER" ) == 0 ){
                outfile << " INORDER Sequence cant create a Binary Tree"<< std::endl;
                return NULL;
            }
            else if( strcmp( strHead.c_str(), "POSTORDER" ) == 0 ){
                int index = 0;
                root = loadBinaryTreePostOrderStack( strData, index );
            }
            else if( strcmp( strHead.c_str(), "BFSORDER" ) == 0 ){
                int index = 0;
                root = loadBinaryTreeBSTOrder( strData, index );
            }
            return root;
        }
        void writeBiTree( pTreeNode root, std::ostream & outfile, int methods ){
            switch( methods ){
                case PREORDER://PREODER
                    {
                        std::string strHead("PREORDER");
                        std::string strData;
                        saveBinaryTreePreOrder( root, strData );
                        outfile << strHead << std::endl;
                        outfile << strData << std::endl;
                        break;
                    }
                case INORDER://INORDER
                    {
                        std::string strHead("INORDER");
                        std::string strData;
                        saveBinaryTreeInOrder( root, strData );
                        outfile << strHead << std::endl;
                        outfile << strData << std::endl;
                        break;
                    }
                case POSTORDER://POSTORDER
                    {
                        std::string strHead("POSTORDER");
                        std::string strData;
                        saveBinaryTreePostOrder( root, strData );
                        outfile << strHead << std::endl;
                        outfile << strData << std::endl;
                        break;
                    }
                case BFSORDER:
                    {
                        std::string strHead("BFSORDER");
                        std::string strData;
                        saveBinaryTreeBFSOrder( root, strData );
                        outfile << strHead << std::endl;
                        outfile << strData << std::endl;
                        break;
                    }
                default:
                    break;
            }
        }
        void traverseBiTree( pTreeNode root, std::ostream & outfile, int methods){
            switch( methods )
            {
                case PREORDER://PREODER
                    {
                        outfile << "Pre-Order Travers:"<<std::endl;
                        traverseBinaryTreePreOrder(root, outfile);
                        outfile<<std::endl;
                        break;
                    }
                case INORDER://INORDER
                    {
                        outfile << "In-Order Travers:"<<std::endl;
                        traverseBinaryTreeInOrder( root, outfile );
                        outfile<<std::endl;
                        break;
                    }
                case POSTORDER://POSTORDER
                    {
                        outfile << "Post-Order Travers:"<<std::endl;
                        traverseBinaryTreePostOrder( root, outfile );
                        outfile<<std::endl;
                        break;
                    }
                case BFSORDER:
                    {
                        outfile << "BFS-Order Travers:"<<std::endl;
                        traverseBiTreeBFS( root, outfile );
                        outfile << std::endl;
                        break;
                    }
                case BFSLAYER:
                    {
                        outfile << "BFS-Order-Layer Travers:"<<std::endl;
                        traverseBiTreeBFSLayer( root, outfile );
                        outfile << std::endl;
                        break;
                    }
                default:
                    break;
            }
        }
        void destroyBiTree( pTreeNode root ){
            if( root == NULL )
                return;
            destroyBiTree( root->left );
            destroyBiTree( root->right );
            delete root;
            return;
        }

    private:

        std::string val2str( int val ){
            std::string digit;
            char a[ARR_MAX_LEN];
            int cnt = 0;
            a[cnt++] = '!';
            while( val/10 ){
                a[cnt++] = (val % 10) + '0';
                val /= 10;
            }
            a[cnt] = (val%10) + '0';
            for( int i = cnt; i >= 0; --i ){
                digit += a[i];
            }
            return digit;
        }

        int str2val( const std::string & strVal, int & start){
            if( strVal[start] == '#' ){
                start += 2;
                return -1;
            }
            int val = 0;
            char a;
            while( (a = strVal[start++] )!= '!' ){
                val = val * 10 + ( a-'0' );
            }
            return val;
        }

        //Save Binary Tree to string
        void saveBinaryTreePreOrder( pTreeNode root , std::string & strTree){
            if( root == NULL )
            {
                strTree += "#!";
                return;
            }
            strTree += val2str( root->val );
            saveBinaryTreePreOrder( root->left, strTree );
            saveBinaryTreePreOrder( root->right, strTree );
        }

        void saveBinaryTreeInOrder( pTreeNode root , std::string & strTree){
            if( root == NULL )
            {
                strTree += "#!";
                return;
            }
            saveBinaryTreeInOrder( root->left, strTree );
            strTree += val2str( root->val );
            saveBinaryTreeInOrder( root->right, strTree );
        }

        void saveBinaryTreePostOrder( pTreeNode root , std::string & strTree){
            if( root == NULL )
            {
                strTree += "#!";
                return;
            }
            saveBinaryTreePostOrder( root->left, strTree );
            saveBinaryTreePostOrder( root->right, strTree );
            strTree += val2str( root->val );
        }

        void saveBinaryTreeBFSOrder( pTreeNode root, std::string & strTree ){
            std::queue<pTreeNode> queueSeq;
            pTreeNode ptr = root;
            queueSeq.push( ptr );
            while( !queueSeq.empty() ){
                ptr = queueSeq.front();
                queueSeq.pop();
                if( ptr == NULL ){
                    strTree += "#!";
                    continue;
                }
                strTree += val2str( ptr->val );
                queueSeq.push( ptr->left );
                queueSeq.push( ptr->right );
            }
        }

        //Load BinaryTree by string
        pTreeNode loadBinaryTreePreOrder( std::string & strTree , int & start){
            int val = str2val( strTree, start );
            if( val == -1 )
                return NULL;
            pTreeNode root = new TreeNode(val);
            root->left     = loadBinaryTreePreOrder( strTree, start );
            root->right    = loadBinaryTreePreOrder( strTree, start );
            return root;
        }

        pTreeNode loadBinaryTreePostOrderStack( std::string & strTree , int & start){
            std::stack<pTreeNode> stackSeq;
            int val = str2val( strTree, start );
            stackSeq.push( NULL );
            while( strTree[start] != '\0' ){
                val = str2val( strTree, start );
                if( val == -1 )
                    stackSeq.push( NULL );
                else{
                    pTreeNode root = new TreeNode( val );
                    root->right = stackSeq.top();
                    stackSeq.pop();
                    root->left = stackSeq.top();
                    stackSeq.pop();
                    stackSeq.push( root );
                }
            }
            return stackSeq.top();
        }

        pTreeNode loadBinaryTreeBSTOrder( std::string & strTree, int &start ){
            std::queue<pTreeNode> queueSeq;
            int val = str2val( strTree, start );
            if( val == -1 )
                return NULL;
            pTreeNode root = new TreeNode( val );
            queueSeq.push( root );
            while( !queueSeq.empty() ){
                pTreeNode ptr = queueSeq.front();
                queueSeq.pop();
                if( (val = str2val( strTree, start )) != -1 ){
                    ptr->left = new TreeNode( val );
                    queueSeq.push( ptr->left );
                }
                else{
                    ptr->left = NULL;
                }
                if( (val = str2val( strTree, start )) != -1 ){
                    ptr->right = new TreeNode( val );
                    queueSeq.push( ptr->right );
                }
                else{
                    ptr->right = NULL;
                }
            }
            return root;
        }

        //Traverse Binary Tree
        void traverseBinaryTreePreOrder( pTreeNode root, std::ostream & outfile ){
            if( root == NULL )
                return;
            outfile << root->val << " ";
            traverseBinaryTreePreOrder( root->left, outfile );
            traverseBinaryTreePreOrder( root->right, outfile );
        }
        void traverseBinaryTreeInOrder( pTreeNode root, std::ostream & outfile ){
            if( root == NULL )
                return;
            traverseBinaryTreeInOrder( root->left, outfile );
            outfile << root->val << " ";
            traverseBinaryTreeInOrder( root->right, outfile );
        }
        void traverseBinaryTreePostOrder( pTreeNode root, std::ostream & outfile ){
            if( root == NULL )
                return;
            traverseBinaryTreePostOrder( root->left, outfile );
            traverseBinaryTreePostOrder( root->right, outfile );
            outfile << root->val << " ";
        }
        void traverseBiTreeBFS( pTreeNode root, std::ostream & outfile ){
            if( root == NULL )
                return;
            std::queue<pTreeNode> queueSeq;
            pTreeNode ptr = root;
            queueSeq.push( ptr );
            while( !queueSeq.empty() ){
                ptr = queueSeq.front();
                queueSeq.pop();
                outfile << ptr-> val << " ";
                if( ptr->left )
                    queueSeq.push( ptr->left );
                if( ptr->right )
                    queueSeq.push( ptr->right );
            }
        }
        void traverseBiTreeBFSLayer( pTreeNode root, std::ostream & outfile ){
            if( root == NULL )
                return;
            std::queue<pTreeNode> queueSeq;
            pTreeNode ptr = root, last, nlast;
            queueSeq.push( ptr );
            last = ptr;
            while( !queueSeq.empty() ){
                ptr = queueSeq.front();
                queueSeq.pop();
                if( ptr->left )
                    queueSeq.push( ptr->left );
                if( ptr->right )
                    queueSeq.push( ptr->right );
                nlast = queueSeq.back();
                outfile << ptr-> val << " ";
                if( ptr == last ) {
                    outfile << std::endl;
                    last = nlast;
                }
            }
        }
};
