//
// Created by Mr. Yu Zhong. on 2020-05-06.
// Copyright (c) 2020 Yu Zhong. All rights reserved.
// Chapter3.3(2-3).cpp
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

//    3.3.1
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

//    3.3.2
//void Train_Arrange(SqStack S,char train[], int length){
//    char c;
//    int q=0;
//    for (int i = 0; i < length; i++) {
//        if(train[i] == 'H'){
//            Push(S,train[i]);
//            GetTop(S,c);
//        }
//        else{
//            train[q++]=0;
////            GetTop(S,c);
//        }
//    }
//    while (!StateEmpty(S)){
//        Pop(S,c);
//        train[q++]=c;
////        printf("%s",&train[q]);
//    }
//}

//    3.3.3
double P_Calculate(int n,double x){
    if(n==0) return 1;
    struct stack{
        int index;
        double px;
    }st[MaxSize];
    int top=-1;
    double fv1=1,fv2=2*x;
    for (int i = n; i >=2 ; i--) {
        top+=1;
        st[top].index=i;
    }
    while (top>=0){
        st[top].px=2*x*fv2-2*(st[top].index-1)*fv1;
        fv1=fv2;
        fv2=st[top].px;
        top--;
    }
    return fv2;
}

int main(){
    SqStack S;
//    ElemType x;
    InitStack(S);
    StateEmpty(S);
//    Push(S,1);
//    Push(S,2);
//    Push(S,3);
//    GetTop(S,x);
//    Pop(S,x);
//    GetTop(S,x);
//    3.3.1
//    char str[8]={ '{','[','(','[',']',')',']','}'};
//    int length=8;
//    if(CheckBracket(S,str,length))
//        printf("200");
//    3.3.2
//    char train[8]={'H','C','H','C','C','H','H','C'};
//    int length=8;
//    Train_Arrange(S,train,length);
//    3.3.3
//    int n=5;
//    double x=2.1;
//    double px = P_Calculate(n,x);
//    printf("px:%f\n",px);
    return 0;
}
