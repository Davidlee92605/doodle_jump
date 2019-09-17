#include<stdio.h>
#include<stdlib.h>
char sym[10],expr[256];
int pos;
typedef struct _node{
    char data;
    struct _node *right;
    struct _node *left;
}Node;
Node* FACTOR();
Node* EXPR();
Node* makeNode(char c);
Node* makeNode(char c)
{
    int i;
    Node *node;
    node = (Node*)malloc(sizeof(Node));
    node->data = c;
    node->left = NULL;
    node->right = NULL;
    return node;
}
Node* EXPR()
{
    char c;
    Node *right=NULL , *node=NULL;
    if(pos>=0){
        right = FACTOR();
        if(pos>0){
            c = expr[pos];
            if(c=='&'||c=='|'){
                node = makeNode(c);
                node->right = right;
                pos--;
                node->left = EXPR();
            }
            else{
                node = right;
            }
        }
        else{
            node = right;
        }
    }
    return node;
}
Node* FACTOR()
{
    char c;
    Node *node = NULL;
    if (pos>=0){
        c = expr[pos--];
        if(c>='A'&&c<='D'){
            node = makeNode(c);
        }
        else if(c==')'){
            node = EXPR();
            if(expr[pos--]!='('){
                printf("error\n");
                freeTree(node);
            }
        }
    }
    return node;
}
void printInfix(Node* root)
{
    if(root!=NULL){
        printInfix(root->left);
        printf("%c",root->data);
        if(root->data=='|'||root->data=='&'){
            if(root->right->data=='|'||root->right->data=='&'){
                printf("(");
            }
        }
        printInfix(root->right);
        if(root->data=='|'||root->data=='&'){
            if(root->right->data=='|'||root->right->data=='&'){
                printf(")");
            }
        }
    }
}
void freeTree(Node* root)
{
    if(root!=NULL){
        free(root->left);
        free(root->right);
        free(root);
    }
}
int main(void)
{
    sym[0]='A';
    sym[1]='B';
    sym[2]='C';
    sym[3]='D';
    sym[4]='&';
    sym[5]='|';
    while(scanf("%s",expr)!=EOF){
        pos = strlen(expr)-1;
        Node* root = EXPR();
        printInfix(root);
        freeTree(root);
    }

}
