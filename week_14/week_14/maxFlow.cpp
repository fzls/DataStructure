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
const int MAXVERTEXS = 1000;

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
    vector<vector<int>> graph;
    void debug( vector<vector<int>> &flow ) {
        cout << "------------------DEBUG------------------"
             << endl;
        cout << "GRAPH" << endl;

        for ( int i = 0; i < vertexs; ++i ) {
            for ( int j = 0; j < vertexs; ++j ) {
                if ( graph[i][j] != INT32_MAX ) {
                    cout << "[" << i << "," << j << "]:" <<
                         graph[i][j] << " ";
                } else {
                    cout << "          ";
                }
            }

            cout << endl;
        }

        cout << "FLOW" << endl;

        for ( int i = 0; i < vertexs; ++i ) {
            for ( int j = 0; j < vertexs; ++j )
                if ( flow[i][j] != 0 ) {
                    cout << "flow[" << i << "][" << j << "]:" <<
                         flow[i][j] << "  ";
                } else {
                    cout << "                ";
                }

            cout << endl;
        }
    }

    void init( vector<tuple<int, int, int>> &label ) {
        for ( auto &l : label ) {
            get<0>( l ) = 1;
            get<1>( l ) = -1;
            get<2>( l ) = INT32_MAX;
        }

        get<2>( label[SOURCE] ) = INT32_MAX - 1;
    }

    bool dfs( const int cv,
              vector<tuple<int, int, int>> &label,
              vector<vector<int>> &flow ) {
        if ( cv == DESTINATION ) {
            //update flow
            int cur = cv, last = get<1>( label[cv] );
            int delta = get<2>( label[cv] );

            while ( last != -1 ) {
                flow[last][cur] += delta * get<0>( label[cur] );
                cur = last;
                last = get<1>( label[cur] );
            }

            //debug( flow );
            return true;
        }

        for ( int nv = 0; nv < vertexs; ++nv ) {
            if ( get<2>( label[nv] ) == INT32_MAX ) {
                if ( graph[cv][nv] != INT32_MAX &&
                        flow[cv][nv] < graph[cv][nv] ) {
                    label[nv] = make_tuple( 1, cv,
                                            min( get<2>( label[cv] ),
                                                 graph[cv][nv] - flow[cv][nv] ) );

                    if ( dfs( nv, label, flow ) ) {
                        return true;
                    } else {
                        label[nv] = make_tuple( 1, -1, INT32_MAX );
                    }
                }

                if ( graph[nv][cv] != INT32_MAX &&
                        flow[nv][cv] > 0 ) {
                    label[nv] = make_tuple( -1, cv,
                                            min( get<2>( label[cv] ), flow[nv][cv] ) );

                    if ( dfs( nv, label, flow ) ) {
                        return true;
                    } else {
                        label[nv] = make_tuple( 1, -1, INT32_MAX );
                    }
                }
            }
        }

        return false;
    }



};

Graph::Graph( string s, string d,
              int e ) : nameToInt{ {s, SOURCE }, {d, DESTINATION} },
source { s }, destination{ d }, vertexs{ 2 },
       edges{ e }, graph( MAXVERTEXS,
vector<int>( MAXVERTEXS, INT32_MAX ) ) {
    //get input
    for ( int i = 0; i < edges; ++i ) {
        string ss, dd;
        int capcity;
        cin >> ss >> dd >> capcity;

        if (nameToInt.find( ss ) == nameToInt.end() ) {
            nameToInt[ss] = vertexs++;
        }

        if (nameToInt.find(dd) == nameToInt.end()) {
            nameToInt[dd] = vertexs++;
        }

        graph[nameToInt[ss]][nameToInt[dd]] = capcity;
        //debug();
    }
}

Graph::~Graph() {
}

int Graph::maxflow() {
    int maxflow = 0;
    vector<vector<int>> flow( vertexs,
                              vector<int>( vertexs, 0 ) );
    vector<tuple<int, int, int>> label( vertexs );

    do { init( label ); }
    while ( dfs( SOURCE, label, flow));

    for ( auto nv : flow[SOURCE] ) {
        maxflow += nv;
    }

    return maxflow;
}


int main() {
    {
        #ifdef ONLINE_JUDGE
        #else
        freopen( "test.in", "r", stdin );
        freopen( "test.out", "w", stdout );
        #endif
    }
    string source, destination;
    int edges;
    cin >> source >> destination >> edges;
    Graph graph( source, destination, edges );
    cout << graph.maxflow();
    {
        #ifdef ONLINE_JUDGE
        #else
        cout << endl;
        system( "pause" );
        #endif
        return 0;
    }
}
