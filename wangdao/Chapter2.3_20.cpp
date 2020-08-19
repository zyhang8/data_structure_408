//
// Created by Yu Zhong. on 2020-04-19.
// 2.3�κ�ϰ��(20)
//

#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct DNode{
    ElemType  data;
    struct DNode *next,*prior;
    int freq=0;
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

//β�巨
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
//        printf("%d\n",p->freq);//2.3.20
        p=p->next;
        x++;
    }
    printf("��Ϊ:%d\n",x-1);
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

