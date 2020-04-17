//
// Created by thinkpad on 2020-04-16.
// ˳���(��̬����)
//


#include <stdio.h>
#include <stdlib.h>
#define MaxSize 50

using namespace std;
typedef int ElemType;
typedef struct{
    ElemType data[MaxSize];
    int length;
}SeqList;

//��ʼ��
void InitList(SeqList &L){
    for (int i = 0; i < MaxSize; i++) {
        L.data[i]=0;
    }
    L.length=0;
}

//����
bool ListInsert(SeqList &L,int i,ElemType e){
    if(i<1||i>L.length+1){
        return false;
    }
    if(L.length>=MaxSize){
        return false;
    }
    for (int j = L.length; j >= i; j--) {
        L.data[j]=L.data[j-1];
    }
    L.data[i-1]=e;
    L.length++;
    return true;
}

//ɾ��
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

//��λ����
ElemType GetElem(SeqList L,int i){
    if(i<1||i>L.length){
        return NULL;
    }
//    printf("%d\n",L.data[i-1]);
    return L.data[i-1];
}

//��ֵ����
int LocateElem(SeqList L,ElemType e){
    for (int i = 0; i < L.length; i++) {
        if(L.data[i]==e) {
            printf("%d\n", i + 1);
            return i + 1;
        }
    }
    return 0;
}

//��ӡ��Ԫ�ؼ���
bool PrintList(SeqList L){
    if(L.length==0){
        printf("��Ϊ��");
        return false;
    }
    for (int i = 0; i < L.length; i++) {
        printf("��%d��Ԫ��Ϊ%d\n",i+1,L.data[i]);
    }
    printf("��Ϊ%d\n",L.length);
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
        printf("ɾ����2��Ԫ��--%d\n",e);
    else
        printf("error\n");
//    GetElem(L,2);
    LocateElem(L,3);
    PrintList(L);
    return 0;
}
