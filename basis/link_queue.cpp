//
// Created by Yu Zhong. on 2020-05-02.
// 链队
//

#include <stdio.h>
#include <stdlib.h>

using namespace std;
typedef int ElemType;

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

bool GetHead(LinkQueue Q,ElemType &x){
    if(Q.rear==Q.front)
        return false;
    x=Q.front->next->data;
    printf("%d\n",x);
    return true;
}

int main(){
    LinkQueue Q;
    ElemType x;
    InitQueue(Q);
    isEmpty(Q);
    EnQueue(Q,1);
    EnQueue(Q,2);
    EnQueue(Q,3);
    GetHead(Q,x);
    DeQueue(Q,x);
    GetHead(Q,x);
    return 0;
}