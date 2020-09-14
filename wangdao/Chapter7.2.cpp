//
// Created by Mr. Roy Z. on 2020/8/23.
// Copyright (c) 2020 Yu Zhong. All rights reserved.
// Chapter7.2.cpp
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

//��ʼ��
void InitList(SeqList &L){
    L.data=(ElemType *)malloc(InitSize* sizeof(ElemType));
    L.length=0;
    L.MaxSize=InitSize;
}

//���Ӷ�̬����ĳ���
void IncreaseSize(SeqList &L,int len){
    ElemType *p=L.data;
    L.data=(ElemType *)malloc((L.MaxSize+len)* sizeof(ElemType));
    for (int i = 0; i < L.length; i++) {
        L.data[i]=p[i];
    }
    L.MaxSize=L.MaxSize+len;
    free(p);
}

//����
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
        return -1;
    }
//    printf("%d\n",L.data[i-1]);
    return L.data[i-1];
}

//��ֵ����
int LocateElem(SeqList L,ElemType e){
    for (int i = 0; i < L.length; i++) {
        if(L.data[i]==e) {
//            printf("%d\n", i + 1);
            return i + 1;
        }
    }
    return -1;
}

//��ӡ��Ԫ�ؼ���
bool PrintList(SeqList L){
    if(L.length==0){
        printf("��Ϊ��");
        return false;
    }
    for (int i = 0; i < L.length; i++) {
        printf("��%d��Ԫ��Ϊ%d\n",i,L.data[i]);
    }
    printf("��Ϊ%d\n",L.length);
    return true;
}

int Search_Seq(SeqList L,int x){
    ListInsert(L,1,x);
    PrintList(L);
    int i;
    for (i = L.length-1; L.data[i]!=x ; i--);
    return i;
}

int Binary_Search(SeqList L,int x){
    int low=0,high=L.length-1,mid;
    while(low<=high){
        mid=(low+high)/2;
        if(L.data[mid]==x)
            return mid;
        else if(L.data[mid]<x)
            low=mid+1;
        else
            high=mid-1;
    }
    return -1;
}

int Binary_Search_Rec(SeqList L,int x,int low,int high){
    if(low>high)
        return 0;
    int mid=(low+high)/2;
    if(L.data[mid]==x)
        return mid;
    else if(L.data[mid]<x)
        Binary_Search_Rec(L,x,mid+1,high);
    else
        Binary_Search_Rec(L,x,low,mid-1);
}

int Search_Exchange(SeqList &L,int x){
    int i=0;
    while(L.data[i]!=x&&i<L.length-1)
        i++;
    if(i<L.length-1&&i>0){
        int temp=L.data[i];
        L.data[i]=L.data[i-1];
        L.data[i-1]=temp;
        return --i;
    } else
        return -1;
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
    ListInsert(L,2,2);
    if(LocateElem(L,3)>0)
        printf("�ҵ�ֵΪ%d,�ڵ�%dλ\n",3,LocateElem(L,3));
    else
        printf("��ֵΪ%d����\n",3);
    PrintList(L);
    IncreaseSize(L,5);
    ListInsert(L,4,4);
    ListInsert(L,5,5);
    ListInsert(L,6,6);
    ListInsert(L,7,7);
    ListInsert(L,8,8);
    ListInsert(L,9,9);
    ListInsert(L,10,10);
    PrintList(L);
//    ListInsert(L,1,11);
//    PrintList(L);
    int seatch_seq=Search_Seq(L,11);
    if(seatch_seq!=0)//�ڱ�����
        printf("�ҵ�ֵΪ%d,�ڵ�%dλ\n",11,seatch_seq);
    else
        printf("��ֵΪ%d����\n",11);
    L.data[0]=0;
    PrintList(L);
    if(Binary_Search(L,11)>=0)//�۰���ҷ�
        printf("�ҵ�ֵΪ%d,�ڵ�%dλ\n",1,Binary_Search(L,11));
    else
        printf("��ֵΪ%d����\n",11);
    printf("�ҵ�ֵΪ%d,�ڵ�%dλ\n",4,Binary_Search_Rec(L,4,1,L.length));
    Search_Exchange(L,2);
    PrintList(L);
    return 0;
}
