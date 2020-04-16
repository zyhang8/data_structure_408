//
// Created by thinkpad on 2020-04-16.
// ˫����
//

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct DNode{
    ElemType  data;
    struct DNode *next,*prior;
}DNode, *DListlist;

//��ʼ��
bool InitDListlist(DListlist &L){
    L=(DNode *)malloc(sizeof(DNode));
    if(L==NULL){
        return false;
    }
    L->next=NULL;
    L->prior=NULL;
    return true;
}

//�ж��Ƿ�Ϊ��
bool Empty(DListlist L){
    if(L->next==NULL){
        return false;
    }
    else
        return true;
}

//��p֮�����s
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

//ͷ�巨
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

//ɾ��p�ĺ�̽��q
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

//�ݚ�����
void DestoryDList(DListlist &L){
    while(L->next!=NULL){
        DeleteNextDNode(L);
    }
    free(L);
    L=NULL;
}

//����Ų���
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

//��ֵ����
DNode *LocateElem(DListlist L,ElemType e){
    DNode *p=L->next;
    while(e!=p->data&&p!=NULL){
        p=p->next;
    }
//    printf("%d",p->data);
    return p;
}

//��ӡ������
bool PrintDList(DListlist L){
    if(L==NULL){
        printf("����Ϊ��");
        return false;
    }
    DNode *p=L->next;
    if(p==NULL){
        printf("�������ͷ���");
        return false;
    }
    int x=1;//���㳤��
    while(p!=NULL){
        printf("��%d��Ԫ��Ϊ:",x);
        printf("%d\n",p->data);
        p=p->next;
        x++;
    }
    printf("��Ϊ:%d\n",x-1);
    return true;
}

int main(){
    DListlist L;
    Empty(L);
    InitDListlist(L);
    DList_HeadInsert(L);
    PrintDList(L);
//    GetElem(L,2);
//    LocateElem(L,3);
    DestoryDList(L);
    PrintDList(L);
    return 0;
}
