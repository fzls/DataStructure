/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:    maxFlow.cpp
* @version:      v1.0
* @Time:         2015-12-25 11:47:58
* @Description:  use adjacent list to represent graph and compute the maxflow with label
*
+----------------------------------------------------------
*/
#include <algorithm>
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <ctime>
#include <map>
#include <list>
#include <cstdlib>
#include <queue>
#include <cstdint>

using namespace std;
const int SOURCE = 0;
const int DESTINATION = 1;
const int MAXVERTEXS = 501;

class Adjacent {
  public:
    Adjacent( int, int );
    ~Adjacent();

  public:
    int adjacent;
    int capcity;
};

Adjacent::Adjacent( int a = -1, int c = -1 ) : adjacent{ a }, capcity{ c } {
}

Adjacent::~Adjacent() {
}

class Graph {
  public:
    Graph( string, string, int );
    ~Graph();
    int maxflow();

  private:
    map<string, int> nameToInt;
    string source, destination;
    int vertexs;
    int edges;
    vector<list<Adjacent>> graph;
    void debug( vector<vector<int>> &flow ) {
        cout << "------------------DEBUG------------------" << endl;
        cout << "GRAPH" << endl;
        for ( int i = 0; i < vertexs; ++i ) {
            cout << "vertex " << i << ":" << endl;
            for ( auto adj : graph[i] )
                cout << adj.adjacent << " " << adj.capcity << endl;
        }
        cout << "FLOW" << endl;
        for ( auto row : flow ) {
            for ( auto col : row )
                cout << col << " ";
            cout << endl;
        }
    }

    void init( vector<tuple<int, int, int>> &label ) {
        for ( auto &l : label ) {
            get<0>( l ) = 1;
            get<1>( l ) = -1;
            get<2>( l ) = INT32_MAX;
        }
    }


};

Graph::Graph( string s, string d, int e ) : nameToInt{ {s, SOURCE }, {d, DESTINATION} }, source { s }, destination{ d }, vertexs{ 2 }, edges{ e }, graph( MAXVERTEXS ) {
    //get input
    for ( int i = 0; i < edges; ++i ) {
        string ss, dd;
        int capcity;
        cin >> ss >> dd >> capcity;
        if ( nameToInt.find( ss ) == nameToInt.end() )
            nameToInt[ss] = vertexs++;
        if ( nameToInt.find( dd ) == nameToInt.end() )
            nameToInt[dd] = vertexs++;
        graph[nameToInt[ss]].push_back( Adjacent{ nameToInt[dd], capcity } );
        //debug();
    }
}

Graph::~Graph() {
}

int Graph::maxflow() {
    int maxflow = 0;
    vector<vector<int>> flow( vertexs, vector<int>( vertexs, 0 ) );
    vector<tuple<int, int, int>> label( vertexs );
    bool stillExistOpenPathInResidualGraph = true;
    while ( stillExistOpenPathInResidualGraph ) {
        stillExistOpenPathInResidualGraph = false;
        queue<int> labeled;
        labeled.push( SOURCE );
        init( label );//all init to <-1,INT32_MAX>
        while ( !labeled.empty() ) {
            int cv = labeled.front();
            labeled.pop();
            if ( cv != DESTINATION )
                for ( auto nv : graph[cv] ) {
                    if ( get<2>( label[nv.adjacent] ) == INT32_MAX ) {
                        if ( flow[cv][nv.adjacent] < nv.capcity ) {
                            label[nv.adjacent] = make_tuple( 1, cv, min( get<2>( label[cv]  ), nv.capcity - flow[cv][nv.adjacent] ) );
                            labeled.push( nv.adjacent );
                            break;
                        }
                        if ( flow[nv.adjacent][cv] > 0 ) {
                            label[nv.adjacent] = make_tuple( -1, cv, min( get<2>( label[cv]  ), flow[nv.adjacent][cv]  ) );
                            labeled.push( nv.adjacent );
                            break;
                        }
                    }
                }
            else {
                stillExistOpenPathInResidualGraph = true;
                //update flow
                int cur = cv, last = get<1>( label[cv] );
                int delta = get<2>( label[cv] );
                while ( last != -1 ) {
                    flow[last][cur] += delta * get<0>( label[cur] );
                    cur = last;
                    last = get<1>( label[cur] );
                }
                break;
            }
            debug( flow );
        }
    }
    //debug( flow );
    for ( auto nv : flow[SOURCE] )
        maxflow += nv;
    return maxflow;
}

int main() {
    freopen( "test.in", "r", stdin );
    freopen( "test.out", "w", stdout );
    string source, destination;
    int edges;
    cin >> source >> destination >> edges;
    Graph graph( source, destination, edges );
    cout << graph.maxflow();
    //cout << endl;
    //system( "pause" );
    return 0;
}
