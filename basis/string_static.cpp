//
// Created by Mr. Roy Z. on 2020-05-17.
// Copyright (c) 2020 Roy Z. All rights reserved.
// string_static.cpp
//

#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 255

using namespace std;
typedef struct{
    char ch[MAXLEN];
    int length;
}SString;


void InitString(SString &S){
    for (int i = 1; i <= MAXLEN; i++) {
        S.ch[i]=0;
    }
    S.length=0;
}

bool StrEmpty(SString S){
    if (S.length==0)
        return true;
    else
        return false;
}

bool ListInsert(SString &S,int i,char e){
    if(i<1||i>S.length+1){
        return false;
    }
    if(S.length>=MAXLEN-1){
        return false;
    }
    for (int j = S.length+1; j > i; j--) {
        S.ch[j]=S.ch[j-1];
    }
    S.ch[i]=e;
    S.length++;
    return true;
}

int StrLength(SString S){
    printf("表长为%d\n",S.length);
    return S.length;
}

void StrCopy(SString &T,SString S){
    for (int i = 1; i <= S.length;i++) {
        T.ch[i]=S.ch[i];
    }
    T.length=S.length;
}

void StrAssign(SString T,char chars[]){
    for (int i = 1; i <= T.length; i++) {
        chars[i-1]=T.ch[i];
        printf("第%d个元素为%c\n",i,chars[i-1]);
    }
}

bool SubString(SString &Sub,SString S,int pos,int len){
    if(pos+len-1>S.length)
        return false;
    for (int i = pos; i < pos+len; i++) {
        Sub.ch[i-pos+1]=S.ch[i];
    }
    Sub.length=len;
    return true;
}

int StrCompare(SString S,SString T){
    for (int i = 1; i <= S.length && i<=T.length; i++) {
        if(S.ch[i]!=T.ch[i])
            return S.ch[i]-T.ch[i];
    }
    return S.length-T.length;
}

void Concat(SString &T,SString S1,SString S2){
    if(S1.length==0&&S2.length==0)
        return;
    else if(S1.length==0&&S2.length!=0){
        StrCopy(T,S2);
        T.length=S2.length;
    }
    else if(S1.length!=0&&S2.length==0){
        StrCopy(T,S1);
        T.length=S1.length;
    } else{
        StrCopy(T,S1);
        for (int i = S1.length+1; i <= S1.length+S2.length; i++) {
            T.ch[i]=S2.ch[i-S1.length];
        }
        T.length=S1.length+S2.length;
    }
}

int Index(SString S,SString T){
    int i=1,m=StrLength(S),n=StrLength(T);
    SString Sub;
    while(i<=m-n+1){
        SubString(Sub,S,i,n);
        if(StrCompare(Sub,T)!=0)    i++;
        else return i;
    }
    return 0;
}

void get_next(SString T,int next[]){
    int i=1,j=0;
    next[1]=0;
    while(i<T.length){
        if(j==0||T.ch[j]==T.ch[i]){
            i++;
            j++;
            next[i]=j;
        } else{
            j=next[j];
        }
    }
}

void get_nextval(SString T,int nextval[]){
    nextval[1]=0;
    int next[T.length+1];
    get_next(T,next);
    for (int j = 2; j <= T.length; j++) {
        if(T.ch[next[j]]==T.ch[j]){
            nextval[j]=nextval[next[j]];
        } else{
            nextval[j]=next[j];
        }
    }
}

int Index_KMP(SString S,SString T){
    int i=1,j=1;
    int next[T.length+1];
    get_next(T,next);
    while(i<=S.length&&j<=T.length){
        if(j==0||S.ch[i]==T.ch[j]){
            i++;
            j++;
        } else{
            j=next[j];
        }
    }
    if(j>T.length)
        return i-T.length;
    else
        return 0;
}

int Index_KMPVAL(SString S,SString T){
    int i=1,j=1;
    int nextval[T.length+1];
    get_nextval(T,nextval);
    while(i<=S.length&&j<=T.length){
        if(j==0||S.ch[i]==T.ch[j]){
            i++;
            j++;
        } else{
            j=nextval[j];
        }
    }
    if(j>T.length)
        return i-T.length;
    else
        return 0;
}

void ClearString(SString &S){
    for (int i = 1; i <= S.length; i++) {
        S.ch[i]=0;
    }
    S.length=0;
}

bool PrintList(SString S){
    if(S.length==0){
        printf("表为空\n");
        return false;
    }
    for (int i = 1; i <= S.length; i++) {
        printf("第%d个元素为%c\n",i,S.ch[i]);
    }
    return true;
}

int main(){
    SString S;
    SString T;
    SString Sub;
    SString C;
    char chars[MAXLEN];
    InitString(S);
    InitString(T);
    InitString(Sub);
    InitString(C);
    ListInsert(S,1,'a');
    ListInsert(S,2,'b');
    ListInsert(S,3,'c');
    StrEmpty(S);
    StrLength(S);
    PrintList(S);
//    StringLength
    StrCopy(T,S);
    PrintList(T);
    StrAssign(T,chars);
    SubString(Sub,S,2,2);
    PrintList(Sub);
    printf("比较差为%d\n",StrCompare(S,T));
    Concat(C,S,Sub);
    PrintList(C);
    printf("简单模式子串在主串的位置为%d\n",Index(S,Sub));
    printf("KMP子串在主串的位置为%d\n",Index_KMP(S,Sub));
    printf("优化KMP子串在主串的位置为%d\n",Index_KMPVAL(S,Sub));
    ClearString(S);
    PrintList(S);
//    DestroyString(S);
    return 0;
}
