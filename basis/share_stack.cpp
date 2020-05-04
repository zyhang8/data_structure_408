//
// Created by Yu Zhong. on 2020-04-27.
//
// 共享栈
//

#include <cstdio>

#define MaxSize 5
typedef int ElemType;
typedef struct {
    ElemType data[MaxSize];
    int top1;
    int top2;
} SqStack;

void InitStack(SqStack &S){
    S.top1=-1;
    S.top2=MaxSize;
}

bool StateEmpty(SqStack S){
    if(S.top1==-1&&S.top2==MaxSize)
        return true;
    else
        return false;
}

bool Push1(SqStack &S,ElemType x){
    if(S.top2-S.top1==1)
        return false;
    S.data[++S.top1]=x;
    return true;
}

bool Push2(SqStack &S,ElemType x){
    if(S.top2-S.top1==1)
        return false;
    S.data[--S.top2]=x;
    return true;
}

bool Pop1(SqStack &S,ElemType &x){
    if(S.top1==-1)
        return false;
    x=S.data[S.top1--];
    return true;
}

bool Pop2(SqStack &S,ElemType &x){
    if(S.top2==MaxSize)
        return false;
    x=S.data[S.top2++];
    return true;
}

bool GetTop1(SqStack S,ElemType &x){
    if(S.top1==-1)
        return false;
    x=S.data[S.top1];
    printf("栈顶1元素为:%d\n",x);
    return true;
}

bool GetTop2(SqStack S,ElemType &x){
    if(S.top2==MaxSize)
        return false;
    x=S.data[S.top2];
    printf("栈顶2元素为:%d\n",x);
    return true;
}

int main(){
    SqStack S;
    ElemType x;
    InitStack(S);
    StateEmpty(S);
    Push1(S,1);
    Push1(S,2);
    Push1(S,3);
    Push2(S,1);
    Push2(S,2);
    GetTop1(S,x);
    GetTop2(S,x);
    Pop1(S,x);
    Pop2(S,x);
    GetTop1(S,x);
    GetTop2(S,x);
    return 0;
}
