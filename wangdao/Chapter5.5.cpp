//
// Created by Mr. Roy Z. on 2020/8/10.
// Copyright (c) 2020 Yu Zhong. All rights reserved.
// Chapter5.5.cpp
//


#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct BSTNode
{
    ElemType data;
    struct BSTNode *lchild,*rchild;
    int count;
}BSTNode,*BSTree;

bool BST_Insert(BSTree &T,ElemType e){
    if(T==NULL){
        T=(BSTree)malloc(sizeof(BSTNode));
        T->data=e;
        T->lchild=T->rchild=NULL;
        return true;
    }
    if(T->data==e)
        return false;
    else if(T->data<e)
        return BST_Insert(T->rchild,e);
    else
        return BST_Insert(T->lchild,e);
}

void CreateBSTree(BSTree &T,ElemType *num,int n){
    T=NULL;
    for (int i = 0; i < n; i++) {
        BST_Insert(T,num[i]);
    }
}

bool BST_Search(BSTree T,ElemType e){
    while(T!=NULL&&T->data!=e){
        if(e<T->data) T=T->lchild;
        else T=T->rchild;
    }
    if(T==NULL)
        return false;
    else
        return true;
}

void visit(BSTree T){
    printf("%d ",T->data);
}

void PreOrderTraverse(BSTree T)//二叉树的先序遍历
{
    if(T==NULL)
        return ;
    PreOrderTraverse(T->lchild);
    visit(T);
    PreOrderTraverse(T->rchild);
}

///6
ElemType temp=-32767;
bool BST_Judge(BSTree T){
    bool b1,b2;
    if(T==NULL)
        return true;
    else{
        b1=BST_Judge(T->lchild);
        if(!b1||temp>=T->data)
            return false;
        b2=BST_Judge(T->rchild);
        return b2;
    }
}

///7
int BSTnodeLevel(BSTree T,BSTNode *p){
    int i=0;
    while(T!=NULL&&T->data!=p->data){
        if(p->data<T->data) T=T->lchild;
        else T=T->rchild;
        i++;
    }
    if(T==NULL)
        return 0;
    else
        return i+1;
}

///8
bool AVL_Judge(BSTree T,int &heigh){
    int hl,hr;
    bool bl,br;
    if(T==NULL){
        heigh=0;
        return true;
    }
    else if(T->lchild==NULL&&T->rchild==NULL){
        heigh=1;
        return true;
    }
    else{
        bl=AVL_Judge(T->lchild,hl);
        br=AVL_Judge(T->rchild,hr);
        if(hl>hr)
            heigh=hl;
        else
            heigh=hr;
        if(abs(hl-hr)<2)
            return bl&&br;
        else
            return false;
    }
}
///9
int BST_Max(BSTree T){
    while(T->lchild!=NULL){
        T=T->lchild;
    }
    return T->data;
}
int BST_Min(BSTree T){
    while(T->rchild!=NULL){
        T=T->rchild;
    }
    return T->data;
}
///10
void Reorder_k(BSTree T,int k)//二叉树的先序遍历
{
    if(T==NULL)
        return ;
    Reorder_k(T->rchild,k);
    if(T->data>=k)
        visit(T);
    Reorder_k(T->lchild,k);
}
///11
void Count(BSTree T,int *count,int &i)//二叉树的先序遍历
{
    if(T==NULL)
        return ;
    Count(T->lchild,count,i);
    T->count=count[i];
    printf("%d ",T->count);
    i++;
    Count(T->rchild,count,i);
}
BSTNode *Search_k_min(BSTree T,int k){
    if(k<1||k>T->count)
        return NULL;
    if(T->lchild==NULL){
        if(k==1) return T;
        else return Search_k_min(T->rchild,k-1);
    } else{
        if(T->lchild->count==k-1) return T;
        else if(T->lchild->count>k-1) return Search_k_min(T->lchild,k);
        else
            return Search_k_min(T->rchild,k-T->lchild->count-1);
    }
}

int main()
{
    BSTree T;
    ElemType num[10]= {5,2,7,6,3,1,9,4,10,8};
    CreateBSTree(T,num,10);
    PreOrderTraverse(T);
    printf("\n");
    if(BST_Search(T,11))
        printf("200\n");
    else
        printf("404\n");
    ///6
    if(BST_Judge(T))
        printf("yes\n");
    else
        printf("no\n");
    ///7
    BSTNode *p=T->lchild->rchild;
    printf("%d\n",BSTnodeLevel(T,p));
    ///8
    int heigh=0;
    if(AVL_Judge(T,heigh))
        printf("TES\n");
    else
        printf("NO\n");
    ///9
    printf("最大值:%d\n",BST_Max(T));
    printf("最小值:%d\n",BST_Min(T));
    ///10
    Reorder_k(T,4);
    printf("\n");
    ///11
    int count[10]= {1,4,2,1,10,5,4,1,3,1};
    int i=0;
    Count(T,count,i);
    printf("\n");
    BSTNode *k=Search_k_min(T,4);
    printf("%d\n",k->data);
    return 0;
}
