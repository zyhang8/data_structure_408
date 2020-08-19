//
// Created by Mr. Roy Z. on 2020/8/12.
// Copyright (c) 2020 Yu Zhong. All rights reserved.
// Chapter6.2.cpp
//

#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100
typedef int VertexType;
typedef int EdgeType;

typedef struct ArcNode{
    int adjvex;
    struct ArcNode *next;
}ArcNode;
typedef struct VNode{
    VertexType data;
    ArcNode *first;
}VNode,AdjList[MaxVertexNum];
typedef struct {
    AdjList vertices;
    int vexnum,arcnum;
}ALGraph;


void Convert(ALGraph &G,EdgeType arcs[][MaxVertexNum]){
    int M,N;
    ArcNode *p;
    int n=10;//结点个数
    for (int i = 0; i < n; ++i) {
        p=(G.vertices[i]).first;
        while(p!=NULL){
            arcs[i][p->adjvex]=1;
            p=p->next;
        }
    }
}

int main(){
    ALGraph G;
    EdgeType Edge[MaxVertexNum][MaxVertexNum];
    Convert(G,Edge);
    return 0;
}
