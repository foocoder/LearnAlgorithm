/*
 *@@@@@@@@@@ File Information Start  @@@@@@@@@@
 * @file:        Fold-Fulkerson.cpp
 * @author:      Fuchen Duan
 * @email:       slow295185031@gmail.com
 * @github:      https://foocoder.github.com
 * @homepage:    http://foocder.github.io
 * @create at:   2017-04-04 19:02:49
 * @last update: 2017-04-05 15:46:27
 *@@@@@@@@@@ File Information Finish @@@@@@@@@@
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <queue>
#include <stack>
#include <climits>

using namespace std;

class Graph{
    typedef
    struct Node{
        int nNodeNo = 0;
        int nWeight = 1;
        struct Node * pNextNode = NULL;

        Node( int nInputNo, int nInputWeight ):
            nNodeNo( nInputNo ),
            nWeight( nInputWeight ),
            pNextNode( NULL ){}
        Node( const Node & rhs ):
            nNodeNo(rhs.nNodeNo),
            nWeight(rhs.nWeight),
            pNextNode(NULL){}
    }Node;

    int nEdgeNum;
    int nVertexNum;
    vector<Node> vNodeVector;

    public:
    Graph(){
        cout<<"Input Number of vertex and edge:"<<endl;
        cin>>nVertexNum>>nEdgeNum;
        for( int i=0; i<nVertexNum; ++i ){
            Node nodeTemp( i, -1 );
            vNodeVector.push_back( nodeTemp );
        }
        cout<<"Input Edge Relationships:(Head Tail and Weight, Separated by blank)"<<endl;
        for( int i=0; i<nEdgeNum; ++i ){
            int nEdgeHead, nEdgeTail, nInputWeight;
            cin>>nEdgeHead>>nEdgeTail>>nInputWeight;
            Node * pTail = new Node( nEdgeTail, nInputWeight );
            Node * pNode = &vNodeVector[nEdgeHead];
            while( pNode->pNextNode != NULL ){
                pNode = pNode->pNextNode;
            }
            pNode->pNextNode = pTail;
        }
    }
    ~Graph(){
        for( auto node : vNodeVector ){
            Node * pNode = node.pNextNode;
            while( pNode != NULL ){
                Node * pNext = pNode->pNextNode;
                delete pNode;
                pNode = pNext;
            }
        }
    }
    void fnPrintGraph(){
        if( vNodeVector.empty() ){
            cout<<"Graph is empty"<<endl;
            return;
        }
        for( auto &node : vNodeVector ){
            cout<<"("<<node.nNodeNo<<")";
            Node * pNode = node.pNextNode;
            while( pNode != NULL ){
                cout<<"->("<<pNode->nNodeNo<<"):"<<pNode->nWeight;
                pNode = pNode->pNextNode;
            }
            cout<<"->NULL"<<endl;
        }
    }
    bool fnBreadthFistSearch( int nSrcNode, int nTerminalNode, vector<int> & vStoTPath ){
        vector<bool> isVisited( nVertexNum, false );
        queue<int> queueNext;
        queueNext.push( nSrcNode );
        isVisited[nSrcNode] = true;
        vector<int> vPath( nVertexNum, -1 );
        for( int & i : vPath ){
            i = -1;
        }
        while( !queueNext.empty() && !isVisited[nTerminalNode] ){
            int nNextNode = queueNext.front();
            queueNext.pop();
            Node * pNode = vNodeVector[nNextNode].pNextNode;
            while( pNode != NULL ){
                if( !isVisited[pNode->nNodeNo] && (pNode->nWeight>0) ) {
                    queueNext.push( pNode->nNodeNo );
                    isVisited[pNode->nNodeNo] = true;
                    vPath[pNode->nNodeNo] = nNextNode;
                }
                pNode = pNode->pNextNode;
            }
        }
        if( isVisited[nTerminalNode] ){
            stack<int> stackPath;
            int nCurNode = nTerminalNode;
            while( vPath[nCurNode] != -1 ){
                stackPath.push( nCurNode );
                nCurNode = vPath[nCurNode];
            }
            stackPath.push( nCurNode );
            while( !stackPath.empty() ){
                vStoTPath.push_back( stackPath.top() );
                stackPath.pop();
            }
        }
        #ifdef DEBUG1
        cout<<"\nPrint Path"<<endl;
        for( int i=0; i<nVertexNum; ++i ){
            int nCurNode = i;
            while( vPath[nCurNode] != -1 ){
                cout<<nCurNode<<"<-";
                nCurNode = vPath[nCurNode];
            }
            cout<<nSrcNode<<endl;
        }
        #endif
        return isVisited[nTerminalNode];
    }
    //nChangedVal 为正
    void fnUpdateEdge( int nHead, int nTail, int nChangedVal ){
        if( nHead >= nVertexNum || nTail >= nVertexNum )
            return;
        #ifdef DEBUG
        assert(nChangedVal>=0);
        #endif
        //Update nHead->nTail;
        Node * pNode = vNodeVector[nHead].pNextNode;
        while( pNode != NULL ){
            if( pNode->nNodeNo == nTail ){
                pNode->nWeight -= nChangedVal;
                #ifdef DEBUG
                assert( pNode->nWeight>=0 );
                #endif
                break;
            }
            pNode = pNode->pNextNode;
        }
        //Update nTail->nHead;
        pNode = &vNodeVector[nTail];
        while( pNode->pNextNode != NULL ){
            if( pNode->nNodeNo == nHead ){
                pNode->nWeight += nChangedVal;
                break;
            }
            pNode = pNode->pNextNode;
        }
        if( !pNode->pNextNode ){
            Node * pNewNode = new Node( nHead, nChangedVal );
            pNode->pNextNode = pNewNode;
        }
        return;

    }

    int fnGetEdgeNum() const{
        return nEdgeNum;
    }
    int fnGetVertexNum() const{
        return nVertexNum;
    }
    int fnGetEdgeWeight( int nHead, int nTail ) const{
        if( nHead >= nVertexNum || nTail >= nVertexNum )
            return INT_MAX;
        Node * pNode = vNodeVector[nHead].pNextNode;
        while( pNode != NULL ){
            if( pNode->nNodeNo == nTail ){
                return pNode->nWeight;
            }
            pNode = pNode->pNextNode;
        }
        return INT_MAX;
    }
};

int Fold_Fulkerson( Graph & residualNetwork, int nSrcNode, int nTerminalNode ){
    int nVertexNum = residualNetwork.fnGetVertexNum();

    int nMaxFlow = 0;
    vector<int> vPath;
    while( residualNetwork.fnBreadthFistSearch(nSrcNode, nTerminalNode, vPath) ){
        int nMinSegFlow = INT_MAX;
        int nPathSize = vPath.size();

        #ifdef DEBUG
        cout<<"Print augmenting path:";
        cout<<"("<<vPath[0]<<")";
        for( int i=1; i<nPathSize; ++i ){
            cout<<"->("<<vPath[i]<<"):"<<residualNetwork.fnGetEdgeWeight(vPath[i-1], vPath[i]);
        }
        cout<<endl;
        #endif
        //计算增广路径最小Weight
        for( int i=0; i<nPathSize-1; ++i ){
            int nWeight = residualNetwork.fnGetEdgeWeight(vPath[i], vPath[i+1]);
            nMinSegFlow = nMinSegFlow < nWeight ? nMinSegFlow : nWeight;
        }

        //更新残余网路Weight
        for( int i=0; i<nPathSize-1; ++i ){
            residualNetwork.fnUpdateEdge(vPath[i], vPath[i+1], nMinSegFlow);
        }
        nMaxFlow += nMinSegFlow;
        vPath.clear();
    }
    return nMaxFlow;
}

int main(int argc, char *argv[])
{
    Graph test;
    test.fnPrintGraph();
    cout<<Fold_Fulkerson( test, 0, 5 )<<endl;
    /* test.fnBreadthFistSearch(1,1); */
    return 0;
}
