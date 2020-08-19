//
// Created by Mr. Roy Z. on 2020/7/10.
// Copyright (c) 2020 Yu Zhong. All rights reserved.
// Chapter5.3.cpp
//

#include <stdio.h>
#include <stdlib.h>
#define MaxSize 50
#define STACK_INIT_SIZE 100
#define STACKINCREMENT 10

typedef char ElemType;


typedef struct BiTNode
{
    char data;
    struct BiTNode *lchild,*rchild;
    int tag;
    int weight;
}BiTNode,*BiTree;
typedef struct {
    struct BiTNode *data[MaxSize];
    int front,rear;
} SqQueue;
typedef struct {
    BiTree *base;
    BiTree *top;
    int stacksize;
}SqStack;
typedef struct LNode {
    ElemType data;
    struct LNode *lchild,*rchild;
} LNode, *LinkList;
void InitQueue(SqQueue &Q){
    Q.rear=Q.front=0;
}

bool EnQueue(SqQueue &Q,BiTNode* x){
    Q.data[++Q.rear]=x;
    return true;
}

void visit(BiTree T){
    printf("%c ",T->data);
}

void PreOrderTraverse(BiTree T)//二叉树的先序遍历
{
    if(T==NULL)
        return ;
    visit(T);
    PreOrderTraverse(T->lchild);
    PreOrderTraverse(T->rchild);
}
void InOrderTraverse(BiTree T)//二叉树的中序遍历
{
    if(T==NULL)
        return ;
    InOrderTraverse(T->lchild);
    visit(T);
    InOrderTraverse(T->rchild);
}
void PostOrderTraverse(BiTree T)//后序遍历
{
    if(T==NULL)
        return;
    PostOrderTraverse(T->lchild);
    PostOrderTraverse(T->rchild);
    visit(T);
}

void CreateBiTree(BiTree &T)
{
    char ch;
    scanf("%c",&ch);
    if(ch=='#')
        T=NULL;
    else
    {
        T=(BiTNode *)malloc(sizeof(BiTNode));
        if(!T)
            return;
        T->data=ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

int treeDepth(BiTree T){
    if (T == NULL)
        return 0;
    else{
        int l= treeDepth(T->lchild);
        int r= treeDepth(T->rchild);
        return l>r ? l+1 : r+1;
    }
}

bool isEmpty(SqQueue Q){
    return Q.rear == Q.front;
}

BiTNode* DeQueue(SqQueue &Q){
    return Q.data[++Q.front];;
}


void LevelOrder(BiTree T,SqQueue Q){
    InitQueue(Q);
    BiTree p;
    EnQueue(Q,T);
    while(!isEmpty(Q)){
        p=DeQueue(Q);
        visit(p);
        if(p->lchild!=NULL) {
            EnQueue(Q, p->lchild);
        }
        if(p->rchild!=NULL) {
            EnQueue(Q, p->rchild);
        }
    }
}

int  InitStack(SqStack &S)//建立栈
{
    S.base = (BiTree *) malloc(STACK_INIT_SIZE * sizeof(BiTree));
    if (!(S.base)) return 0;
    S.top = S.base;
    S.stacksize = STACK_INIT_SIZE;
    return 0;
}

int Push(SqStack &S,BiTree e)//将元素e插入栈中
{
    if (S.top - S.base >= S.stacksize)
    {
        if(!(S.base = (BiTree*)realloc(S.base, (STACK_INIT_SIZE + STACKINCREMENT) * sizeof(BiTree))))
            return 0;
        S.top = S.base + STACKINCREMENT;
        S.stacksize += STACKINCREMENT;
    }
    *S.top++ = e;
    return 0;
}

int Pop(SqStack &S, BiTree &e)//出栈，将栈顶元素赋值给e返回
{
    if (S.base == S.top)
        return false;
    e =*--S.top;
    return 0;
}

int StackEmpty(SqStack &S)//判定栈是否为空
{
    if (S.base == S.top)
    {
        return true;
    }
    else
        return false;
}

int GetTop(SqStack S, BiTree &e)//取栈顶元素赋值给e
{
    if (S.top == S.base) return false;
    e = *(S.top-1);
    return 0;
}

void InOrder(BiTree T){//中序非递归遍历
    SqStack S;
    InitStack(S);
    BiTree p=T;
    while(p||!StackEmpty(S)){
        if(p){
            Push(S,p);
            p=p->lchild;
        } else{
            Pop(S,p);
            visit(p);
            p=p->rchild;
        }
    }
}

void PreOrder(BiTree T){//前序非递归遍历
    SqStack S;
    InitStack(S);
    BiTree p=T;
    while(p||!StackEmpty(S)){
        if(p){
            visit(p);
            Push(S,p);
            p=p->lchild;
        } else{
            Pop(S,p);
            p=p->rchild;
        }
    }
}

void PostOrder(BiTree T){//后序非递归遍历
    SqStack S;
    InitStack(S);
    BiTree p=T,r = NULL;
    while (p||!StackEmpty(S)) {
        if(p){
            Push(S,p);
            p=p->lchild;
        } else {
            GetTop(S, p);
            if (p->rchild && p->rchild != r) {
                p = p->rchild;
                Push(S, p);
                p = p->lchild;
            } else {
                Pop(S, p);
                visit(p);
                r = p;
                p = NULL;
            }
        }
    }
}

//3
void ReLevelOrder(BiTree T,SqQueue Q){
    InitQueue(Q);
    SqStack S;
    InitStack(S);
    BiTree p;
    EnQueue(Q,T);
    while(!isEmpty(Q)){
        p=DeQueue(Q);
//        visit(p);
        Push(S,p);
        if(p->lchild!=NULL) {
            EnQueue(Q, p->lchild);
        }
        if(p->rchild!=NULL) {
            EnQueue(Q, p->rchild);
        }
    }
    while(!StackEmpty(S)){
        Pop(S, p);
        visit(p);
    }
}

//5
int TreeDepth(BiTree T,SqQueue Q){
    InitQueue(Q);
    int last=1,level=0;
    BiTree p;
    EnQueue(Q,T);
    while(!isEmpty(Q)){
        p=DeQueue(Q);
        if(p->lchild!=NULL) {
            EnQueue(Q, p->lchild);
        }
        if(p->rchild!=NULL) {
            EnQueue(Q, p->rchild);
        }
        if(Q.front==last){
            level++;
            last=Q.rear;
        }
    }
    return level;
}

//6
BiTree PreInCreateBiTree(ElemType A[],ElemType B[],int p1,int q1,int p2,int q2){
    BiTree T=(BiTNode *)malloc(sizeof(BiTNode));
    T->data=A[p1];
    int i;
    for(i=p2;B[i]!=T->data;i++);
    int llen=i-p2;
    int rlen=q2-i;
    if(llen)
        T->lchild=PreInCreateBiTree(A,B,p1+1,p1+llen,p2,p2+llen-1);
    else
        T->lchild=NULL;
    if(rlen)
        T->rchild=PreInCreateBiTree(A,B,q1-rlen+1,q1,q2-rlen+1,q2);
    else
        T->rchild=NULL;
    return T;
}

//7
bool IsComplete(BiTree T,SqQueue Q){
    InitQueue(Q);
    if(!T)
        return true;
    BiTree p;
    EnQueue(Q,T);
    while(!isEmpty(Q)){
        p=DeQueue(Q);
        if(p) {
            EnQueue(Q, p->lchild);
            EnQueue(Q, p->rchild);
        } else{
            while(!isEmpty(Q)){
                p=DeQueue(Q);
                if(p){
                    return false;
                }
            }
        }
    }
    return true;
}

//8
int DsonNodes(BiTree T){
    int d=0;
    if(T==0)
        return 0;
    else if(T->lchild!=NULL&&T->rchild!=NULL){
       d=DsonNodes(T->lchild)+DsonNodes(T->rchild)+1;
   } else{
        d=DsonNodes(T->lchild)+DsonNodes(T->rchild);
    }
    return d;
}

//9
void swap(BiTree &T){
    BiTree temp;
    if(T){
        swap(T->lchild);
        swap(T->rchild);
        temp=T->lchild;
        T->lchild=T->rchild;
        T->rchild=temp;
    }
}

//10
int i=1;
ElemType PreIndex(BiTree T,int index)//二叉树的先序遍历
{
    char ch;
    if(T==NULL)
        return '#';
    if(i==index){
        return T->data;
    }
    i++;
    ch=PreIndex(T->lchild,index);
    if(ch!='#')
        return ch;
    ch=PreIndex(T->rchild,index);
    return ch;
}

//11
void DeleteXTree(BiTree &T){
    if(T){
        DeleteXTree(T->lchild);
        DeleteXTree(T->rchild);
        free(T);
    }
}
void SearchParent(BiTree &T,SqQueue Q,ElemType x){
    if(T->data==x){
        DeleteXTree(T);
        return;
    }
    InitQueue(Q);
    BiTree p;
    EnQueue(Q,T);
    while(!isEmpty(Q)){
        p=DeQueue(Q);
        if(p->lchild!=NULL) {
            if(p->lchild->data==x){
                DeleteXTree(p->lchild);
                p->lchild=NULL;
            } else{
                EnQueue(Q, p->lchild);
            }
        }
        if(p->rchild!=NULL) {
            if(p->rchild->data==x){
                DeleteXTree(p->rchild);
                p->rchild=NULL;
            } else{
                EnQueue(Q, p->rchild);
            }
        }
    }
}

//12
void SearchXParent(BiTree T,ElemType x){//后序非递归遍历
    SqStack S;
    InitStack(S);
    BiTree p=T,r = NULL;
    while (p||!StackEmpty(S)) {
        if(p){
            Push(S,p);
            p=p->lchild;
        } else {
            GetTop(S, p);
            if (p->rchild && p->rchild != r) {
                p = p->rchild;
                Push(S, p);
                p = p->lchild;
            } else {
                if (p->data==x){
                    Pop(S,p);
                    while (!StackEmpty(S)){
                        Pop(S,p);
                        visit(p);
                    }
                    return;
                } else{
                    Pop(S, p);
                    r = p;
                    p = NULL;
                }
            }
        }
    }
}

//13
BiTree SearchX(BiTree T,ElemType x){//后序非递归遍历
    SqQueue Q;
    InitQueue(Q);
    BiTree p;
    EnQueue(Q,T);
    while(!isEmpty(Q)){
        p=DeQueue(Q);
        if(p->data==x){
            return p;
        }
        if(p->lchild!=NULL) {
            EnQueue(Q, p->lchild);
        }
        if(p->rchild!=NULL) {
            EnQueue(Q, p->rchild);
        }
    }
    return NULL;
}
typedef struct {
    BiTree t;
    int tag;
}stack;
stack s[10],s1[10];
BiTree Ancestor(BiTree ROOT,BiTNode *p,BiTNode *q){
    int top=0,top1=0;
    BiTree bt=ROOT;
//    SqStack S
//    InitStack(S);
//    BiTree bt=ROOT;
    while (bt!=NULL||top>0) {
        while (bt!=NULL&&bt!=p&&bt!=q)
            while (bt!=NULL){
                s[++top].t=bt;
                s[top].tag=0;
                bt=bt->lchild;
            }
        while (top!=0&&s[top].tag==1){
            if(s[top].t==p){
                for (int i = 1; i <= top; i++) {
                    s1[i]=s[i];
                    top1=top;
                }
            }
            if(s[top].t==q)
                for (int i = top; i > 0; i--) {
                    for (int j = top1; j > 0; j--)
                        if (s1[j].t == s[i].t)
                            return s[i].t;
                }
            top--;
        }
        if(top!=0){
            s[top].tag=1;
            bt=s[top].t->rchild;
        }
    }
    return NULL;
}

//14
int Width(BiTree T,SqQueue Q){
    if(T==NULL){
        return 0;
    }
    int width=1;
    InitQueue(Q);
    BiTree p;
    BiTNode *q;
    if(T->rchild){
        width++;
        q=T->rchild;
    } else
        q=T->lchild;
    EnQueue(Q,T);
    while(!isEmpty(Q)){
        p=DeQueue(Q);
        if(p==q){
            if(p->rchild){
                width++;
                q=T->rchild;
            } else
                q=T->lchild;
        }
        if(p->lchild!=NULL) {
            EnQueue(Q, p->lchild);
        }
        if(p->rchild!=NULL) {
            EnQueue(Q, p->rchild);
        }
    }
    return width;
}

//15
void PreToPost(ElemType pre[],int l1,int h1,ElemType post[],int l2,int h2){
    int half;
    if(l1<=h1){
        post[h2]=pre[l1];
        half=(h1-l1)/2;
        PreToPost(pre,l1+1,l1+half,post,l2,l2+half-1);
        PreToPost(pre,l1+half+1,h1,post,l2+half,h2-1);
    }
}
//16
BiTree head,pre=NULL;
BiTree BitreeLink(BiTree T){
    if(T){
        BitreeLink(T->lchild);
        if(T->lchild==NULL&&T->rchild==NULL)
            if(pre==NULL) {
                head=T;
                pre=T;
            } else{
            pre->rchild=T;
//            visit(pre->rchild);
            pre=T;
            }
        BitreeLink(T->rchild);
        pre->rchild=NULL;
    }
    return head;
}

//17
bool SimiliarTree(BiTree T1,BiTree T2){
    if(T1==NULL&&T2==NULL)
        return true;
    else if(T1==NULL||T2==NULL)
        return false;
    else{
        return SimiliarTree(T1->lchild,T2->lchild)&&SimiliarTree(T1->rchild,T2->rchild);
    }
}

//19
int WPL(BiTree T,int deep){
    static int wpl=0;
    if(T->lchild==NULL&&T->rchild==NULL)
        return wpl+=T->weight*deep;
    if(T->lchild!=NULL)
        WPL(T->lchild,deep+1);
    if(T->rchild!=NULL)
        WPL(T->rchild,deep+1);
    return wpl;
}

//20
void BiTreeExp(BiTree T){
    if(T==NULL) return;
    else{
        printf("(");
        BiTreeExp(T->lchild);
        printf("%c",T->data);
        BiTreeExp(T->rchild);
        printf(")");
    }
}

int main()
{
    BiTree T2;
    BiTree T;
    // ABDG##H###CE#I##F##  https://img-blog.csdn.net/20180622225556216?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2RyZWFtMDEzMF9f/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70
    SqQueue Q;
    int x;
    InitQueue(Q);
    //6
//    char A[9]={'A','B','D','G','H','C','E','I','F'};
//    char B[9]={'G','D','H','B','A','E','I','C','F'};
//    T=PreInCreateBiTree(A,B,0,8,0,8);
    CreateBiTree(T);
    PreOrderTraverse (T);//A B D G H C E I F
    printf("\n");
    InOrderTraverse(T);//G D H B A E I C F
    printf("\n");
    PostOrderTraverse(T);//G H D B I E F C A
    printf("\n");
    printf("深度:%d\n",treeDepth(T));
    LevelOrder(T,Q);
    printf("\n");
    InOrder(T);
    printf("\n");
    PreOrder(T);
    printf("\n");
    PostOrder(T);
    printf("\n");
    //4 层级遍历、右到左、上到下
    ReLevelOrder(T,Q);
    printf("\n");
    //5
    printf("深度:%d\n",TreeDepth(T,Q));
    //7
    if(IsComplete(T, Q))
        printf("满二叉树");
    else
        printf("非满二叉树");
    printf("\n");
    //8
    printf("双分支结点个数为：%d\n",DsonNodes(T));
    //9
//    swap(T);
//    PreOrderTraverse (T);
//    printf("\n");
    //10
    printf("第5个字符为：%c\n",PreIndex(T,5));
    //11
//    SearchParent(T,Q,'D');
//    PreOrderTraverse (T);
//    printf("\n");
    //12
    SearchXParent(T,'G');
    printf("\n");
    //13
    BiTNode *p=(BiTNode *)malloc(sizeof(BiTNode));
    BiTNode *q=(BiTNode *)malloc(sizeof(BiTNode));
    p = SearchX(T, 'D');
    visit(p);
    q = SearchX(T, 'D');
    visit(q);
    BiTree r=Ancestor(T,p,q);
    visit(r);
    printf("\n");
    //14
    printf("宽度为:%d",Width(T,Q));
    printf("\n");
    //15
    char pre[7]={'A','B','C','D','E','F','G'};
    char post[7];
    PreToPost(pre,0,6,post,0,6);
    for (int i = 0; i < 7; i++) {
        printf("%c ",pre[i]);
    }
    printf("\n");
    for (int i = 0; i < 7; i++) {
        printf("%c ",post[i]);
    }
    printf("\n");
    //16
//    InOrderTraverse(T);//G D H B A E I C F
//    printf("\n");
    InOrderTraverse(BitreeLink(T));//G D H B A E I C F
    printf("\n");
    //17
    T2=T;
    if(SimiliarTree(T,T2))
        printf("相似");
    else
        printf("不相似");
    printf("\n");
    //19
    printf("%d",WPL(T,0));
    printf("\n");
    //20
    BiTreeExp(T);
    printf("\n");
    return 0;
}
