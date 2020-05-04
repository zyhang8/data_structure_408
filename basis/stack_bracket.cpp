//
// Created by Mr. Yu Zhong. on 2020-05-04.
// Copyright (c) 2020 Yu Zhong. All rights reserved.
// stack_bracket.cpp
//

#include <cstdio>

#define MaxSize 50
typedef char ElemType;
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
    printf("Õ»¶¥ÔªËØÎª:%s\n",&x);
    return true;
}

bool CheckBracket(SqStack S,char str[], int length){
    ElemType p;
    for (int i = 0; i < length; i++) {
        if(str[i] == '[' || str[i] == '{' || str[i] == '('){
            Push(S,str[i]);
//            GetTop(S,p);
        }
        else{
            if(StateEmpty(S))
                return false;
            ElemType x;
            Pop(S,x);
            if(str[i]==')' && x!='(')
                return false;
            if(str[i]==']' && x!='[')
                return false;
            if(str[i]=='}' && x!='{')
                return false;
//            GetTop(S,p);
        }
    }
    return StateEmpty(S);
}

int main(){
    SqStack S;
    ElemType x;
    InitStack(S);
    StateEmpty(S);
//    Push(S,1);
//    Push(S,2);
//    Push(S,3);
//    GetTop(S,x);
//    Pop(S,x);
//    GetTop(S,x);
    char str[8]={ '{','[','(','[',']',')',']','}'};
    int length=8;
    if(CheckBracket(S,str,length))
        printf("200");
    return 0;
}
