//#include <stdio.h>
//#include <stdlib.h>
//
//
//typedef enum { false, true } bool;
//#define INFINITY 1000000
//#define MaxVertexNum 10  /* maximum number of vertices */
//typedef int Vertex;      /* vertices are numbered from 0 to MaxVertexNum-1 */
//typedef int WeightType;
//
//typedef struct GNode *PtrToGNode;
//struct GNode {
//    int Nv;
//    int Ne;
//    WeightType G[MaxVertexNum][MaxVertexNum];
//};
//typedef PtrToGNode MGraph;
//
//void print(MGraph mgraph) {
//    printf("------------start of the debug info--------------\n");
//    for (int i = 0; i < MaxVertexNum; ++i) {
//        for (int j = 0; j < MaxVertexNum; ++j)
//            printf("%d ", mgraph->G[i][j]);
//        printf("\n");
//    }
//}
//
//
//
//MGraph ReadG(); /* details omitted */
//
//void ShortestDist(MGraph Graph, int dist[], Vertex S);
//
//int main() {
//    freopen("test.in", "r", stdin);
//    freopen("test.out", "w", stdout);
//    int dist[MaxVertexNum];
//    Vertex S, V;// int s,v
//    MGraph G = ReadG();
//
//    scanf("%d", &S);
//    ShortestDist(G, dist, S);
//
//    for (V = 0; V < G->Nv; V++)
//        printf("%d ", dist[V]);
//
//    return 0;
//}
//
//int findMinInNoLabels(MGraph graph,int dist[], bool labeled[]) {
//    int minIndex = 0;
//    for (; labeled[minIndex]; ++minIndex)
//        ;
//    for (int i = 0; i < graph->Nv; ++i)
//        if (!labeled[i] && dist[i] < dist[minIndex])
//            minIndex = i;
//    //printf("minIndex is :%d\n", minIndex);
//    return minIndex;
//}
//
///* Your function will be put here */
//void ShortestDist(MGraph graph, int dist[], Vertex s) {
//    //初始化
//    //print(graph);
//    bool labeled[MaxVertexNum];
//    int minItemIndex;
//    for (int i = 0; i < graph->Nv; ++i) {
//        labeled[i] = false;
//        dist[i] = INFINITY;
//    }
//    dist[s] = 0;
//    //求最短距离
//    for (int k = 0; k < graph->Nv; ++k) {
//        minItemIndex = findMinInNoLabels(graph,dist, labeled);
//        labeled[minItemIndex] = true;
//        for (int i = 0; i < graph->Nv; ++i)
//            if (graph->G[minItemIndex][i] != -1 && dist[minItemIndex] + graph->G[minItemIndex][i] < dist[i])
//                dist[i] = dist[minItemIndex] + graph->G[minItemIndex][i];
//    }
//    for (int i = 0; i < graph->Nv; ++i)
//        if (dist[i] == INFINITY)
//            dist[i] = -1;
//}
//
//MGraph ReadG() {
//    MGraph mgraph = (MGraph)malloc(sizeof(struct GNode));
//    scanf("%d%d", &mgraph->Nv, &mgraph->Ne);
//    for (int i = 0; i < MaxVertexNum; ++i)
//        for (int j = 0; j < MaxVertexNum; ++j)
//            mgraph->G[i][j] = -1;
////print(mgraph);
//    for (int i = 0; i < mgraph->Ne; ++i) {
//        int v1, v2, w;
//        scanf("%d%d%d", &v1, &v2, &w);
//        mgraph->G[v1][v2] = w;
//    }
////print(mgraph);
//    return mgraph;
//}
