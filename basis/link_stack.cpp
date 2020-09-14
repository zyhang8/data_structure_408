//
// Created by Yu Zhong. on 2020-04-27.
// Á´Õ»
//
#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct Linknode{
    ElemType data;
    struct Linknode *next;
} Linknode, *LiStack;

void InitStack(LiStack &S){
    S=NULL;
}

bool StackEmpty(LiStack S){
    if(S==NULL)
        return true;
    else
        return false;
}

bool Push(LiStack &S,ElemType x){
    Linknode *s = (Linknode *)malloc(sizeof(Linknode));
    s->data=x;
    if(S==NULL){
        S=s;
        S->next=NULL;
        return true;
    }
    s->next=S;
    S=s;
    return true;
}

bool Pop(LiStack &S,ElemType &x){
    if(S->next==NULL){
        x=S->data;
        S=NULL;
        return true;
    }
    Linknode *p;
    p=S;
    x=S->data;
    S=S->next;
    free(p);
    return true;
}

bool GetTop(LiStack S,ElemType &x){
    if(S==NULL)
        return false;
    else {
        x = S->data;
        printf("Õ»¶¥Îª:%d\n",x);
        return true;
    }
}

int main(){
    LiStack S;
    ElemType x;
    InitStack(S);
    StackEmpty(S);
    Push(S,1);
    Push(S,2);
    Push(S,3);
    GetTop(S,x);
    Pop(S,x);
    GetTop(S,x);
    return 0;
}
