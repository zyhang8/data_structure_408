//
// Created by Mr. Roy Z. on 2020/8/18.
// Copyright (c) 2020 Yu Zhong. All rights reserved.
// mgraph_directed.cpp
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#define MaxVertexNum 100

typedef bool VertexType;
typedef int EdgeType;
typedef bool VisitType;
typedef int ElemType;
VisitType visited[MaxVertexNum];
EdgeType distance[MaxVertexNum];//非带权图从u到其他节点的最小路径
typedef struct{
    VertexType Vex[MaxVertexNum];
    EdgeType Edge[MaxVertexNum][MaxVertexNum];
    int vexnum;//顶点数
    int arcnum;// 弧数
}MGraph;
typedef struct LinkNode{
    ElemType  data;
    struct LinkNode *next;
}LinkNode;
typedef struct {
    LinkNode *front,*rear;
}LinkQueue;

void InitQueue(LinkQueue &Q){
    Q.front=Q.rear=(LinkNode *)malloc(sizeof(LinkNode));
    Q.front->next=NULL;
}

bool isEmpty(LinkQueue Q){
    if(Q.rear==Q.front)
        return true;
    else return false;
}

void EnQueue(LinkQueue &Q,ElemType x){
    LinkNode *p=(LinkNode *)malloc(sizeof(LinkNode));
    p->data=x;
    p->next=NULL;
    Q.rear->next=p;
    Q.rear=p;
}

bool DeQueue(LinkQueue &Q,ElemType &x){
    if(Q.rear==Q.front)
        return false;
    LinkNode *p=Q.front->next;
    x=p->data;
    Q.front->next=p->next;
    if(p==Q.rear)
        Q.rear=Q.front;
    free(p);
    return true;
}

void CreateGraph(MGraph &G,VertexType vex[],EdgeType edge[][5],int vexnum,int arcnum){
    G.vexnum=vexnum;
    G.arcnum=arcnum;
    for (int i = 0; i < G.vexnum; i++) {
        G.Vex[i]=true;
    }
    for (int i = 0; i < G.vexnum; i++) {
        for (int j = 0; j < G.vexnum; j++) {
            G.Edge[i][j]=edge[i][j];
        }
    }
}

void visit(int x){
    printf("%d ",x);
}

void PrintfGraph(MGraph G){
    for (int i = 0; i < MaxVertexNum; i++) {
        for (int j = 0; j < MaxVertexNum; j++) {
            if(G.Vex[i]&&G.Vex[j])
                printf("%d ",G.Edge[i][j]);
        }
        if(G.Vex[i]== true)
            printf("\n");
    }
    printf("结点数为:%d\n",G.vexnum);
    printf("边数为:%d\n",G.arcnum);
}

bool Adjacent(MGraph G,int n,int m){
    if(G.Edge[n][m]==0||G.Vex[n]== false||G.Vex[m]== false||n>=MaxVertexNum||m>=MaxVertexNum){
        return false;
    } else{
        return true;
    }
}

void Neighbors(MGraph G,int n){
    for (int i = 0; i < G.vexnum; i++) {
        if(Adjacent(G,n,i)){
            printf("存在边%d-%d\n",n,i);
        }
    }
}

void InsertVertex(MGraph &G,int x){
    if(x>=MaxVertexNum||G.Vex[x]== true){
        printf("矩阵空位还有：");
        for (int i = 0; i < MaxVertexNum; i++) {
            if(G.Vex[i]== false)
                printf("%d ",i);
        }
        printf("\n");
        return;
    }
    G.Vex[x]= true;
    G.vexnum++;
}
void DeleteVertex(MGraph &G,int x){
    if(x>=MaxVertexNum||G.Vex[x]== false){
        printf("无该结点，请重新输入");
        return;
    }
    for (int i = 0; i < MaxVertexNum; i++) {
        if(G.Edge[x][i]==1) {
            G.Edge[x][i] = 0;
            G.arcnum--;
        }
        if(G.Edge[i][x]==1) {
            G.Edge[i][x] = 0;
            G.arcnum--;
        }
    }
    G.Vex[x]= false;
    G.vexnum--;
}

void AddEdge(MGraph &G,int n,int m){
    if(G.Vex[n]== false||G.Vex[m]== false||n>=MaxVertexNum||m>=MaxVertexNum)
        return;
    G.Edge[n][m]=1;
    G.arcnum++;
}

void RemoveEdge(MGraph &G,int n,int m){
    if(G.Vex[n]== false||G.Vex[m]== false||n>=MaxVertexNum||m>=MaxVertexNum)
        return;
    G.Edge[n][m]=0;
    G.arcnum--;
}

int FirstNeighbor(MGraph G,int x){
    if(G.Vex[x]== false||x>=MaxVertexNum)
        return -1;
    for (int i = 0; i < MaxVertexNum; i++) {
        if(G.Vex[i]== true&&G.Edge[x][i]>=1){
            return i;
        }
    }
    return -1;
}

int NextNeighbor(MGraph G,int n,int m){
    if(G.Vex[n]== false||G.Vex[m]== false||n>=MaxVertexNum||m>=MaxVertexNum-1)
        return -1;
    for (int i = m+1; i < MaxVertexNum; i++) {
        if(G.Edge[n][i]>= 1)
            return i;
    }
    return -1;
}

int Get_edge_value(MGraph G,int n,int m){
    if(G.Vex[n]== false||G.Vex[m]== false||G.Edge[n][m]==0||n>=MaxVertexNum||m>=MaxVertexNum)
        return -1;
    return G.Edge[n][m];
}

void Set_edge_value(MGraph &G,int n,int m,int weight){
    if(G.Vex[n]== false||G.Vex[m]== false||G.Edge[n][m]==0||n>=MaxVertexNum||m>=MaxVertexNum)
        return;
    G.Edge[n][m]=weight;
}

void BFS(MGraph G,int n,LinkQueue Q){
    visit(n);
    visited[n]= true;
    EnQueue(Q,n);
    while (!isEmpty(Q)){
        DeQueue(Q,n);
        for (int i = FirstNeighbor(G,n); i >= 0; i=NextNeighbor(G,n,i)) {
            if(!visited[i]){
                visit(i);
                visited[i]= true;
                EnQueue(Q,i);
            }
        }
    }
}
void BFSTraverse(MGraph G){
    LinkQueue Q;
    for (int i = 0; i < MaxVertexNum; i++) {
        visited[i]= false;
    }
    InitQueue(Q);
    for (int i = 0; i < MaxVertexNum; i++) {
        if(G.Vex[i]>0&&visited[i]== 0){
            BFS(G,i,Q);
        }
    }
}

void BFS_MIN_Distance(MGraph G,int x){
    LinkQueue Q;
    for (int i = 0; i < MaxVertexNum; i++) {
        if(G.Vex[i]>0)
            distance[i]=-1;
    }
    visited[x]= true;
    distance[x]=0;
    InitQueue(Q);
    EnQueue(Q,x);
    printf("%d,%d ",x,distance[x]);
    while (!isEmpty(Q)){
        DeQueue(Q,x);
        for (int i = FirstNeighbor(G,x); i >= 0; i=NextNeighbor(G,x,i)) {
            if(!visited[i]){
                distance[i]=distance[x]+1;
                visited[i]= true;
                printf("%d,%d ",i,distance[i]);
                EnQueue(Q,i);
            }
        }
    }
}

void DFS(MGraph G,int n){
    visit(n);
    visited[n]= true;
    for (int i = FirstNeighbor(G,n); i >= 0; i=NextNeighbor(G,n,i)) {
        if(!visited[i]){
            DFS(G,i);
        }
    }
}
void DFSTraverse(MGraph G){
    for (int i = 0; i < MaxVertexNum; i++) {
        visited[i]= false;
    }
    for (int i = 0; i < MaxVertexNum; i++) {
        if(G.Vex[i]>0&&visited[i]== false){
            DFS(G,i);
        }
    }
}

int main(){
    MGraph G;
    VertexType vex[5]={true,true,true,true,true};
    EdgeType edge[5][5]={{0,1,0,0,0},{1,0,1,0,0},{0,0,0,1,1},{1,0,0,0,0},{0,1,0,0,0}};
    CreateGraph(G,vex,edge,5,7);
    PrintfGraph(G);
    if(Adjacent(G,2,3)== true){
        printf("存在边\n");
    } else{
        printf("不存在边\n");
    }
    Neighbors(G,2);
    InsertVertex(G,7);
    PrintfGraph(G);
    DeleteVertex(G,7);
    PrintfGraph(G);
    AddEdge(G,3,4);
    PrintfGraph(G);
    RemoveEdge(G,3,4);
    PrintfGraph(G);
    if(FirstNeighbor(G,4)==-1)
        printf("无邻接点\n");
    else
        printf("%d的第一个邻界点为%d\n",4,FirstNeighbor(G,4));
    if(NextNeighbor(G,4,1)==-1)
        printf("无下一个邻接点\n");
    else
        printf("%d下一个邻界点为%d\n",4,NextNeighbor(G,4,1));
    if(Get_edge_value(G,2,3)==-1)
        printf("error\n");
    else
        printf("权值为%d\n",Get_edge_value(G,2,3));
    Set_edge_value(G,2,3,3);
    PrintfGraph(G);
    InsertVertex(G,7);
//    BFSTraverse(G);
//    BFS_MIN_Distance(G,1);//单源非带权图从u到其他节点的最小路径
    DFSTraverse(G);
    return 0;
};
