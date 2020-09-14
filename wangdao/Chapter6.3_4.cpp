//
// Created by Mr. Roy Z. on 2020/8/20.
// Copyright (c) 2020 Yu Zhong. All rights reserved.
// Chapter6.3_4.cpp
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#define MaxVertexNum 100

typedef int VertexType;
typedef int EdgeType;
typedef bool VisitType;
typedef int ElemType;
VisitType visited[MaxVertexNum]={0};
EdgeType distance[MaxVertexNum];//非带权图从u到其他节点的最小路径
typedef struct ArcNode{//边表结点
    EdgeType adjvex;
    EdgeType weight;
    struct ArcNode *next;
}ArcNode;
typedef struct VNode{//顶点表结点
    VertexType data;
    VertexType state;//权值/状态
    ArcNode *first;//指向第一条依附该结点的弧的指针
}VNode,AdjList[MaxVertexNum];
typedef struct {//邻接表
    AdjList vertices;
    int vexnum;
    int arcnum;
}ALGraph;
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

void CreateGraph(ALGraph &G,EdgeType edge[][5],int n,int m){
    ArcNode *e;
    G.vexnum=n;
    G.arcnum=m;
    for(int i = 0;i < G.vexnum;i++) /* 读入顶点信息,建立顶点表 */
        G.vertices[i].first=NULL; 	/* 将边表置为空表 */
    for(int i = 0;i < MaxVertexNum;i++)
        G.vertices[i].state= 0;
    for (int i = 0; i < G.vexnum; i++) {
        G.vertices[i].data=i;
        for (int j = 0; j < G.vexnum; j++) {
            if(edge[i][G.vexnum-1-j]==1){
                e=(ArcNode *)malloc(sizeof(ArcNode));
                e->adjvex=G.vexnum-1-j;
                e->weight=1;
                e->next=G.vertices[i].first;
                G.vertices[i].first=e;
            }
        }
        G.vertices[i].state= 1;
    }
}

void visit(ALGraph G,int x){
    printf("%d ",G.vertices[x].data);
}

void PrintfGraph(ALGraph G){
    ArcNode *p;
    for (int i = 0; i < MaxVertexNum; i++) {
        if(G.vertices[i].state==1){
            p=G.vertices[i].first;
            visit(G,i);
            while (p!=NULL){
                printf("%d,%d  ",p->adjvex,p->weight);
                p=p->next;
            }
            printf("\n");
        }
    }
    printf("结点数:%d\n",G.vexnum);
    printf("弧数:%d\n",G.arcnum);
}

bool Adjacent(ALGraph G,int n,int m){
    if(G.vertices[n].state<1||G.vertices[m].state<1||n>=MaxVertexNum||m>=MaxVertexNum)
        return false;
    ArcNode *p=G.vertices[n].first;
    while(p!=NULL){
        if(p->adjvex==m)
            return true;
        p=p->next;
    }
    return false;
}

void Neighbors(ALGraph G,int x){
    if(G.vertices[x].state<1||x>=MaxVertexNum){
        printf("error\n");
        return;
    }
    ArcNode *p=G.vertices[x].first;
    while(p!=NULL){
        printf("%d ",p->adjvex);
        p=p->next;
    }
    printf("\n");
}

void InsertVertex(ALGraph &G,int x){
    if(G.vertices[x].state==1||x>=MaxVertexNum){
        printf("矩阵空位还有：");
        for (int i = 0; i < MaxVertexNum; i++) {
            if(G.vertices[i].state == 0)
                printf("%d ",i);
        }
        printf("\n");
        return;
    }
    G.vertices[x].state=1;
    G.vexnum++;
    G.vertices[x].data=x;
    G.vertices[x].first=NULL;
}

void AddEdge(ALGraph &G,int n,int m){
    if(G.vertices[n].state<1||G.vertices[m].state<1||n>=MaxVertexNum||m>=MaxVertexNum)
        return;
    ArcNode *p,*e;
    if(G.vertices[n].first==NULL||m<G.vertices[n].first->adjvex){
        e=(ArcNode *)malloc(sizeof(ArcNode));
        e->adjvex=m;
        e->weight=1;
        e->next=G.vertices[n].first;
        G.vertices[n].first=e;
    } else{
        p=G.vertices[n].first;
        while(p->next!=NULL){
            if(p->next->adjvex<m){
                p=p->next;
            } else
                break;
        }
        e=(ArcNode *)malloc(sizeof(ArcNode));
        e->adjvex=m;
        e->weight=1;
        e->next=p->next;
        p->next=e;
    }
    G.arcnum++;
}

void RemoveEdge(ALGraph &G,int n,int m){
    if(G.vertices[n].state<1||G.vertices[m].state<1||n>=MaxVertexNum||m>=MaxVertexNum)
        return;
    if(G.vertices[n].first==NULL||G.vertices[m].first==NULL)
        return;
    ArcNode *p,*q;
    p=G.vertices[n].first;
    if(p->adjvex==m){
        p->weight=0;
        G.vertices[n].first=p->next;
        free(p);
    } else{
        while(p->next!=NULL){
            if(p->next->adjvex==m){
                q=p->next;
                p->next=q->next;
                q->weight=0;
                free(q);
                break;
            } else{
                p=p->next;
            }
        }
    }
    G.arcnum--;
}

void DeleteVertex(ALGraph &G,int x){
    if(G.vertices[x].state<1||x>=MaxVertexNum){
        printf("error\n");
        return;
    }
    ArcNode *p;
    p=G.vertices[x].first;
    while(p!=NULL){
        RemoveEdge(G,x,p->adjvex);
        p=G.vertices[x].first;
    }
    G.vertices[x].state=0;
    G.vexnum--;
}
int FirstNeighbor(ALGraph G,int x){
    if(G.vertices[x].state<1||x>=MaxVertexNum||G.vertices[x].first==NULL){
        return -1;
    } else{
        return G.vertices[x].first->adjvex;
    }
}

int NextNeighbor(ALGraph G,int n,int m){
    if(G.vertices[n].state<1||G.vertices[m].state<1||n>=MaxVertexNum||m>=MaxVertexNum)
        return -1;
    ArcNode *p;
    p=G.vertices[n].first;
    while(p!=NULL){
        if(p->adjvex==m&&p->next!=NULL){
            return p->next->adjvex;
        } else{
            p=p->next;
        }
    }
    return -1;
}

int Get_edge_value(ALGraph G,int n,int m){
    if(G.vertices[n].state<1||G.vertices[m].state<1||n>=MaxVertexNum||m>=MaxVertexNum)
        return -1;
    ArcNode *p;
    p=G.vertices[n].first;
    while(p!=NULL){
        if(p->adjvex==m){
            return p->weight;
        } else{
            p=p->next;
        }
    }
    return -1;
}

void Set_edge_value(ALGraph &G,int n,int m,int weight){
    if(weight<=0||G.vertices[n].state<1||G.vertices[m].state<1||n>=MaxVertexNum||m>=MaxVertexNum)
        return;
    ArcNode *p;
    p=G.vertices[n].first;
    while(p!=NULL){
        if(p->adjvex==m){
            p->weight=weight;
            break;
        } else{
            p=p->next;
        }
    }
    return;
}

void BFS(ALGraph G,int n,LinkQueue Q){
    visit(G,n);
    visited[n]= true;
    EnQueue(Q,n);
    while (!isEmpty(Q)){
        DeQueue(Q,n);
        for (int i = FirstNeighbor(G,n); i >= 0; i=NextNeighbor(G,n,i)) {
            if(!visited[i]){
                visit(G,i);
                visited[i]= true;
                EnQueue(Q,i);
            }
        }
    }
}
void BFSTraverse(ALGraph G){
    LinkQueue Q;
    for (int i = 0; i < MaxVertexNum; i++) {
        visited[i]= false;
    }
    InitQueue(Q);
    for (int i = 0; i < MaxVertexNum; i++) {
        if(G.vertices[i].state>0&&visited[i]== false){
            BFS(G,i,Q);
        }
    }
}

void BFS_MIN_Distance(ALGraph G,int x){
    LinkQueue Q;
    for (int i = 0; i < MaxVertexNum; i++) {
        visited[i]= false;
    }
    for (int i = 0; i < MaxVertexNum; i++) {
        if(G.vertices[i].state>0)
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

void DFS(ALGraph G,int n){
    visit(G,n);
    visited[n]= true;
    for (int i = FirstNeighbor(G,n); i >= 0; i=NextNeighbor(G,n,i)) {
        if(!visited[i]){
            DFS(G,i);
        }
    }
}
void DFSTraverse(ALGraph G){
    for (int i = 0; i < MaxVertexNum; i++) {
        visited[i]= false;
    }
    for (int i = 0; i < MaxVertexNum; i++) {
        if(G.vertices[i].state>0&&visited[i]== false){
            DFS(G,i);
        }
    }
}

bool Exist_Path_DFS(ALGraph G,int n,int m){
    if(n==m)
        return true;
    else{
        visited[n]= true;
        for (int i = FirstNeighbor(G,n); i >= 0; i=NextNeighbor(G,n,i)) {
            if(!visited[i]&&Exist_Path_DFS(G,i,m)){
                return true;
            }
        }
    }
    return false;
}

bool Exist_Path_BFS(ALGraph G,int n,int m){
    int x;
    LinkQueue Q;
    InitQueue(Q);
    EnQueue(Q,n);
    while (!isEmpty(Q)){
        DeQueue(Q,x);
        visited[x]= true;
        for (int i = FirstNeighbor(G,x); i >= 0; i=NextNeighbor(G,x,i)) {
            if(i==m)
                return true;
            if(!visited[i])
                EnQueue(Q,i);
        }
    }
    return false;
}

int main(){
    ALGraph G;
    EdgeType edge[5][5]={{0,1,0,0,0},{1,0,1,0,0},{0,0,0,1,1},{1,0,0,0,0},{0,1,0,0,0}};
    CreateGraph(G,edge,5,7);
    PrintfGraph(G);
    if(Adjacent(G,1,2)){
        printf("存在边\n");
    } else{
        printf("不存在边\n");
    }
    Neighbors(G,2);
    InsertVertex(G,7);
    PrintfGraph(G);
    AddEdge(G,7,3);
    PrintfGraph(G);
    RemoveEdge(G,7,3);
    PrintfGraph(G);
    DeleteVertex(G,7);
    PrintfGraph(G);
    if(FirstNeighbor(G,4)==-1)
        printf("无邻接点\n");
    else
        printf("%d的第一个邻界点为%d\n",2,FirstNeighbor(G,4));
    if(NextNeighbor(G,2,3)==-1)
        printf("无下一个邻接点\n");
    else
        printf("%d下一个邻界点为%d\n",2,NextNeighbor(G,2,3));
    if(Get_edge_value(G,2,3)==-1)
        printf("error\n");
    else
        printf("权值为%d\n",Get_edge_value(G,2,3));
    Set_edge_value(G,2,3,2);
    PrintfGraph(G);
    InsertVertex(G,7);
//    BFSTraverse(G);
//    BFS_MIN_Distance(G,1);//单源非带权图从u到其他节点的最小路径
//    DFSTraverse(G);
    ///4
//    if(Exist_Path_DFS(G,1,7))
//        printf("存在路径\n");
//    else
//        printf("不存在路径\n");
    ///5
    if(Exist_Path_BFS(G,1,4))
        printf("存在路径\n");
    else
        printf("不存在路径\n");
    return 0;
}
