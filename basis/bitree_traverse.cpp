//
// Created by Mr. Roy Z. on 2020-06-14.
// Copyright (c) 2020 Yu Zhong. All rights reserved.
// bitree_traverse.cpp
//

#include <stdio.h>
#include <stdlib.h>
#define MaxSize 50
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef int ElemType;


typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;
typedef struct {
    struct BiTNode *data[MaxSize];
    int front,rear;
} SqQueue;
typedef struct {
    BiTree *base;
    BiTree *top;
    int stacksize;
}SqStack;

void InitQueue(SqQueue &Q){
    Q.rear=Q.front=0;
}

bool EnQueue(SqQueue &Q,BiTNode* x){
    Q.data[++Q.rear]=x;
    return true;
}

void visit(BiTree T){
    printf("%c ",T->data);
}

void PreOrderTraverse(BiTree T)//二叉树的先序遍历
{
    if(T==NULL)
        return ;
    visit(T);
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}
void InOrderTraverse(BiTree T)//二叉树的中序遍历
{
    if(T==NULL)
        return ;
    InOrderTraverse(T->lchild);
    visit(T);
    InOrderTraverse(T->rchild);
}
void PostOrderTraverse(BiTree T)//后序遍历
{
    if(T==NULL)
        return;
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    visit(T);
}
void CreateBiTree(BiTree &T)
{
    char ch;
    scanf("%c",&ch);
    if(ch=='#')
        T=NULL;
    else
    {
        T=(BiTNode *)malloc(sizeof(BiTNode));
        if(!T)
            return;
        T->data=ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

int treeDepth(BiTree T){
    if (T == NULL)
        return 0;
    else{
        int l= treeDepth(T->lchild);
        int r= treeDepth(T->rchild);
        return l>r ? l+1 : r+1;
    }
}

bool isEmpty(SqQueue Q){
    return Q.rear == Q.front;
}

BiTNode* DeQueue(SqQueue &Q){
    return Q.data[++Q.front];;
}


void LevelOrder(BiTree T,SqQueue Q){
    InitQueue(Q);
    BiTree p;
    EnQueue(Q,T);
    while(!isEmpty(Q)){
        p=DeQueue(Q);
        visit(p);
        if(p->lchild!=NULL) {
            EnQueue(Q, p->lchild);
        }
        if(p->rchild!=NULL) {
            EnQueue(Q, p->rchild);
        }
    }
}

int  InitStack(SqStack &S)//建立栈
{
    S.base = (BiTree *) malloc(STACK_INIT_SIZE * sizeof(BiTree));
    if (!(S.base)) return 0;
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return 0;
}

int Push(SqStack &S,BiTree e)//将元素e插入栈中
{
    if (S.top - S.base >= S.stacksize)
    {
        if(!(S.base = (BiTree*)realloc(S.base, (STACK_INIT_SIZE + STACKINCREMENT) * sizeof(BiTree))))
            return 0;
        S.top = S.base + STACKINCREMENT;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return 0;
}

int Pop(SqStack &S, BiTree &e)//出栈，将栈顶元素赋值给e返回
{
    if (S.base == S.top)
        return false;
    e =*--S.top;
    return 0;
}

int StackEmpty(SqStack &S)//判定栈是否为空
{
    if (S.base == S.top)
    {
        return true;
    }
    else
        return false;
}

int GetTop(SqStack S, BiTree &e)//取栈顶元素赋值给e
{
    if (S.top == S.base) return false;
    e = *(S.top-1);
    return 0;
}

void InOrder(BiTree T){//中序非递归遍历
    SqStack S;
    InitStack(S);
    BiTree p=T;
    while(p||!StackEmpty(S)){
        if(p){
            Push(S,p);
            p=p->lchild;
        } else{
            Pop(S,p);
            visit(p);
            p=p->rchild;
        }
    }
}

void PreOrder(BiTree T){//前序非递归遍历
    SqStack S;
    InitStack(S);
    BiTree p=T;
    while(p||!StackEmpty(S)){
        if(p){
            visit(p);
            Push(S,p);
            p=p->lchild;
        } else{
            Pop(S,p);
            p=p->rchild;
        }
    }
}

void PostOrder(BiTree T){//后序非递归遍历
    SqStack S;
    InitStack(S);
    BiTree p=T,r = NULL;
    while (p||!StackEmpty(S)) {
        if(p){
            Push(S,p);
            p=p->lchild;
        } else {
            GetTop(S, p);
            if (p->rchild && p->rchild != r) {
                p = p->rchild;
                Push(S, p);
                p = p->lchild;
            } else {
                Pop(S, p);
                visit(p);
                r = p;
                p = NULL;
            }
        }
    }
}


int main()
{
    // ABDG##H###CE#I##F##  https://img-blog.csdn.net/20180622225556216?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2RyZWFtMDEzMF9f/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70
    BiTree T;
    SqQueue Q;
    int x;
    InitQueue(Q);
    CreateBiTree(T);
    PreOrderTraverse (T);
    printf("\n");
    InOrderTraverse(T);
    printf("\n");
    PostOrderTraverse(T);
    printf("\n");
    printf("深度:%d\n",treeDepth(T));
    LevelOrder(T,Q);
    printf("\n");
    InOrder(T);
    printf("\n");
    PreOrder(T);
    printf("\n");
    PostOrder(T);
    printf("\n");
    return 0;
}
