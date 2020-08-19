//
// Created by Mr. Yu Zhong. on 2020-05-07.
// Copyright (c) 2020 Yu Zhong. All rights reserved.
// Chapter3.3(4).cpp
//

#include <cstdio>
#include <cstdlib>
#define MaxSize 50

typedef int ElemType;
typedef struct {
    ElemType data[MaxSize];
    int front,rear;
    int size;
    int tag;
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

//    3.3.4
bool HarberArrange(SqQueue &Q,SqQueue c,SqQueue t){
    int i=0,j=0;
    ElemType x;
    while(j<10){
        if(!isEmpty(c)&&i<4) {
            DeQueue(c,x);
            EnQueue(Q,x);
            j++;
            i++;
        }
        else if(isEmpty(t)&&i<4){
            DeQueue(t,x);
            EnQueue(Q,x);
            j++;
            i=0;
        }
        else if(isEmpty(c)&&isEmpty(t))
            return false;
        else{
            while(isEmpty(c)&&i<4){
                DeQueue(t,x);
                EnQueue(Q,x);
                j++;
                i++;
            }
            i=0;
        }
    }
    return true;
}

int main(){
    SqQueue Q;
    SqQueue c;
    SqQueue t;
    int x;
    InitQueue(Q);
    InitQueue(c);
    InitQueue(t);
    isEmpty(Q);
    EnQueue(c,1);
    EnQueue(c,2);
    EnQueue(c,3);
    EnQueue(t,4);
    GetHead(Q,x);
//    DeQueue(Q,x);
//    GetHead(Q,x);
//    HarberArrange(Q,c,t);
//    EnQueue(c,1);
//    EnQueue(c,2);
//    EnQueue(c,3);
//    EnQueue(t,4);
//    HarberArrange(Q,c,t);
//    GetHead(Q,x);
    return 0;
}