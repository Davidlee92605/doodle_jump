#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int N,length;
char expr[300001];
static int pos=-1;
typedef struct _node{
    char chr;
    struct _node *left,*right;
}Node;

void construct(Node *root)
{
    int i;
    pos++;
    if(expr[pos]=='+'||expr[pos]=='-'||expr[pos]=='*'){
        if(pos<length){
            root->chr = expr[pos];
            root->left = (Node*)malloc(sizeof(Node));
            root->right = (Node*)malloc(sizeof(Node));
            construct(root->left);
            construct(root->right);
        }
    }
    else{
        if(pos<length){
            root->chr = expr[pos];
            root->left = NULL;
            root->right = NULL;
        }
    }
}
int eval(Node* root)
{
    if(root->chr=='*'){
        return eval(root->left)*eval(root->right);
    }
    else if(root->chr=='-'){
        return eval(root->left)-eval(root->right);
    }
    else if(root->chr=='+'){
        return eval(root->left)+eval(root->right);
    }
    else if(root->chr=='1'){
        return 1;
    }
    else if(root->chr=='2'){
        return 2;
    }
    else if(root->chr=='3'){
        return 3;
    }
    else if(root->chr=='4'){
        return 4;
    }
    else if(root->chr=='5'){
        return 5;
    }
    else if(root->chr=='6'){
        return 6;
    }
    else if(root->chr=='7'){
        return 7;
    }
    else if(root->chr=='8'){
        return 8;
    }
    else if(root->chr=='9'){
        return 9;
    }
}

/*Node* makeNode(int num)
{
    Node *node;
    node = (Node*)malloc(sizeof(Node));
    node->num = num;
    node->left = NULL;
    node->right = NULL;
    return node;
}
*/
int main(void)
{
    Node *root;
    root=(Node*)malloc(sizeof(Node));
    int i=0;
    scanf("%d",&N);
    getchar();
    while(scanf("%c",&expr[i])){
        if(expr[i]=='\n'){
            break;
        }
        i++;
    }
    length = i;
    construct(root);
    printf("%d\n",eval(root)%10007);
    //printf("%c\n",root->chr);
    free_(root);
    //printf("%d",i);
    for(i=0;i<N;i++){
        Node *node;
        node=(Node*)malloc(sizeof(Node));
        int a,b,j,k=0;
        scanf("%d%d",&a,&b);
        for(j=0;j<length-b;j++){
            expr[a+j-1]=expr[b+j];
        }
        length = length-(b-a+1);
        pos = -1;
        construct(node);
        printf("%d\n",eval(node)%10007);
        //printf("%c\n",node->chr);
        free_(node);
    }
}
void free_(Node *root)
{
    if(root!=NULL){
         free_(root->left);
         free_(root->right);
         free(root);
    }

}
