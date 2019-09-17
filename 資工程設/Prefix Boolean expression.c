#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int a,b,c,d;
typedef struct _node{
    char ch;
    struct _node *left;
    struct _node *right;
}Node;

/*Node* create(char c)
{
    Node* root;
    root = (Node*)malloc(sizeof(Node));
    root->ch=c;
    root->left=NULL;
    root->right=NULL;
}
Node* tree(Node *root)
{
    char cch = getchar();
    if((cch=='|')||(cch=='&')){
        root = create(cch);
        root->left = tree(root->left);
        root->right = tree(root->right);
    }
    else{
        root = create(cch);
    }
} runtime error*/
void tree(Node *root)
{
    char cch = getchar();
    if((cch=='|')||(cch=='&')){
        root->left = (Node*)malloc(sizeof(Node));
        root->right = (Node*)malloc(sizeof(Node));
        tree(root->left);
        tree(root->right);
    }
    else {
        root->left = NULL;
        root->right = NULL;
    }
    root->ch = cch;
}
void free_(Node *root)
{
    if(root!=NULL){
         free_(root->left);
         free_(root->right);
         free(root);
    }

}
int eval(Node *root)
{
    if(root->ch=='&'){
        return eval(root->left) && eval(root->right);
    }
    else if(root->ch=='|'){
        return eval(root->left) || eval(root->right);
    }
    else if(root->ch=='A'){
        return a;
    }
    else if(root->ch=='B'){
        return b;
    }
    else if(root->ch=='C'){
        return c;
    }
    else if(root->ch=='D'){
        return d;
    }
}
int main()
{
    Node *root;
    root = (Node*)malloc(sizeof(Node));
    tree(root);

    for(a=0;a<=1;a++){
        for(b=0;b<=1;b++){
            for(c=0;c<=1;c++){
                for(d=0;d<=1;d++){
                    printf("%d %d %d %d %d\n",a,b,c,d,eval(root));
                }
            }
        }
    }
    free_(root);
}
