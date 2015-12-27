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
//void ShortestDist(MGraph graph, int dist[], int count[], Vertex s);
//
//int main() {
//    freopen("test.in", "r", stdin);
//    freopen("test.out", "w", stdout);
//    int dist[MaxVertexNum], count[MaxVertexNum];
//    Vertex S, V;
//    MGraph G = ReadG();
//
//    scanf("%d", &S);
//    ShortestDist(G, dist, count, S);
//
//    for (V = 0; V < G->Nv; V++)
//        printf("%d ", dist[V]);
//    printf("\n");
//    for (V = 0; V < G->Nv; V++)
//        printf("%d ", count[V]);
//    printf("\n");
//
//    return 0;
//}
//
///* Your function will be put here */
//
//void debug(MGraph graph,int dist[], int count[]) {
//    for (int V = 0; V < graph->Nv; V++)
//        printf("%d:%d ",V, dist[V]);
//    printf("\n");
//    for (int V = 0; V < graph->Nv; V++)
//        printf("%d:%d ", V, count[V]);
//    printf("\n");
//}
//
//int findMinInNoLabels(MGraph graph, int dist[], bool labeled[]) {
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
//
//void ShortestDist(MGraph graph, int dist[], int count[], Vertex s) {
//    //初始化
//    bool labeled[MaxVertexNum];
//    int minItemIndex;
//    for (int i = 0; i < graph->Nv; ++i) {
//        labeled[i] = false;
//        count[i] = 0;
//        dist[i] = INFINITY;
//    }
//    dist[s] = 0;
//    count[s] = 1;
//    //求最短距离
//    for (int k = 0; k < graph->Nv; ++k) {
//        minItemIndex = findMinInNoLabels(graph, dist, labeled);
//        if (dist[minItemIndex] == INFINITY)
//            break;
//        labeled[minItemIndex] = true;
//        //debug(graph, dist, count);
//        for (int i = 0; i < graph->Nv; ++i)
//            if (graph->G[minItemIndex][i] !=INFINITY && dist[minItemIndex] + graph->G[minItemIndex][i] <= dist[i]) {
//                if (dist[minItemIndex] + graph->G[minItemIndex][i] < dist[i]) {
//                    count[i] = count[minItemIndex];
//                    dist[i] = dist[minItemIndex] + graph->G[minItemIndex][i];
//                } else
//                    count[i] += count[minItemIndex];
//            }
//        //debug(graph, dist, count);
//    }
//    for (int i = 0; i < graph->Nv; ++i)
//        if (dist[i] == INFINITY)
//            dist[i] = -1;
//}
//
//
//MGraph ReadG() {
//    MGraph mgraph = (MGraph)malloc(sizeof(struct GNode));
//    scanf("%d%d", &mgraph->Nv, &mgraph->Ne);
//    for (int i = 0; i < MaxVertexNum; ++i)
//        for (int j = 0; j < MaxVertexNum; ++j)
//            mgraph->G[i][j] = INFINITY;
//    //print(mgraph);
//    for (int i = 0; i < mgraph->Ne; ++i) {
//        int v1, v2, w;
//        scanf("%d%d%d", &v1, &v2, &w);
//        mgraph->G[v1][v2] = w;
//    }
//    //print(mgraph);
//    return mgraph;
//}


/*
+----------------------------------------------------------
*
* @authors: 风之凌殇 <1054073896@qq.com>
* @FILE NAME:	 ShortestPath[3].c
* @version:
* @Time:
* @Description:
*
+----------------------------------------------------------
*/
