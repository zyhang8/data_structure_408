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
typedef struct{
    VertexType Vex[MaxVertexNum];
    EdgeType Edge[MaxVertexNum][MaxVertexNum];
    int vexnum;//������
    int arcnum;// ����
}MGraph;

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

void PrintfGraph(MGraph G){
    for (int i = 0; i < MaxVertexNum; i++) {
        for (int j = 0; j < MaxVertexNum; j++) {
            if(G.Vex[i]&&G.Vex[j])
                printf("%d ",G.Edge[i][j]);
        }
        if(G.Vex[i]== true)
            printf("\n");
    }
    printf("�����Ϊ:%d\n",G.vexnum);
    printf("����Ϊ:%d\n",G.arcnum);
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
            printf("���ڱ�%d-%d\n",n,i);
        }
    }
}

void InsertVertex(MGraph &G,int x){
    if(x>=MaxVertexNum||G.Vex[x]== true){
        printf("�����λ���У�");
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
        printf("�޸ý�㣬����������");
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
        if(G.Vex[i]== true&&G.Edge[x][i]==1){
            return i;
        }
    }
    return -1;
}

int NextNeighbor(MGraph G,int n,int m){
    if(G.Vex[n]== false||G.Vex[m]== false||n>=MaxVertexNum||m>=MaxVertexNum-1)
        return -1;
    for (int i = m+1; i < MaxVertexNum; i++) {
        if(G.Edge[n][i]== 1)
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

int main(){
    MGraph G;
    VertexType vex[5]={true,true,true,true,true};
    EdgeType edge[5][5]={{0,1,0,0,0},{1,0,1,0,0},{0,0,0,1,1},{1,0,0,0,0},{0,1,0,0,0}};
    CreateGraph(G,vex,edge,5,7);
    PrintfGraph(G);
    if(Adjacent(G,2,3)== true){
        printf("���ڱ�\n");
    } else{
        printf("�����ڱ�\n");
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
        printf("���ڽӵ�\n");
    else
        printf("%d�ĵ�һ���ڽ��Ϊ%d\n",4,FirstNeighbor(G,4));
    if(NextNeighbor(G,4,1)==-1)
        printf("����һ���ڽӵ�\n");
    else
        printf("%d��һ���ڽ��Ϊ%d\n",4,NextNeighbor(G,4,1));
    if(Get_edge_value(G,2,3)==-1)
        printf("error\n");
    else
        printf("ȨֵΪ%d\n",Get_edge_value(G,2,3));
    Set_edge_value(G,2,3,3);
    PrintfGraph(G);
    return 0;
};
