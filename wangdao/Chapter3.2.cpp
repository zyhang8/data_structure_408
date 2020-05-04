//
// Created by Yu Zhong. on 2020-05-02.
// 3.2课后习题
//

#include <stdio.h>
#include <stdlib.h>
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

typedef struct {
    ElemType data[MaxSize];
    int top;
} SqStack;

void InitStack(SqStack &S){
    S.top=-1;
}

bool StackEmpty(SqStack S){
    if(S.top==-1)
        return true;
    else
        return false;
}

bool Push(SqStack &S,ElemType x){
    if(S.top==MaxSize-1)
        return false;
    S.data[++S.top]=x;
    return true;
}

bool Pop(SqStack &S,ElemType &x){
    if(S.top==-1)
        return false;
    x=S.data[S.top--];
    return true;
}

bool GetTop(SqStack S,ElemType &x){
    if(S.top==-1)
        return false;
    x=S.data[S.top];
    printf("栈顶元素为:%d\n",x);
    return true;
}

//    3.2.2
bool StackReverse(SqQueue &Q,SqStack S){
    ElemType x;
    while(!isEmpty(Q)){
        DeQueue(Q,x);
        Push(S,x);
    }
    while(isEmpty(Q)){
        x=Pop(S,x);
        EnQueue(Q,x);
    }
}

//    3.2.3
bool StackOverflow(SqStack S){
    if(S.top==MaxSize-1)
        return true;
    return false;
}
bool EnQueue_Stack(SqStack &S,SqStack &S2,ElemType x){
    if(!StackOverflow(S))
        Push(S,x);
    else if(StackOverflow(S)&&!StackEmpty(S2)){
        return false;
    } else{
        while(!StackEmpty(S)){
            Pop(S,x);
            Push(S2,x);
        }
        Push(S,x);
        return true;
    }
}
bool DeQueue_Stack(SqStack &S,SqStack &S2,ElemType &x){
    if(!StackEmpty(S2)){
        Pop(S2,x);
        return true;
    } else if(StackEmpty(S)){
        return false;
    } else{
        while (!StackEmpty(S)){
            Pop(S,x);
            Push(S2,x);
        }
        Pop(S2,x);
    }
}
bool QueueEmpty_Stack(SqStack S,SqStack S2){
    if(StackEmpty(S)&&StackEmpty(S2))
        return true;
    else
        return false;
}

//    3.2.4
//bool CircleEnQuene(SqQueue Q,ElemType x){
//    if(Q.rear->next==Q.front){
//        LinkNode *p=(LinkNode *)malloc(sizeof(LinkNode));
//    }
//    Q.rear->data=x;
//    p->next=Q.rear->next;
//    Q.rear->next=p;
//    Q.rear=p;
//    return true;
//}
//bool CircleDeQuene(SqQueue Q,ElemType &x){
//    if(Q.rear==Q.front){
//        return false;
//    }
//    x=Q.front;
//    Q.front=Q.front->next;
//    return true;
//}


int main(){
    SqQueue Q;
    SqStack S;
    SqStack S2;
    ElemType x;
    InitStack(S);
    InitStack(S2);
    InitQueue(Q);
    isEmpty(Q);
    StackEmpty(S);
    EnQueue(Q,1);
    EnQueue(Q,2);
    EnQueue(Q,3);
    EnQueue(Q,4);
    GetHead(Q,x);
//    DeQueue(Q,x);
//    GetHead(Q,x);
//    3.2.2
//    StackReverse(Q,S);
//    EnQueue_Stack(S,S2,1);
//    EnQueue_Stack(S,S2,2);
//    EnQueue_Stack(S,S2,3);
//    EnQueue_Stack(S,S2,4);
//    DeQueue_Stack(S,S2,x);
//    QueueEmpty_Stack(S,S2);
//    3.2.3
//    CircleEnQuene(Q,1);
//    CircleDeQuene(Q,x);
    GetHead(Q,x);
    return 0;
}
