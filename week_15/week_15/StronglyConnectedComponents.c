//NOTICE: if the program didn't give you how to initialize the DS, then be careful with it.

#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)

#define MaxVertices 20  /* maximum number of vertices */
typedef int Vertex;     /* vertices are numbered from 0 to MaxVertices-1 */
typedef struct VNode *PtrToVNode;
struct VNode {
    Vertex Vert;
    PtrToVNode Next;
};
typedef struct GNode *Graph;
struct GNode {
    int NumOfVertices;
    int NumOfEdges;
    PtrToVNode *Array;
};
void print(Graph graph) {
    for (int i = 0; i < graph->NumOfVertices; ++i) {
        printf("Vertex %d : ", i);

        for (PtrToVNode v = graph->Array[i]; v != NULL; v = v->Next) {
            printf("%d ", v->Vert);
        }

        printf("\n");
    }
}
Graph ReadG() {
    Graph graph = (Graph)malloc(sizeof(struct GNode));
    scanf("%d %d", &graph->NumOfVertices, &graph->NumOfEdges);
    graph->Array = (PtrToVNode *)malloc(graph->NumOfVertices * sizeof(PtrToVNode));

    //initially the adjacent list only consists pointers pointed to NULL
    for (int i = 0; i < graph->NumOfVertices; ++i) {
        graph->Array[i] = NULL;
    }

    for (int i = 0; i < graph->NumOfEdges; ++i) {
        int vs, vt;
        scanf("%d %d", &vs, &vt);
        PtrToVNode newNode = (PtrToVNode)malloc(sizeof(struct VNode));
        newNode->Vert = vt;
        newNode->Next = NULL;
        PtrToVNode temp = graph->Array[vs];

        if(temp == NULL) {//if adj list is empty, set the newNode to the first elem
            graph->Array[vs] = newNode;
        } else {//else put it to the last position
            while (temp->Next != NULL) {
                temp = temp->Next;
            }

            temp->Next = newNode;
        }
    }

    //print(graph);
    return graph;
}

void PrintV(Vertex V) {
    printf("%d ", V);
}

void StronglyConnectedComponents(Graph G, void(*visit)(Vertex V));

int main() {
    freopen("test.in", "r" , stdin);
    freopen("test.out", "w" , stdout);
    Graph G = ReadG();
    StronglyConnectedComponents(G, PrintV);
    return 0;
}

/* Your function will be put here */
enum Bool {
    false = 0,
    true = 1
} ;
typedef enum Bool bool;
void fillOrder(Graph G, int v, bool visited[], int stack[], int *top) {
    visited[v] = true;

    for (PtrToVNode adj = G->Array[v]; adj != NULL; adj = adj->Next)
        if (!visited[adj->Vert]) {
            fillOrder(G, adj->Vert, visited, stack, top);
        }

    stack[++*top] = v;
}

Graph getTranspose(Graph ori) {
    Graph graph = (Graph)malloc(sizeof(struct GNode));
    graph->NumOfVertices = ori->NumOfVertices;
    graph->NumOfEdges = ori->NumOfEdges;
    graph->Array = (PtrToVNode *)malloc(graph->NumOfVertices * sizeof(PtrToVNode));

    for (int i = 0; i < graph->NumOfVertices; ++i) {
        graph->Array[i] = NULL;
    }

    for (int i = 0; i < ori->NumOfVertices; ++i)
        for (PtrToVNode adj = ori->Array[i]; adj != NULL; adj = adj->Next) {
            PtrToVNode node = (PtrToVNode)malloc(sizeof(struct VNode));
            node->Vert = i;
            node->Next = NULL;
            PtrToVNode temp = graph->Array[adj->Vert];

            if(temp == NULL) {
                graph->Array[adj->Vert] = node;
            } else {
                while (temp->Next != NULL) {
                    temp = temp->Next;
                }

                temp->Next = node;
            }
        }

    return graph;
}
void DFSUtil(Graph gr, int v, bool visited[], void(*visit)(Vertex V)) {
    visited[v] = true;
    visit(v);

    for (PtrToVNode adj = gr->Array[v]; adj != NULL; adj = adj->Next)
        if (!visited[adj->Vert]) {
            DFSUtil(gr, adj->Vert, visited, visit);
        }
}
void StronglyConnectedComponents(Graph G, void(*visit)(Vertex V)) {
    bool visited[MaxVertices];
    int stack[MaxVertices];
    int top = -1;

    for (int i = 0; i < G->NumOfVertices; ++i) {
        visited[i] = false;
    }

    Graph gr = getTranspose(G);

    for (int i = 0; i < gr->NumOfVertices; ++i)
        if (visited[i] == false) {
            fillOrder(gr, i, visited, stack, &top);
        }

    //print(gr);

    for (int i = 0; i < G->NumOfVertices; ++i) {
        visited[i] = false;
    }

    while (top != -1) {
        int v = stack[top--];

        if (visited[v] == false) {
            DFSUtil(G, v, visited, visit);
            printf("\n");
        }
    }
}
