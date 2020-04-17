//
// Created by thinkpad on 2020-04-17.
// 顺序表(动态分配)
//


#include <stdio.h>
#include <stdlib.h>
#define InitSize 10

using namespace std;
typedef int ElemType;

typedef struct{
    ElemType *data;
    int MaxSize;
    int length;
}SeqList;

//初始化
void InitList(SeqList &L){
    L.data=(ElemType *)malloc(InitSize* sizeof(ElemType));
    L.length=0;
    L.MaxSize=InitSize;
}

//增加动态数组的长度
void IncreaseSize(SeqList &L,int len){
    ElemType *p=L.data;
    L.data=(ElemType *)malloc((L.MaxSize+len)* sizeof(ElemType));
    for (int i = 0; i < L.length; i++) {
        L.data[i]=p[i];
    }
    L.MaxSize=L.MaxSize+len;
    free(p);
}

//插入
bool ListInsert(SeqList &L,int i,ElemType e){
    if(i<1||i>L.length+1){
        return false;
    }
    if(L.length>=L.MaxSize){
        return false;
    }
    for (int j = L.length; j >= i; j--) {
        L.data[j]=L.data[j-1];
    }
    L.data[i-1]=e;
    L.length++;
    return true;
}

//删除
bool ListDelete(SeqList &L,int i,ElemType &e){
    if(i<1||i>L.length){
        return false;
    }
    e=L.data[i-1];
    for (int j = i; j < L.length; j++) {
        L.data[j-1]=L.data[j];
    }
    L.length--;
    return true;
}

//按位查找
ElemType GetElem(SeqList L,int i){
    if(i<1||i>L.length){
        return NULL;
    }
//    printf("%d\n",L.data[i-1]);
    return L.data[i-1];
}

//按值查找
int LocateElem(SeqList L,ElemType e){
    for (int i = 0; i < L.length; i++) {
        if(L.data[i]==e) {
//            printf("%d\n", i + 1);
            return i + 1;
        }
    }
    return 0;
}

//打印表元素及表长
bool PrintList(SeqList L){
    if(L.length==0){
        printf("表为空");
        return false;
    }
    for (int i = 0; i < L.length; i++) {
        printf("第%d个元素为%d\n",i+1,L.data[i]);
    }
    printf("表长为%d\n",L.length);
    return true;
}

int main(){
    SeqList L;
    InitList(L);
//    PrintList(L);
    ListInsert(L,1,1);
    ListInsert(L,2,2);
    ListInsert(L,3,3);
//    PrintList(L);
    ElemType e=-1;
    if(ListDelete(L,2,e))
        printf("删除第2个元素--%d\n",e);
    else
        printf("error\n");
//    GetElem(L,2);
    LocateElem(L,3);
    PrintList(L);
    IncreaseSize(L,5);
    return 0;
}
