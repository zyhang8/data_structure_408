//
// Created by Mr. Roy Z. on 2020/8/9.
// Copyright (c) 2020 Yu Zhong. All rights reserved.
// Chapter5.4.cpp
//

#include <stdio.h>
#include <stdlib.h>
#define MAXNODES 9

typedef char ElemType;
typedef struct CSNode{
    ElemType data;
    struct CSNode *lchild,*rsibling;
}CSNode,*CSTree;

/// 输出T的所有边
void TreePrintEdge(CSTree T) {
    CSNode *p;
    for (p=T->lchild; p; p=p->rsibling) {
        printf("(%c,%c)\n", T->data, p->data); //输出T的孩子
        TreePrintEdge(p); //输出p的孩子
    }
}

/// 7
void CreateCSTree(CSTree &T,ElemType *elements,int *degree,int n){
    int k=0;
    CSNode *pointer;
    CSNode *pointers[MAXNODES];
//    CSTree *pointer=new CSTree[MAXNODES];
    for (int i = 0; i < n ; i++) {
        pointer=(CSNode *)malloc(sizeof(CSNode));
        pointer->data=elements[i];
        pointer->lchild=pointer->rsibling=NULL;
        pointers[i]=pointer;
    }
    printf("1\n");
    for (int i = 0; i < n; i++) {
        if(degree[i]!=0){
            k++;
            pointers[i]->lchild=pointers[k];
            for (int j = 2; j <= degree[i]; j++) {
                k++;
                pointers[k-1]->rsibling=pointers[k];
            }
        }
    }
    T=pointers[0];
}

/// 5
int Leaves(CSTree T){
    if(T==NULL)
        return 0;
    if(T->lchild==NULL)
        return 1+Leaves(T->rsibling);
    else
        return Leaves(T->lchild)+Leaves(T->rsibling);
}

///6
int TreeDepth(CSTree T){
    int dl,dr;
    if(T==NULL)
        return 0;
    else{
        dl=TreeDepth(T->lchild);
        dr=TreeDepth(T->rsibling);
        if(dl+1>dr)
            return dl+1;
        else
            return dr;
    }
}

int main()
{
    // ABDG##H###CE#I##F##
    // https://img-blog.csdn.net/20180622225556216?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2RyZWFtMDEzMF9f/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70
    CSTree T;
    /// 7
    ElemType elements[MAXNODES] = {'A','B','C','D','E','F','G','H','I'};
    int degree[MAXNODES] = {2,1,2,2,1,0,0,0,0};
    CreateCSTree(T,elements,degree,MAXNODES);
    TreePrintEdge(T);
    /// 5
    printf("叶子节点数:%d\n",Leaves(T));
    ///6
    printf("深度为:%d\n",TreeDepth(T));
    return 0;
}
