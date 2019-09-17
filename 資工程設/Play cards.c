#include<stdio.h>
#include<stdlib.h>
int n,m,index[10000];
typedef struct _node{
    int num;
    struct _node *next;
}Node;
typedef struct _chang{
    char chr[10000];
    int a;
    int b;
}change;
void add ;
void cut ;
int main()
{
    int i;
    change op[10000];
    Node head;
    Node *np, *nq;
    scanf("%d%d",&n,&m);
    for(i=0;i<n;i++)
    {
        scanf("%d",&index[i]);
    }

   // printf("%d",head.num);
    head.num = index[0];
    head.next = (Node*)malloc(sizeof(Node));
    np = head.next;
    for(i=1;i<n-1;i++)
    {
        np->num = index[i];
        np->next = (Node*)malloc(sizeof(Node));
        np = np->next;
    }
    np->num = i;
    np->next = NULL;

    for(i=0;i<m;i++)
    {
        scanf("%c%c%c%d%d",&op[i].chr[0],&op[i].chr[1],&op[i].chr[2],&op[i].a,&op[i].b);
        if(op[i].chr[0]=='A')
        {
            add(index,op[i].a,op[i].b,&head);
            n++;
        }
        else if(op[i].chr[0]=='C')
        {
            if((op[i].a<n)&&(op[i].a+op[i].b<n))
            cut(index,op[i].a,op[i].b,&head);
        }
    }
}
void add(int num[],int a,int b,Node* head)
{
    int i;
    Node* p;
    Node* temp;
    temp = head;
    for(i=0;i<n;i++)
    {
        if(a==temp->)
        {
            break;
        }
        else{
            temp=temp->next;
        }
    }
    p->num=b;
    p->next=temp;
}
void cut(int num[],int a,int b,Node* head)
{
    int i;
    Node* temp;

}
