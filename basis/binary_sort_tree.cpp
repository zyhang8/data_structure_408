//
// Created by Mr. Roy Z. on 2020/8/10.
// Copyright (c) 2020 Yu Zhong. All rights reserved.
// binary_sort_tree.cpp
//

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct BSTNode
{
    ElemType data;
    struct BSTNode *lchild,*rchild;
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

void degree(BSTree T,int &zero,int &one,int &two)//二叉树的先序遍历
{
    if(T==NULL)
        return ;
    degree(T->lchild,zero,one,two);
    if(T->lchild==NULL&&T->rchild==NULL)
        zero++;
    else if((T->lchild!=NULL&&T->rchild==NULL)||(T->rchild!=NULL&&T->lchild==NULL))
        one++;
    else
        two++;
    degree(T->rchild,zero,one,two);
}

int TreeDepth(BSTree T){
    int hl,hr;
    if(T==NULL){
        return 0;
    }
    else{
        hl=TreeDepth(T->lchild);
        hr=TreeDepth(T->rchild);
        if(hl>hr)
            return hl+1;
        else
            return hr+1;
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
    int zero=0,one=0 ,two=0;
    degree(T,zero,one,two);
    printf("0度:%d\n",zero);
    printf("1度:%d\n",one);
    printf("2度:%d\n",two);
    printf("深度:%d",TreeDepth(T));
    return 0;
}
