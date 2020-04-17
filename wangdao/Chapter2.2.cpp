//
// Created by thinkpad on 2020-04-17.
// 2.2课后习题
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

//初始化
void InitList(SeqList &L){
    for (int i = 0; i < MaxSize; i++) {
        L.data[i]=0;
    }
    L.length=0;
}

//插入
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

//打印表元素及表长
int LocateElem(SeqList L,ElemType e){
    for (int i = 0; i < L.length; i++) {
        if(L.data[i]==e) {
            printf("%d\n", i + 1);
            return i + 1;
        }
    }
    return 0;
}

bool PrintList(SeqList L){
    if(L.length==0){
        printf("表为空\n");
        return false;
    }
    for (int i = 0; i < L.length; i++) {
        printf("第%d个元素为%d\n",i+1,L.data[i]);
    }
    printf("表长为%d\n",L.length);
    return true;
}

//2.2.1
bool Del_Min(SeqList &L,ElemType &value){
    if(L.length==0)
        return false;
    int pos=0;
    value=L.data[0];
    for (int i = 1; i < L.length; i++) {
        if (L.data[i] < value) {
            value = L.data[i];
            pos = i;
        }
    }
    L.data[pos]=L.data[L.length-1];
    L.length--;
    return true;
}

//2.2.2
void Reverse(SeqList &L){
    ElemType temp;
    for (int i = 0; i < L.length/2; i++) {
        temp = L.data[i];
        L.data[i] = L.data[L.length-i-1];
        L.data[L.length-i-1]=temp;
    }
}

//2.2.3
void Del_x(SeqList &L,ElemType x){
    int k=0;
    for (int i = 0; i < L.length; i++) {
        if(L.data[i]!=x){
            L.data[k]=L.data[i];
            k++;
        }
    }
    L.length=k;
};

//2.2.4
bool Del_s_t(SeqList &L,ElemType s,ElemType t){
    if(s>=t||L.length==0)
        return false;
    int i,j;
    for(i=0;i<L.length&&L.data[i]<s;i++);
    if(i>=L.length)
        return false;
    for (j = i; L.data[j]<=t&&j<L.length; j++);
    for (; j<L.length; i++,j++) {
        L.data[i]=L.data[j];
    }
    L.length=i;
    return true;
};

//2.2.5
bool Del_s_t2(SeqList &L,ElemType s,ElemType t){
    if(s>=t||L.length==0)
        return false;
    int k=0;
    for (int i = 0; i < L.length; i++) {
        if(L.data[i]<s||L.data[i]>t){
            L.data[k]=L.data[i];
            k++;
        }
    }
    L.length=k;
}

//2.2.6
bool Del_dup(SeqList &L){
    if(L.length==0)
        return false;
    int k=1;
    for (int i = 1; i < L.length; i++) {
        if(L.data[i]!=L.data[i-1]){
            L.data[k]=L.data[i];
            k++;
        }
    }
    L.length=k;
}

//2.2.7
bool Merge(SeqList &L,SeqList &B,SeqList &C){
    if(L.length+B.length>MaxSize){
        return false;
    }
    int i=0,j=0,k=0;
    while(i<L.length&&j<B.length){
        if(L.data[i]<B.data[j])
            C.data[k++]=L.data[i++];
        else
            C.data[k++]=B.data[j++];
    }
    while(i<L.length)
        C.data[k++]=L.data[i++];
    while(j<B.length)
        C.data[k++]=B.data[j++];
    C.length=k;
    return true;
}

//2.2.8、2.2.10
void Reverse_m_n(SeqList &L,int left,int right){
    if(left>=right)
        return;
    ElemType temp;
    int mid= (right+left+1)/2;
    for (int i = left; i < mid; i++) {
        temp = L.data[i];
        L.data[i] = L.data[left+right-i];
        L.data[left+right-i]=temp;
    }
}
void Exchange(SeqList &L,int m,int n){
    Reverse_m_n(L,0,m+n-1);
    Reverse_m_n(L,0,n-1);
    Reverse_m_n(L,n,n+m-1);
}

//2.2.11
ElemType M_Search(SeqList L,SeqList B){
    if(L.length+B.length<2)
        return 0;
    int pos=(L.length+B.length)/2;
    ElemType value = 0;
    int i=0,j=0,k=0;
    while(k<pos){
        if(L.data[i]<B.data[j]){
            value=L.data[i++];
        } else{
            value=B.data[j++];
        }
        k++;
    }
//    printf("%d\n",value);
    return value;
}

//2.2.12
int Majority(SeqList L){
    ElemType sort[L.length];
    for (int i = 0; i < L.length; i++) {
        sort[i]=0;
    }
    for (int j = 0; j < L.length; j++) {
        sort[L.data[j]]+=1;
    }
    ElemType max=sort[0];
    for (int k = 1; k < L.length; k++) {
        if(sort[k]>max)
            max=sort[k];
    }
    if(max>L.length/2) {
//        printf("%d\n", max);
        return max;
    }
    else
        return -1;
}

//
int findMissMin(SeqList L){
    ElemType sort[L.length];
    for (int i = 0; i < L.length; i++) {
        sort[i]=0;
    }
    for (int j = 0; j < L.length; j++) {
        if(L.data[j]>0){
            sort[L.data[j]-1]=1;
        }
    }
    int k;
    for ( k = 1; k < L.length; k++){
        if(sort[k]==0){
            break;
        }
    }
    printf("%d\n",k+1);
    return k+1;
}

int main(){
    SeqList L,B,C;
    InitList(L);
    InitList(B);
    InitList(C);
//    PrintList(L);

//    ListInsert(L,1,1);
//    ListInsert(B,1,2);
//    ListInsert(L,2,3);
//    ListInsert(B,2,4);
//    ListInsert(L,3,5);
//    ListInsert(B,3,6);
//    ListInsert(L,4,7);
//    ListInsert(B,4,10);
//    ListInsert(L,5,9);
//    ListInsert(B,5,12);

    //test
    ListInsert(L,1,1);
    ListInsert(B,1,2);
    ListInsert(L,2,2);
    ListInsert(B,2,4);
    ListInsert(L,3,5);
    ListInsert(B,3,6);
    ListInsert(L,4,3);
    ListInsert(B,4,10);
    ListInsert(L,5,9);
    ListInsert(B,5,12);

//    2.2.1
//    ElemType value;
//    Del_Min(L,value);
//    2.2.2
//    Reverse(L);
//    2.2.3
//    Del_x(L,5);
//    2.2.4
//    Del_s_t(L,3,5);
//    2.2.5
//    Del_s_t2(L,3,11);
//    2.2.6
//    Del_dup(L);
//    2.2.7
//    Merge(L,B,C);
//    PrintList(C);
//    2.2.8、2.2.10
//    Merge(L,B,C);
//    PrintList(C);
//    Exchange(C,4,6);
//    PrintList(C);
//    2.2.11
//    printf("%d\n",M_Search(L,B));
//    2.2.12
//    Majority(L);
//    2.3.13
    findMissMin(L);
    return 0;
}

