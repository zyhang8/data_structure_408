//
// Created by Yu Zhong. on 2020-05-02.
// 顺序队列
//

#include <stdio.h>
#include <stdlib.h>
#define MaxSize 50

typedef int ElemType;
typedef struct {
    ElemType data[MaxSize];
    int front,rear;
    int size; //数量大小
    int tag; //标记队不空还是队空
} SqQueue;

void InitQueue(SqQueue &Q){
    Q.rear=Q.front=0;
    Q.size=0;
    Q.tag=0;
}

bool isEmpty(SqQueue Q){
    if(Q.rear==Q.front&&Q.size==0&&Q.tag==0) return true;
    else return false;
}
bool EnQueue(SqQueue &Q,ElemType x){
    if((Q.rear+1)%MaxSize==Q.front&&Q.size==MaxSize&&(Q.tag==1&&Q.rear==Q.front))
        return false;
    Q.data[Q.rear]=x;
    Q.rear=(Q.rear+1)%MaxSize;
    Q.size++;
    Q.tag=1;
    return true;
}

bool DeQueue(SqQueue &Q,ElemType &x){
    if(Q.front&&Q.rear&&Q.size==0&&Q.tag==0)
        return false;
    x=Q.data[Q.front];
    Q.front=(Q.front+1)%MaxSize;
    Q.size--;
    if(Q.rear==Q.front)
        Q.tag=0;
    return true;
}

bool GetHead(SqQueue Q,ElemType &x){
    if(Q.front==Q.rear&&Q.size==0)
        return false;
    x=Q.data[Q.front];
    printf("%d\n",x);
    return true;
}
int main(){
    SqQueue Q;
    int x;
    InitQueue(Q);
    isEmpty(Q);
    EnQueue(Q,1);
    EnQueue(Q,2);
    EnQueue(Q,3);
    EnQueue(Q,4);
    GetHead(Q,x);
    DeQueue(Q,x);
    GetHead(Q,x);
    return 0;
}