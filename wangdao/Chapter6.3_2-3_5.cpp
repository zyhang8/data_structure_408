//
// Created by Mr. Roy Z. on 2020/8/20.
// Copyright (c) 2020 Yu Zhong. All rights reserved.
// Chapter6.3.cpp
//

#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#define MaxVertexNum 100

typedef int VertexType;
typedef int EdgeType;
typedef bool VisitType;
typedef int ElemType;
VisitType visited[MaxVertexNum];
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
typedef struct Linknode{
    ElemType data;
    struct Linknode *next;
} Linknode, *LiStack;

void InitStack(LiStack &S){
    S=NULL;
}

bool StateEmpty(LiStack S){
    if(S==NULL)
        return true;
    else
        return false;
}

bool Push(LiStack &S,ElemType x){
    Linknode *s = (Linknode *)malloc(sizeof(Linknode));
    s->data=x;
    if(S==NULL){
        S=s;
        S->next=NULL;
        return true;
    }
    s->next=S;
    S=s;
    return true;
}

bool Pop(LiStack &S,ElemType &x){
    if(S->next==NULL){
        x=S->data;
        S=NULL;
        return true;
    }
    Linknode *p;
    p=S;
    x=S->data;
    S=S->next;
    free(p);
    return true;
}

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
    if(n<G.vertices[m].first->adjvex){
        e=(ArcNode *)malloc(sizeof(ArcNode));
        e->adjvex=n;
        e->weight=1;
        e->next=G.vertices[m].first;
        G.vertices[m].first=e;
    } else{
        p=G.vertices[m].first;
        while(p->next!=NULL){
            if(p->next->adjvex<n){
                p=p->next;
            } else
                break;
        }
        e=(ArcNode *)malloc(sizeof(ArcNode));
        e->adjvex=n;
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
    p=G.vertices[m].first;
    if(p->adjvex==n){
        G.vertices[m].first=p->next;
        p->weight=0;
        free(p);
    } else{
        while(p->next!=NULL){
            if(p->next->adjvex==n){
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
        printf("200 %d\n",p->adjvex);
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
    p=G.vertices[m].first;
    while(p!=NULL){
        if(p->adjvex==n){
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

void DFS(ALGraph G,int n,int &Vnum,int &Enum,VisitType visited[]){
    visited[n]= true;
    Vnum++;
    for (int i = FirstNeighbor(G,n); i >= 0; i=NextNeighbor(G,n,i)) {
        Enum++;
        if(!visited[i]){
            DFS(G,i,Vnum,Enum,visited);
        }
    }
}
bool isTree(ALGraph G){
    for (int i = 0; i < MaxVertexNum; i++) {
        visited[i]= false;
    }
    int Vnum=0,Enum=0;
    DFS(G,1,Vnum,Enum,visited);
    if(Vnum==G.vexnum&&Enum==2*(G.vexnum-1))
        return true;
    else
        return false;
}

void DFS_Non_RC(ALGraph &G,int x){
    LiStack S;
    int p;
    InitStack(S);
    for (int i = 0; i < MaxVertexNum; i++) {
        visited[i]= false;
    }
    Push(S,x);
    visited[x]= true;
    while (!StateEmpty(S)){
        Pop(S,p);
        visit(G,p);
        for (int i = FirstNeighbor(G,p); i >= 0; i=NextNeighbor(G,p,i)) {
            if(!visited[i]){
                printf("200 %d\n",i);
                Push(S,i);
                visited[i]= true;
            }
        }
    }
}
///5
void FindPath(ALGraph G,int n,int m,VertexType path[],int distance){
    int x;
    ArcNode *p;
    distance++;
    path[distance]=n;
    visited[n]= true;
    if(n==m){
        for (int i = 0; i < distance+1; i++) {
            printf("%d ",path[i]);
        }
        printf("\n");
    }
    p=G.vertices[n].first;
    while (p!=NULL){
        x=p->adjvex;
        if(visited[x]== false)
            FindPath(G,x,m,path,distance);
        p=p->next;
    }
    visited[n]= false;


}

int main(){
    ALGraph G;
    EdgeType edge[5][5]={{0,1,0,1,0},{1,0,1,0,1},{0,1,0,1,1},{1,0,1,0,0},{0,1,1,0,0}};
    CreateGraph(G,edge,5,6);
    PrintfGraph(G);
    if(Adjacent(G,2,0)){
        printf("存在边\n");
    } else{
        printf("不存在边\n");
    }
    Neighbors(G,2);
    InsertVertex(G,7);
    PrintfGraph(G);
    AddEdge(G,0,2);
    PrintfGraph(G);
    RemoveEdge(G,0,2);
    PrintfGraph(G);
    DeleteVertex(G,7);
    PrintfGraph(G);
    if(FirstNeighbor(G,4)==-1)
        printf("无邻接点\n");
    else
        printf("%d的第一个邻界点为%d\n",4,FirstNeighbor(G,4));
    if(NextNeighbor(G,4,1)==-1)
        printf("无下一个邻接点\n");
    else
        printf("%d下一个邻界点为%d\n",4,NextNeighbor(G,4,1));
    if(Get_edge_value(G,3,2)==-1)
        printf("error\n");
    else
        printf("权值为%d\n",Get_edge_value(G,3,2));
    Set_edge_value(G,3,2,2);
    PrintfGraph(G);
    InsertVertex(G,7);
//    BFSTraverse(G);
//    BFS_MIN_Distance(G,1);//单源非带权图从u到其他节点的最小路径
//    DFSTraverse(G);
    ///2
//    if(isTree(G)== true)
//        printf("是树\n");
//    else
//        printf("不是树\n");
    ///3
//    DFS_Non_RC(G,1);
    ///5
    VertexType path[MaxVertexNum]={0};
    FindPath(G,1,3,path,-1);
    return 0;
}