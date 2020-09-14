//
// Created by Mr. Roy Z. on 2020/8/24.
// Copyright (c) 2020 Yu Zhong. All rights reserved.
// Chapter8.3.cpp
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
typedef enum {RED,WHITE,BLUE} color;

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
        return -1;
    }
//    printf("%d\n",L.data[i-1]);
    return L.data[i-1];
}

//按值查找
int LocateElem(SeqList L,ElemType e){
    for (int i = 0; i < L.length; i++) {
        if(L.data[i]==e) {
            printf("%d\n", i + 1);
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
        printf("%d ",L.data[i]);
    }
    printf("表长为%d\n",L.length);
    return true;
}

void InsertSort(ElemType data[],int n){
    int i,j;
    for (i = 2; i <= n; i++) {
        if(data[i]<data[i-1]){
            data[0]=data[i];
            for (j = i-1; data[0]<data[j]; j--) {
                data[j+1]=data[j];
            }
            data[j+1]=data[0];
        }
    }
    data[0]=0;
}

void BinaryInsertSort(ElemType data[], int n){
    int i,j,low,high,mid;
    for (i = 2; i <= n; i++) {
        data[0]=data[i];
        low=1;
        high=i-1;
        while (low<=high){
            mid=(low+high)/2;
            if(data[0]<data[mid])
                high=mid-1;
            else
                low=mid+1;
        }
        for (j = i-1; j >= low ; j--) {
            data[j+1]=data[j];
        }
        data[j+1]=data[0];
    }
    data[0]=0;
}

void ShellSort(ElemType data[],int n){
    int i,j,d;
    for (d = n/2; d >=1 ; d=d/2) {
        for (i = d+1; i <= n; i++) {
            if(data[i]<data[i-d]){
                data[0]=data[i];
                for (j = i-d; j>0 && data[0]<data[j] ; j=j-d) {
                    data[j+d]=data[j];
                }
                data[j+d]=data[0];
            }
        }
    }
    data[0]=0;
}

void swap(int &n,int &m){
    int temp=n;
    n=m;
    m=temp;
}

void BubbleSort(ElemType data[],int n){
    for (int i = 0; i < n-1; i++) {
        bool flag= false;
        for (int j = n-1; j > i; j--) {
            if(data[j-1]>data[j]){
                swap(data[j-1],data[j]);
                flag= true;
            }
        }
        if (flag == false)
            return;
    }
}

int Partition(ElemType data[],int low,int high){
    int pivot=data[low];
    while(low<high){
        while (low<high&&data[high]>=pivot) high--;
        data[low]=data[high];
        while (low<high&&data[low]<=pivot) low++;
        data[high]=data[low];
    }
    data[low]=pivot;
    return low;
}
void QucikSort(ElemType data[],int low,int high){
    if(low<high){
        int pivotpos=Partition(data,low,high);
        QucikSort(data,low,pivotpos-1);
        QucikSort(data,pivotpos+1,high);
    }
}

///2
void DoubleBubbleSort(ElemType data[],int n){
    bool flag1,flag2;
    int count=0;
    for (int i = 0; i < n-1; i++) {
        flag1= false;
        flag2= false;
        for (int j = n-1; j > i; j--) {
            if(data[j-1]>data[j]){
                swap(data[j-1],data[j]);
                flag1= true;
            }
        }
        for (int j = 0; j < n-i-1; j++) {
            if(data[j]>data[j+1]){
                swap(data[j],data[j+1]);
                flag2= true;
            }
        }
        count++;
        printf("200 %d\n",count);
        if (flag1 == false && flag2== false)
            return;
    }
}

///3
void EvenFront(ElemType data[],int n){
    int low=0,high=n-1;
    while(low<high){
        while(low<high&&data[low]%2!=0) low++;
        while(low<high&&data[high]%2==0) high--;
        if(low<high)
            swap(data[low],data[high]);
        low++;
        high--;
    }
}

///4
int Partition2(ElemType data[],int low,int high){
    int rand_index=low+rand()%(high-low+1);
    swap(data[rand_index],data[low]);
    int pivot=data[low];
    while(low<high){
        while (low<high&&data[high]>=pivot) high--;
        data[low]=data[high];
        while (low<high&&data[low]<=pivot) low++;
        data[high]=data[low];
    }
    data[low]=pivot;
    return low;
}
void QucikSort2(ElemType data[],int low,int high){
    if(low<high){
        int pivotpos=Partition2(data,low,high);
        QucikSort2(data,low,pivotpos-1);
        QucikSort2(data,pivotpos+1,high);
    }
}

///5
int kth_elem(ElemType data[],int n,int k){
    if(k>n)
        return -1;
    for (int i = 0; i < n-1; i++) {
        for (int j = n-1; j > i; j--) {
            if(data[j-1]>data[j]){
                swap(data[j-1],data[j]);
            }
        }
        k--;
        if (k==0)
            return data[i];
    }
    return -1;
}

///6
int setPatition(ElemType data[],int n){
    int pivot,low=0,high=n-1,k=n/2,low0=0,high0=n-1,flag=1,sum1=0,sum2=0;
    while(flag== 1){
        pivot=data[low];
        while(low<high){
            while(low<high&&data[high]>=pivot) high--;
            data[low]=data[high];
            while(low<high&&data[low]<=pivot) low++;
            data[high]=data[low];
        }
        data[low]=pivot;
        if(low==k-1)    flag=0;
        else if(low<k-1){
            low=low+1;
            low0=low;
            high=high0;
        } else{
            high=high-1;
            high0=high;
            low=low0;
        }
    }
    for (int i = 0; i <= low; i++) {
        sum1+=data[i];
    }
    for (int i = low+1; i < n; i++) {
        sum2+=data[i];
    }
    return sum2-sum1;
}

///7
void FlagArrange(ElemType data[],int n){
    int i=0,j=0,k=n-1;
    while (j<=k){
        switch (data[j]){
            case RED:swap(data[j],data[i]);i++;j++;
                break;
            case WHITE:j++;
                break;
            case BLUE:swap(data[j],data[k]);k--;
        }
    }
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
    L.data[0]={0};
    L.data[1]={49};
    ListInsert(L,3,38);
    ListInsert(L,4,65);
    ListInsert(L,5,97);
    ListInsert(L,6,76);
    ListInsert(L,7,13);
    ListInsert(L,8,27);
    ListInsert(L,9,49);
    PrintList(L);
//    InsertSort(L.data,L.length-1);//带哨兵 直接插入排序
//    PrintList(L);
//    BinaryInsertSort(L.data,L.length-1);//带哨兵 直接插入排序
//    PrintList(L);
//    ShellSort(L.data,L.length-1);//希尔排序
//    PrintList(L);
    int x;
    ListDelete(L,1,x);
    PrintList(L);
//    BubbleSort(L.data,L.length);//冒泡排序
//    PrintList(L);
//    QucikSort(L.data,0,L.length-1);//快速排序
//    PrintList(L);
///2
//    DoubleBubbleSort(L.data,L.length);
//    PrintList(L);
    ///3
//    EvenFront(L.data,L.length);
//    PrintList(L);
///4
//    QucikSort2(L.data,0,L.length-1);//快速排序,pivot随机
//    PrintList(L);
///5
//    printf("第5小的元素为%d\n",kth_elem(L.data,L.length,5));
///6
    printf("差值为%d\n",setPatition(L.data,L.length));
    PrintList(L);
    ///7
    L.data[0]={RED};
    L.data[1]={BLUE};
    L.data[2]={WHITE};
    L.data[3]={BLUE};
    L.data[4]={WHITE};
    L.data[5]={RED};
    L.data[6]={BLUE};
    L.data[7]={WHITE};
    PrintList(L);
    FlagArrange(L.data,L.length);
    PrintList(L);
    return 0;
}

