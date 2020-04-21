//
// Created by thinkpad on 2020-04-18.
// 2.3�κ�ϰ��(18-19)
//

#include <stdio.h>
#include <stdlib.h>

using namespace std;
typedef int ElemType;
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

//��ʼ��
bool InitList(LinkList &L) {
    L = (LNode *) malloc(sizeof(LNode));
    if (L == NULL) //��ֹ������
        return false;
    L->next = L;
    return true;
}

//�жϵ������Ƿ�Ϊ��
bool Empty(LinkList L){
    if(L->next==L)
        return false;
    else
        return true;
}

//��p���֮�����Ԫ��e
bool InsertNextLNode(LNode *p,ElemType e){
    if(p==NULL)
        return false;
    LNode *s = (LNode *)malloc(sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return true;
}

//ͷ�巨
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

//β�巨
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

//����Ų���
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

//��ֵ����
LNode *LocateElem(LinkList L,ElemType e){
    LNode *p=L->next;
    while(p!=L&&p->data!=e){
        p=p->next;
    }
    printf("%d",p->data);
    return p;
}

//�ڽ��pǰ��
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

//�����i��λ��
bool ListInsert(LinkList &L, int i, ElemType e) {
    LNode *p;
    p=GetElem(L,i-1);//sds ɶ������ʱ����ʱ����
//    InsertNextLNode(p,e);
//    p=GetElem(L,i);//ǰ��sd sd �ط� ����
//    ListPriorInsert(p,e);
}

//ɾ�����p
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

//ɾ���������i����㲢����ɾ��ֵ
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

//��ӡ�������ݼ���
bool PrintList(LinkList L) {
    if(L==NULL) {
        printf("����Ϊ��");
        return false;
    }
    LNode *p=L->next;
    int x= 1;
    if (p == L) {
        printf("�������ͷ���");
        return false;
    }
    while(p!=L){
        printf("��%d��Ԫ��Ϊ:",x);
        printf("%d\n",p->data);
        p=p->next;
        x++;
    }
    printf("��Ϊ:%d\n",x-1);
    return true;
}

//�ݻٵ�����
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
//    PrintList(L);//����Ƿ���������

    return 0;
}

