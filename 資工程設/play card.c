#include<stdio.h>
#include<stdlib.h>
int n,m,index[10000];
typedef struct _node{
    int num;
    struct _node *next;
}Node;
Node *head;
Node *np;
Node *nq;
void add();
void cut();
void generate();
int main(void)
{
    int i,a,b;
    char lit[10000];
    scanf("%d%d",&n,&m);
    for(i=0;i<n;i++)
    {
        scanf("%d",&index[i]);
    }
    generate();
            //printf("%d%d",head->num,np->num);
    for(i=0;i<m;i++)
    {
        scanf("%s%d%d",lit,&a,&b);
        if(lit[0]=='A')
        {
            add(a,b);
            n++;
            //printf("%d%d\n",head->num,np->num);
        }
        else if(lit[0]=='C'&&(a<n)&&(a+b-1<n))
        {
            cut(a,b);
            //printf("%d\n",head->num);
        }
    }
    np = head;
    while(np!=NULL){
        printf("%d\n",np->num);
        np=np->next;
    }
    /*np = head;
    while (np!=NULL) {
        nq = np;
        np = np->next;
        free(nq);
    }*/


}
void generate()
{
    int i;
    head = (Node*)malloc(sizeof(Node));
    head->num=index[0];
    np = head;
    for(i=1;i<n;i++)
    {
        np->next = (Node*)malloc(sizeof(Node));
        np = np->next;
        np->num = index[i];
    }
    np->next = NULL;
}
void add(int a,int b)
{
    int i;
    Node *p;
    Node *cp;
    /*for(i=n-1;i>=a;i--)
    {
        int temp;
        temp=index[i];
        index[i+1]=temp;
    }
    index[a]=b;*/

    cp=head;
    for(i=1;i<a;i++)
    {
        cp=cp->next;
    }
    if(a==0)
    {
        p=(Node*)malloc(sizeof(Node));
        p->num=b;
        p->next=cp;
        head=p;
    }
    else
    {
        p=(Node*)malloc(sizeof(Node));
        p->num=b;
        p->next=cp->next;
        cp->next=p;
    }
    //printf("%d",head->num);
}
void cut(int a,int b)
{
    int i;
    Node *p,*lp , *cp;
    p = head;
    cp = head;
    for(i=1;i<a;i++) p=p->next;
    for(i=0;i<a;i++) cp=cp->next;
    //printf("%d\n",cp->num);
    lp=cp;
    for(i=a;i<a+b-1;i++) lp=lp->next;
    //printf("%d\n",lp->num);
    if(a>0)
    {
        p->next=lp->next;
        lp->next=head;
        head=cp;
    }
}
