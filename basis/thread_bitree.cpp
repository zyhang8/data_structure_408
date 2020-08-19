//
// Created by Mr. Roy Z. on 2020-06-17.
// Copyright (c) 2020 Yu Zhong. All rights reserved.
// thread_bitree.cpp
//


#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;
typedef struct ThreadNode
{
    ElemType data;
    struct ThreadNode *lchild,*rchild;
    int ltag, rtag;
}ThreadNode,*ThreadTree;

void CreateBiTree(ThreadTree &T)
{
    char ch;
    scanf("%c",&ch);
    if(ch=='#')
        T=NULL;
    else
    {
        T=(ThreadNode *)malloc(sizeof(ThreadNode));
        if(!T)
            return;
        T->data=ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

void visit(ThreadTree &p,ThreadTree &pre){
    if(p->lchild==NULL){
//        printf("%c",p->data);
        p->lchild=pre;
        p->ltag=1;
    } else{
        p->ltag=0;
    }
    if(pre!=NULL&&pre->rchild==NULL){
//        printf("pre:%c\n",pre->data);
//        printf("p:%c\n",p->data);
        pre->rchild=p;
        pre->rtag=1;
    } else{
        pre->rtag=0;
    }
    pre=p;
}

void InThread(ThreadTree &p,ThreadTree &pre){
    if(p!=NULL){
        InThread(p->lchild,pre);
        visit(p,pre);
        InThread(p->rchild,pre);
    }
}

void NodeVisit(ThreadTree T){
    printf("%c ",T->data);
}

void ThrInOrderTraverse(ThreadTree T){//线索二叉树的中序遍历
    ThreadNode *p=T->lchild;
    while (p!=T){
//        printf("%d\n",p->ltag);
        while (p->ltag==0)
            p=p->lchild;
        NodeVisit(p);
//        printf("%d\n",p->rtag);
        while (p->rtag==1&&p->rchild!=T){
            p=p->rchild;
            NodeVisit(p);
        }
        p=p->rchild;
    }
}

void CreateInThread(ThreadTree &T){
    ThreadNode *ThrHead = (ThreadNode *)malloc(sizeof(ThreadNode));
    ThreadTree pre = NULL;
    ThrHead->rtag = 1;
    ThrHead->rchild = ThrHead;/* 先将ThrHead->rchild指向自身 */
    ThrHead->ltag = 0;
    if(T!=NULL){
        ThrHead->lchild = T;
        pre = ThrHead;/* 将ThrHead赋给pre，pre为中序线索树中first节点前驱 */
        InThread(T,pre); /* 二叉树线索化完毕，pre指向last节点 */
        pre->rchild = ThrHead;
        pre->rtag=1;
        ThrHead->rchild = pre;/* 将ThrHead->rchild指向pre(last) */
    }
    ThrInOrderTraverse(ThrHead);
}

void InOrderTraverse(ThreadTree T)//二叉树的中序遍历
{
    if(T==NULL)
        return ;
    InOrderTraverse(T->lchild);
//    printf("%c ",T->data);
    NodeVisit(T);
    InOrderTraverse(T->rchild);
}

int main()
{
    // ABDG##H###CE#I##F##
    // https://img-blog.csdn.net/20180622225556216?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2RyZWFtMDEzMF9f/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70
    ThreadTree T;
    int x;
    CreateBiTree(T);
//    printf("%c \n",T->data);
//    InOrderTraverse(T);
//    printf("\n");
//    InOrderTraverse(T);
    //G D H B A E I C F
//    printf("\n");
    CreateInThread(T);
    printf("\n");
    return 0;
}
