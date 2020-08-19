//
// Created by Yu Zhong. on 2020-04-19.
// 2.3课后习题(20)
//

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct DNode{
    ElemType  data;
    struct DNode *next,*prior;
    int freq=0;
}DNode, *DListlist;

//初始化
bool InitDListlist(DListlist &L){
    L=(DNode *)malloc(sizeof(DNode));
    if(L==NULL){
        return false;
    }
    L->next=NULL;
    L->prior=NULL;
    return true;
}

//判断是否为空
bool Empty(DListlist L){
    if(L->next==NULL){
        return false;
    }
    else
        return true;
}

//在p之后插入s
bool InsertNextDNode(DNode *p,DNode *s){
    if(p==NULL || s==NULL){
        return false;
    }
    s->next=p->next;
    if(p->next!=NULL){
        p->next->prior=s;
    }
    s->prior=p;
    p->next=s;
    return true;
}

//头插法
DListlist DList_HeadInsert(DListlist &L){
    int x;
    DNode *s;
    scanf("%d",&x);
    while(x!=9999){
        s=(DNode *)malloc(sizeof(DNode));
        s->data=x;
        InsertNextDNode(L,s);
        scanf("%d",&x);
    }
    return L;
}

//尾插法
DListlist DList_TailInsert(DListlist &L){
    int x;
    int freq;//2.3.20
    DNode *s,*r=L;
    scanf("%d",&x);
//    scanf("%d",&freq);//2.3.20
    while(x!=9999){
        s=(DNode *)malloc(sizeof(DNode));
        s->data=x;
        r->next=s;
        s->prior=r;
        r=s;
//        r->freq=freq;//2.3.20
        scanf("%d",&x);
//        scanf("%d",&freq);//2.3.20
    }
    r->next=NULL;
    return L;
}

//删除p的后继结点q
bool DeleteNextDNode(DNode *p){
    if(p==NULL)
        return false;
    DNode *q=p->next;
    if(q==NULL){
        return false;
    }
    p->next=q->next;
    if(q->next!=NULL){
        q->next->prior=p;
    }
    free(q);
    return true;
}

//摧毀链表
void DestoryDList(DListlist &L){
    while(L->next!=NULL){
        DeleteNextDNode(L);
    }
    free(L);
    L=NULL;
}

//按序号查找
DNode *GetElem(DListlist L,int i){
    int j=1;
    DNode *p=L->next;
    if(i==0)
        return L;
    if(i<1)
        return NULL;
    while(p!=NULL&&j<i){
        p=p->next;
        j++;
    }
    if(p==NULL)
        return NULL;
//    printf("%d",p->data);//debug
    return p;
}

//按值查找
DNode *LocateElem(DListlist L,ElemType e){
    DNode *p=L->next;
    while(e!=p->data&&p!=NULL){
        p=p->next;
    }
//    printf("%d",p->data);
    return p;
}

//打印链表及表长
bool PrintDList(DListlist L){
    if(L==NULL){
        printf("链表为空");
        return false;
    }
    DNode *p=L->next;
    if(p==NULL){
        printf("链表仅有头结点");
        return false;
    }
    int x=1;//计算长度
    while(p!=NULL){
        printf("第%d个元素为:",x);
        printf("%d\n",p->data);
//        printf("%d\n",p->freq);//2.3.20
        p=p->next;
        x++;
    }
    printf("表长为:%d\n",x-1);
    return true;
}

//    2.3.20
DNode *Locate(DListlist L,ElemType e){
    DNode *p=L->next;
    while(e!=p->data&&p!=NULL){
        p=p->next;
    }
    ElemType temp1,temp2;
//    printf("%d",p->data);
    if(p!=NULL){
        p->freq++;
        while(p!=L&&p->prior->freq<=p->freq){
            temp1=p->data;
            temp2=p->freq;
            p->data=p->prior->data;
            p->freq=p->prior->freq;
            p=p->prior;
            p->data=temp1;
            p->freq=temp2;
        }
    }
    return p;
}

int main(){
    DListlist L;
//    Empty(L);
    InitDListlist(L);
//    DList_HeadInsert(L);
    DList_TailInsert(L);
    PrintDList(L);
//    GetElem(L,2);
//    LocateElem(L,3);
//    2.3.20
//    Locate(L,4);
//    PrintDList(L);

//    DestoryDList(L);
//    PrintDList(L);
    return 0;
}

