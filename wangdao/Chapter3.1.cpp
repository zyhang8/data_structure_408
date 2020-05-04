//
// Created by Yu Zhong. on 2020-05-03.
// 3.1课后习题
//

#include <cstdio>

#define MaxSize 50
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
    x=S.data[MaxSize];
    printf("栈顶元素为:%d\n",x);
    return true;
}

//    3.1.3
bool Judge(SqStack S){
    int i=0,j=0;
    while(S.top!=-1) {
        if (S.data[S.top] == 1)
            i++;
        else if (S.data[S.top] == 2) {
            j++;
            if (j > i) return false;
        } else
            return false;
        S.top--;
    }
    if(i==j) {
        printf("200\n");
        return true;
    }
    else {
        printf("error\n");
        return false;
    }
}

//    3.1.4
//    3.1.4
//bool Symmetry(SqStack S,SqStack S2,int n){
//    ElemType x;
//    for (int i = 0; i < n/2; i++) {
//        Pop(S,x);
//        S2.data[++S2.top]=x;
//    }
//    if(n%2==1)
//        Pop(S,x);
//    while (!StateEmpty(S)&&S.data[S.top]==S2.data[S2.top]){
//        Pop(S,x);
//        Pop(S2,x);
//    }
//    if(StateEmpty(S2)){
//        printf("200\n");
//    }
//    else{
//        printf("error\n");
//        return false;
//    }
//}

int main(){
    SqStack S;
    SqStack S2;
    ElemType x;
    InitStack(S);
    InitStack(S2);
    StateEmpty(S);
    Push(S,1);
    Push(S,2);
    Push(S,3);
    Push(S,2);
    Push(S,2);
//    GetTop(S,x);
//    Pop(S,x);
//    GetTop(S,x);
//    3.1.3
//    Judge(S);
//    3.1.4
//    Symmetry(S,S2,5);
    return 0;
}
