//
// Created by thinkpad on 2020-04-15.
// 单链表
//

#include <stdio.h>
#include <stdlib.h>

using namespace std;
typedef int ElemType;
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

//初始化(带头结点)
bool InitList(LinkList &L) {
    L = (LNode *) malloc(sizeof(LNode));
    if (L == NULL) //防止脏数据
        return false;
    L->next = NULL;
    return true;
}

//    初始化(不带头结点)
bool InitList(LinkList &L) {
    L = NULL;
    return true;
}

//    判断单链表是否为空(带头结点)
bool Empty(LinkList L){
    if(L->next==NULL)
        return false;
    else
        return true;
}

//    判断单链表是否为空(不带头结点)
bool Empty(LinkList L){
    if(L==NULL)
        return false;
    else
        return true;
}

//    在p结点之后插入元素e
bool InsertNextLNode(LNode *p,ElemType e){
    if(p==NULL)
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

//    头插法(带头结点)
LinkList List_HeadInsert(LinkList &L) {
    LNode *s;
    int x;
    scanf("%d", &x);
    while (x != 9999) {
        InsertNextLNode(L,x);
        scanf("%d", &x);
    }
    return L;
}

//尾插法
LinkList List_TailInsert(LinkList &L){
    int x;
    LNode *s,*r=L;
    scanf("%d",&x);
//    //    不带头节点
//    L = (LNode *) malloc(sizeof(LNode));
//    if (L == NULL) //防止脏数据
//        return NULL;
//    L->data=x;
//    L->next=NULL;
    while(x!=9999){
        s=(LNode *)malloc(sizeof(LNode));
        s->data=x;
        r->next=s;
        r=s;
        scanf("%d",&x);
    }
    r->next=NULL;
    return L;
}

//按序号查找
LNode *GetElem(LinkList L,int i){
    int j = 1;
    LNode *p=L->next;
    if(i==0)
        return L;
    if(i<1){
        return NULL;
    }
    while(p!=NULL&&j<i){
        p=p->next;
        j++;
    }
    if(p==NULL) return NULL;
    return p;
}

//按值查找
LNode *LocateElem(LinkList L,ElemType e){
    LNode *p=L->next;
    while(p!=NULL&&p->data!=e){
        p=p->next;
    }
    return p;
}

//在结点p前插
bool ListPriorInsert(LNode *p,ElemType e){
    if(p==NULL)
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    if (s==NULL)
        return false;
    s->next=p->next;
    p->next=s;
    s->data=p->data;
    p->data=e;
    return true;
}

//插入第i个位置
bool ListInsert(LinkList &L, int i, ElemType e) {
//    不带头结点
//    if(i==1){
//        LNode *s = (LNode *)malloc(sizeof(LNode));
//        s->data=e;
//        s->next=L;
//        L=s;
//        return true;
//    }
    LNode *p;
    p=GetElem(L,i-1);//后插
//    InsertNextLNode(p,e);
//    p=GetElem(L,i);//前插
//    ListPriorInsert(p,e);
}

//删除结点p
bool DeleteLNode(LNode *p){
    LNode *q;
    if(p==NULL)
        return false;
    q=p->next;
    p->data=p->next->data;
    p->next=q->next;
    free(q);
    return true;
}

//删除单链表第i个结点并返回删除值
bool ListDelete(LinkList &L, int i, ElemType &e){
    LNode *p,*q;
    p=GetElem(L,i-1);
    q=p->next;
    e=q->data;
    p->next=q->next;
    free(q);
    return true;
}

//打印链表数据及表长
bool PrintList(LinkList L) {
    if(L==NULL) {
        printf("链表为空\n");
        return false;
    }
    LNode *p=L->next;
    int x= 1;
    if (p == NULL) {
        printf("链表仅有头结点\n");
        return false;
    }
    while(p!=NULL){
        printf("第%d个元素为:",x);
        printf("%d\n",p->data);
        p=p->next;
        x++;
    }
    printf("表长为:%d\n",x-1);
    return true;
}

//打印链表数据及表长(无头结点)
bool PrintList1(LinkList L) {
    if(L==NULL) {
        printf("链表为空");
        return false;
    }
    LNode *p=L;
    int x= 1;
    while(p!=NULL){
        printf("第%d个元素为:",x);
        printf("%d\n",p->data);
        p=p->next;
        x++;
    }
    printf("表长为:%d\n",x-1);
    return true;
}

//摧毁单链表
void DestroyList(LinkList &L){
    LNode *q,*p=L;
    if (p == NULL) {
        return;
    }
    while(p!=NULL){
        q = p->next;
        free(p);
        p=q;
    }
    L = NULL;
}

int main() {
    ElemType e;
    LinkList L;
    Empty(L);//带头结点
//    Empty(L);//不带头结点
    InitList(L);//带头结点
//    InitList(L);//不带头结点
//    List_HeadInsert(L);//带头结点
    List_HeadInsert(L);//不带头结点
    List_TailInsert(L);
//    L=GetElem(L,1);
//    L=LocateElem(L,1);
//    ListInsert(L,1,5);
//    ListDelete(L,2,e);
//    DeleteLNode(L->next);
    PrintList(L);
    DestroyList(L);
//    PrintList(L);//检查是否链表销毁
    return 0;
}