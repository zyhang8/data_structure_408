//
// Created by thinkpad on 2020-04-27.
// Ë³ÐòÕ»
//

#include <cstdio>

#define MaxSize 50;
typedef int ElemType;
typedef struct {
    ElemType data[MaxSize];
    int top;
} SqStack;

void InitStack(SqStack &S){
    S.top=-1;
}

bool StateEmpty(SqStack S){
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
    printf("Õ»¶¥ÔªËØÎª:%d\n",x);
    return true;
}

int main(){
    SqStack S;
    ElemType x;
    InitStack(S);
    StateEmpty(S);
    Push(S,1);
    Push(S,2);
    Push(S,3);
    GetTop(S,x);
    Pop(S,x);
    GetTop(S,x);
    return 0;
}
