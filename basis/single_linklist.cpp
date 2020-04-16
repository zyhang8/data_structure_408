//
// Created by thinkpad on 2020-04-15.
// ������
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
    L->next = NULL;
    return true;
}

//�жϵ������Ƿ�Ϊ��
bool Empty(LinkList L){
    if(L->next==NULL)
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
    r->next=NULL;
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
    while(p!=NULL&&j<i){
        p=p->next;
        j++;
    }
    if(p==NULL) return NULL;
    return p;
}

//��ֵ����
LNode *LocateElem(LinkList L,ElemType e){
    LNode *p=L->next;
    while(p!=NULL&&p->data!=e){
        p=p->next;
    }
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
    p=GetElem(L,i-1);//���
//    InsertNextLNode(p,e);
//    p=GetElem(L,i);//ǰ��
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
    if (p == NULL) {
        printf("�������ͷ���");
        return false;
    }
    while(p!=NULL){
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
    Empty(L);
    InitList(L);
//    List_HeadInsert(L);
    List_TailInsert(L);
//    L=GetElem(L,1);
//    L=LocateElem(L,1);
//    ListInsert(L,1,5);
//    ListDelete(L,2,e);
//    DeleteLNode(L->next);
    PrintList(L);
    DestroyList(L);
//    PrintList(L);//����Ƿ���������
    return 0;
}