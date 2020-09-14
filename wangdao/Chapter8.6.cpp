//
// Created by Mr. Roy Z. on 2020/8/25.
// Copyright (c) 2020 Yu Zhong. All rights reserved.
// Chapter8.6.cpp

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

void SelectSort(ElemType data[],int n){
    int min;
    for (int i = 0; i < n-1; i++) {
        min=i;
        for (int j = i+1; j < n; j++) {
            if(data[j]<data[min])
                min=j;
        }
        if(min!=i)
            swap(data[min],data[i]);
    }
}

void HeapAdjust(ElemType data[],int k,int n){
    data[0]=data[k];
    for (int i = 2*k; i <= n; i=i*2) {
        if(i<n&&data[i]<data[i+1])
            i++;
        if(data[0]>=data[i])
            break;
        else{
            data[k]=data[i];
            k=i;
        }
    }
    data[k]=data[0];
    data[0]=0;
}
void BuildMaxHeap(ElemType data[],int n){
    for (int i = n/2; i >= 1; i--) {
        HeapAdjust(data,i,n);
    }
}
void HeapSort(ElemType data[],int n){
    BuildMaxHeap(data,n);
    for (int i = n; i > 1; i--) {
        swap(data[i],data[1]);
        HeapAdjust(data,1,i-1);
    }
}

void HeapMinAdjust(ElemType data[],int k,int n){
    data[0]=data[k];
    for (int i = 2*k; i <= n; i=i*2) {
        if(i<n&&data[i]>data[i+1])
            i++;
        if(data[0]<=data[i])
            break;
        else{
            data[k]=data[i];
            k=i;
        }
    }
    data[k]=data[0];
    data[0]=0;
}
void BuildMinHeap(ElemType data[],int n){
    for (int i = n/2; i >= 1; i--) {
        HeapMinAdjust(data,i,n);
    }
}
void HeapSortMin(ElemType data[],int n){
    BuildMinHeap(data,n);
    for (int i = n; i > 1; i--) {
        swap(data[i],data[1]);
        HeapMinAdjust(data,1,i-1);
    }
}

ElemType *B=(ElemType *)malloc(8* sizeof(ElemType));
void Merge(ElemType data[],int low,int mid,int high){
    for (int i = low; i <= high; i++) {
        B[i]=data[i];
    }
    int i,j,k;
    for (i = low,j=mid+1,k=i; i <= mid&& j<= high; k++) {
        if(B[i]<=B[j])
            data[k]=B[i++];
        else
            data[k]=B[j++];
    }
    while(i<=mid)   data[k++]=B[i++];
    while(j<=high)   data[k++]=B[j++];
}
void MergeSort(ElemType data[],int low,int high){
    int mid=(low+high)/2;
    if(low<high){
        MergeSort(data,low,mid);
        MergeSort(data,mid+1,high);
        Merge(data,low,mid,high);
    }
}

///2
void Insert_Sort(ElemType data[],int m,int n){
    int j;
    for (int i = m+1; i <= m+n; i++) {
        data[0]=data[i];
        for (j = i-1; data[j] >data[0] ; j--) {
            data[j+1]=data[j];
        }
        data[j+1]=data[0];
    }
    data[0]=0;
}

///3
ElemType *Count=(ElemType *)malloc(8* sizeof(ElemType));
void CountSort(ElemType data[],int n){
    int count;
    for (int i = 0; i < n; i++) {
        count =0;
        for (int j = 0; j < n; j++) {
            if(data[j]<data[i])
                count++;
        }
        Count[count]=data[i];
    }
    for (int k = 0; k < n; k++) {
        data[k]=Count[k];
    }
}

///4
void KnLocate(ElemType data[],int low,int high){
    int pivot=data[high];
    while(low<high){
        while(low<high&&data[low]<=pivot)   low++;
        data[high]=data[low];
        while(low<high&&data[high]>=pivot)   high--;
        data[low]=data[high];
    }
    data[low]=pivot;
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
//    SelectSort(L.data,L.length);//选择排序
//    PrintList(L);
    ListInsert(L,1,0);//是否有哨兵
//    HeapSort(L.data,L.length-1);//堆排序从小到大
//    PrintList(L);
//    HeapSortMin(L.data,L.length-1);//堆排序从大到小
//    PrintList(L);
//    MergeSort(L.data,0,7);//归并排序
//    PrintList(L);
///2
//    MergeSort(L.data,1,5);//创造题目条件
//    Insert_Sort(L.data,5,3);
//    PrintList(L);
///3
//    L.data[0]=50;
//    PrintList(L);
//    CountSort(L.data,L.length);
//    PrintList(L);
///4
    KnLocate(L.data,1,8);
    PrintList(L);
    return 0;
}
