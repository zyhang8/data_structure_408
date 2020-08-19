//
// Created by Yu Zhong. on 2020-04-17.
// 2.3课后习题(1-16,21)
//

#include <stdio.h>
#include <stdlib.h>

using namespace std;
typedef int ElemType;
//typedef char ElemType;//2.3.22
typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

//    初始化(带头结点)
bool InitList(LinkList &L) {
    L = (LNode *) malloc(sizeof(LNode));
    if (L == NULL) //防止脏数据
        return false;
    L->next = NULL;
    return true;
}

//    初始化(不带头结点)
bool InitList1(LinkList &L) {
    L = NULL;
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

//头插法(带头结点)
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

//    插入第i个位置(带头结点)
bool ListInsert(LinkList &L, int i, ElemType e) {
    LNode *p;
    p=GetElem(L,i-1);//后插
    InsertNextLNode(p,e);
//    p=GetElem(L,i);//前插
//    ListPriorInsert(p,e);
}

//    插入第i个位置(不带头结点)
bool ListInsert1(LinkList &L, int i, ElemType e) {
    if(i==1){
        LNode *s = (LNode *)malloc(sizeof(LNode));
        s->data=e;
        s->next=L;
        L=s;
        return true;
    }
    LNode *p;
    p=GetElem(L,i-1);//后插
    InsertNextLNode(p,e);
//    p=GetElem(L,i);//前插
//    ListPriorInsert(p,e);
}

//    头插法(不带头结点)
LinkList List_HeadInsert1(LinkList &L) {
    LNode *s;
    int x;
    scanf("%d", &x);
    L = (LNode *) malloc(sizeof(LNode));
    if (L == NULL) //防止脏数据
        return NULL;
    L->data=x;
    L->next=NULL;
    scanf("%d", &x);
    while (x != 9999) {
        ListInsert(L,1,x);
        scanf("%d", &x);
    }
    return L;
}

//    打印链表数据及表长
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
    r->next=NULL;
    return L;
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

//    2.3.1
void Del_x(LinkList &L,ElemType x){
    LNode *p=L;
    if(p==NULL){
        return;
    }
    if(L->data==x){
        p=L;
        L=L->next;
        free(p);
        Del_x(L,x);
    } else
        Del_x(L->next,x);
}

//    2.3.2
void Del_x_head(LinkList &L,ElemType x){
    LNode *p,*s=L;
    while(s->next!=NULL){
        p=s->next;
        if(p->data!=x){
            s=s->next;
        } else{
            s->next=p->next;
            free(p);
        }
    }
}

//    2.3.3
void R_Print(LinkList L){
    if(L->next!=NULL){
        R_Print(L->next);
        printf("元素:%d\n",L->next->data);
    }
}

//    2.3.4
void Del_min(LinkList &L){
    LNode *p=L->next,*min=L,*temp;
    ElemType value=L->next->data;
    while(p->next!=NULL){
        if(p->next->data<value){
            value=p->next->data;
            min=p;
        }
        p=p->next;
    }
    printf("%d\n",value);
    temp=min->next;
    min->next=temp->next;
    free(temp);
}

//    2.3.5
void Reverse(LinkList &L){
    LNode *p=L->next,*r;
    L->next=NULL;
    while(p!=NULL){
        r=p->next;
        p->next=L->next;
        L->next=p;
        p=r;
    }
}

//    2.3.6
void Del_m_n(LinkList &L,ElemType m,ElemType n){
    if(m>n){
        return;
    }
    LNode *p,*s=L;
    while(s->next!=NULL){
        p=s->next;
        if(p->data<=m||p->data>=n){
            s=s->next;
        } else{
            s->next=p->next;
            free(p);
        }
    }
}

//    2.3.7
void Order(LinkList &L){
    LNode *p=L->next,*r,*pre;
    r=p->next;
    p->next=NULL;
    p=r;
    while (p!=NULL){
        r=p->next;
        pre=L;
        while (pre->next!=NULL&&pre->next->data<p->data){
            pre=pre->next;
        }
        p->next=pre->next;
        pre->next=p;
        p=r;
    }
}

//    2.3.8
int Length(LinkList &L){
    LNode *p;
    if(L==NULL||L->next==NULL){
        return 0;
    }
    p=L->next;
    int length=0;
    while (p!=NULL) {
        length++;
        p=p->next;
    }
    return length;
}
LinkList Search_common(LinkList L,LinkList B){
    LNode *shortlist,*longlist;
    int dif=0;
    int length_L=Length(L);
    int length_B=Length(B);
    if (length_L<length_B){
        longlist=B->next;
        shortlist=L->next;
        dif=length_B-length_L;
    } else{
        longlist=L->next;
        shortlist=B->next;
        dif=length_L-length_B;
    }
    while (dif>0){
        longlist=longlist->next;
        dif--;
    }
    while (longlist!=NULL){
       if(longlist!=shortlist){
           longlist=longlist->next;
           shortlist=shortlist->next;
       } else{
           return longlist;
       }
    }
//    printf("为空");
    return NULL;
}

//    2.3.10
void Decompose(LinkList &L,LinkList &B){
    int flag=1;
    LNode *p,*r,*pre=L;
    p=L->next;
    r=B;
    while (p!=NULL){
        if(flag==1){
            pre->next=p->next;
            p->next=r->next;
            r->next=p;
            r=p;
            p=pre->next;
            flag=0;
        } else{
            pre=p;
            p=p->next;
            flag=1;
        }
    }
}

//    2.3.11
void Decompose_head(LinkList &L,LinkList &B){
    int flag=0;
    LNode *p,*r,*pre=L;
    p=L->next;
    r=B;
    while (p!=NULL){
        if(flag==1){
            pre->next=p->next;
            p->next=r->next;
            r->next=p;
            p=pre->next;
            flag=0;
        } else{
            pre=p;
            p=p->next;
            flag=1;
        }
    }
}

//    2.3.12
void Del_dup(LinkList &L){
    LNode *p=L->next;
    LNode *r,*q;
    if (p->next==NULL){
        return;
    }
    while(p->next!=NULL){
        r=p->next;
        if(p->data==r->data){
            p->next=r->next;
            q=r;
            r=r->next;
            free(q);
        } else{
            p=r;
            r=r->next;
        }
    }
}

//    2.3.13
void Merge(LinkList &L,LinkList &B) {
    LNode *p=L->next,*r=B->next,*temp;
    L->next=NULL;
    while(p!=NULL&&r!=NULL){
        if(p->data<r->data){
            temp=p->next;
            p->next=L->next;
            L->next=p;
            p=temp;
        } else{
            temp=r->next;
            r->next=L->next;
            L->next=r;
            r=temp;
        }
    }
    while (p!=NULL){
        temp=p->next;
        p->next=L->next;
        L->next=p;
        p=temp;
    }
    while (r!=NULL){
        temp=r->next;
        r->next=L->next;
        L->next=r;
        r=temp;
    }
}

//    2.3.14
void Merge_C(LinkList L,LinkList B,LinkList &C){
    LNode *p=L->next,*r=B->next;
    LNode *temp,*pre=C;
    while (p!=NULL&&r!=NULL){
        if (p->data<r->data){
            p=p->next;
        } else if(p->data>r->data) {
            r=r->next;
        } else{
            temp = (LNode *)malloc(sizeof(LNode));
            temp->data=r->data;
            pre->next=temp;
            pre=temp;
            p=p->next;
            r=r->next;
        }
    }
    pre->next=NULL;
}

//    2.3.15
void find_con(LinkList &L,LinkList &B){
    LNode *p=L->next,*r=B->next,*temp;
    while (p!=NULL&&r!=NULL){
        if (p->data<r->data){
            p=p->next;
        } else if(p->data>r->data) {
            r=r->next;
        } else{
            temp=r->next;
            r->next=p->next;
            p->next=r;
            r=temp;
            p=p->next;
        }
    }
}

//    2.3.16
bool son_list(LinkList &L,LinkList &B){
    LNode *p=L->next,*r=B->next;
    LNode *pre=L->next;
    while(p!=NULL&&r!=NULL) {
        if(p->data==r->data){
            p=p->next;
            r=r->next;
        } else{
            pre=pre->next;
            p=pre;
            r=B->next;
        }
    }
    if(r==NULL){
        printf("true");
        return true;
    } else{
        return false;
    }
}

//    2.3.21
int GetElem_Reverse(LinkList L,int i){
    int j = 1;
    i=Length(L)-i+1;
    LNode *p=L->next;
    if(i==0)
        return 0;
    if(i<1||i>Length(L)){
        return 0;
    }
    while(p!=NULL&&j<i){
        p=p->next;
        j++;
    }
    if(p==NULL) return NULL;
    printf("%d\n",p->data);
    return 1;
}

//    2.3.22
LNode *Suf_first(LinkList L,LinkList &B){
    int m,n;
    LNode *p=L->next;
    LNode *q=B->next;
    m=Length(L);
    n=Length(B);
    while(m>n){
        p=p->next;
        m--;
    }
    while(n>m){
        q=q->next;
        n--;
    }
    while (p!=q&&p->next!=NULL){
        p=p->next;
        q=q->next;
    }
    return p;
}

//    2.3.23
void Del_equal(LinkList &L, int n){
    int amount[n+1],data;
    LNode *p=L,*temp;
    for (int i = 0; i < n+1; i++) {
        amount[i]=0;
    }
    while (p->next!=NULL){
        data=p->next->data;
        if(p->next->data<0){
            data*=-1;
        }
        if(amount[data]==0){
            amount[data]=1;
            p=p->next;
        } else{
            temp=p->next;
            p->next=temp->next;
            free(temp);
        }
    }
}

//    2.3.24
LNode *circle1(LinkList L){
    LNode *p=L,*q=L;
    while (p!=NULL){
        while (q->next!=p&&q!=NULL){
            q=q->next;
        }
        if (q==NULL){
            p=p->next;
        } else{
            return p;
        }
    }
    return NULL;
}
LNode *circle2(LinkList L){
    LNode *slow=L,*fast=L;
    while (fast->next!=NULL&&fast!=NULL){
        slow=slow->next;
        fast=fast->next->next;
        if (slow==fast) break;
    }
    if(fast==NULL||fast->next==NULL){
        return NULL;
    }
    LNode *p=L, *q=slow;
    while (p!=q){
        p=p->next;
        q=q->next;
    }
    return p;
}

//    2.3.25
void Reverse_insert(LinkList &L){
    LNode *slow=L,*fast=L;
    while (fast->next!=NULL){
        slow=slow->next;
        fast=fast->next;
        if (fast->next!=NULL)
            fast=fast->next;
    }
    fast=slow->next;
    slow->next=NULL;
    LNode *r;
    while (fast!=NULL){
        r=fast->next;
        fast->next=slow->next;
        slow->next=fast;
        fast=r;
    }
    fast=slow->next;
    slow->next=NULL;
    slow=L->next;
    while (fast!=NULL){
        r=fast->next;
        fast->next=slow->next;
        slow->next=fast;
        slow=fast->next;
        fast=r;
    }
}
int main() {
    ElemType e;
    LinkList L;
    LinkList B;
    LinkList C;
    InitList(L);//带头结点
    InitList(B);//带头结点
    InitList(C);//带头结点
//    InitList1(L);//不带头结点
//    List_HeadInsert(L);//带头结点
//    List_HeadInsert(B);//带头结点
    List_TailInsert(L);
//    List_TailInsert(B);
//    List_HeadInsert(L);//不带头结点
//    L=GetElem(L,1);
//    L=LocateElem(L,1);
//    ListInsert(L,1,5);
//    ListDelete(L,2,e);
//    DeleteLNode(L->next);
    PrintList(L);//有头结点
//    PrintList(B);//有头结点
//    2.3.1

//    Del_x(L,2);
//    PrintList(L);
//    DestroyList(L);
//    2.3.2
//    Del_x_head(L,2);
//    PrintList(L);
//    2.3.3
//    R_Print(L);
//    PrintList(L);
//    2.3.4
//    Del_min(L);
//    PrintList(L);
//    2.3.5
//    Reverse(L);
//    PrintList(L);
//    2.3.6
//    Order(L);
//    PrintList(L);
//    2.3.7
//    Del_m_n(L,2,5);
//    PrintList(L);
//    2.3.8
//    Search_common(L,B);
//    2.3.9
//    PrintList(L);
//    DestroyList(L);
//    2.3.10
//    Decompose(L,B);
//    PrintList(L);
//    PrintList(B);
//    2.3.11
//    Decompose_head(L,B);
//    PrintList(L);
//    PrintList(B);
//    2.3.12
//    Del_dup(L);
//    PrintList(L);
//    2.3.13
//    Merge(L,B);
//    2.3.14
//    Merge_C(L,B,C);
//    PrintList(C);
//    2.3.15
//    find_con(L,B);
//    PrintList(L);
//    2.3.16
//    son_list(L,B);
//    2.3.21
//    GetElem_Reverse(L,3);
//    2.3.22
//    Suf_first(L,B);
//    PrintList(L);
//    2.3.23
//    Del_equal(L,22);
//    PrintList(L);
//    2.3.24
//    circle1(L);//解法1
//    circle2(L);//解法2
//    2.3.25
    Reverse_insert(L);
    PrintList(L);
    return 0;
}

