//
// Created by thinkpad on 2020-04-18.
// 2.3课后习题(18-19)
//

#include <stdio.h>
#include <stdlib.h>

using namespace std;
typedef int ElemType;
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

//初始化
bool InitList(LinkList &L) {
    L = (LNode *) malloc(sizeof(LNode));
    if (L == NULL) //防止脏数据
        return false;
    L->next = L;
    return true;
}

//判断单链表是否为空
bool Empty(LinkList L){
    if(L->next==L)
        return false;
    else
        return true;
}

//在p结点之后插入元素e
bool InsertNextLNode(LNode *p,ElemType e){
    if(p==NULL)
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

//头插法
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
    while(x!=9999){
        s=(LNode *)malloc(sizeof(LNode));
        s->data=x;
        r->next=s;
        r=s;
        scanf("%d",&x);
    }
    r->next=L;
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
    while(p!=L&&j<i){
        p=p->next;
        j++;
    }
    if(p==L) return NULL;
//    printf("%d",p->data);
    return p;
}

//按值查找
LNode *LocateElem(LinkList L,ElemType e){
    LNode *p=L->next;
    while(p!=L&&p->data!=e){
        p=p->next;
    }
    printf("%d",p->data);
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
    LNode *p;
    p=GetElem(L,i-1);//sds 啥爱党按时啊按时爱党
//    InsertNextLNode(p,e);
//    p=GetElem(L,i);//前插sd sd 地方 爱党
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
//    printf("%d",e);
    return true;
}

//打印链表数据及表长
bool PrintList(LinkList L) {
    if(L==NULL) {
        printf("链表为空");
        return false;
    }
    LNode *p=L->next;
    int x= 1;
    if (p == L) {
        printf("链表仅有头结点");
        return false;
    }
    while(p!=L){
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
    while(p!=L){
        q = p->next;
        free(p);
        p=q;
    }
    L = NULL;
}

//    2.3.18
void Merge(LinkList &L,LinkList &B){
    LNode *p,*q;
    p=L;
    while (p->next!=L){
        p=p->next;
    }
    q=B;
    while (q->next!=B){
        q=q->next;
    }
    p->next=B;
    q->next=L;
}

//    2.3.19
void Search_min(LinkList &L){
    LNode *pmin,*min,*pre,*p;
    while (L->next!=L){
        pmin=L;
        min=L->next;
        pre=L;
        p=L->next;
        while(p!=L){
            if(p->data<min->data){
                min=p;
                pmin=pre;
            }
            pre=p;
            p=p->next;
        }
        pmin->next=min->next;
        printf("%d\n",min->data);
        free(min);
    }
    free(L);
}

int main() {
    ElemType e;
    LinkList L;
    LinkList B;
//    Empty(L);
    InitList(L);
//    InitList(B);
//    List_HeadInsert(L);
    List_TailInsert(L);
//    List_TailInsert(B);
//    GetElem(L,1);
//    LocateElem(L,1);
//    ListInsert(L,1,5);
//    ListDelete(L,2,e);
//    DeleteLNode(L->next);
    PrintList(L);
//    2.3.18
//    Merge(L,B);
//    PrintList(L);
//    2.3.19
//    Search_min(L);
//    2.3.20

    DestroyList(L);
//    PrintList(L);//检查是否链表销毁

    return 0;
}

