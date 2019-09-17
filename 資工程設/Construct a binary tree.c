#include<stdio.h>
#include<stdlib.h>
int inorder[200005],preorder[200005],postorder[200005],pos[200005];
typedef struct _node{
    int num;
    struct _node *right;
    struct _node *left;
}Node;

Node* create(int n){
    Node *root;
    root = (Node*)malloc(sizeof(Node));
    root->num = n;
    root->left = NULL;
    root->right = NULL;
    return root;
}
void destroy(Node* root)
{
    free(root);
}
void post_order(Node* root)
{
    if(root!=NULL) {
        post_order(root->left);
        post_order(root->right);
        printf("%d ",root->num);
        destroy(root);
    }
}
Node *build(int *inorder, int *preorder, int inorder_start, int inorder_end) {
          static int preorder_idx = 0;
          // basis step
          if (inorder_start > inorder_end) return NULL;
          Node *node = create(preorder[preorder_idx++]);
          if (inorder_start == inorder_end) return node;

          int inorder_idx = -1 ;
          inorder_idx = pos[preorder[preorder_idx+inorder_idx]];
          /* In inorder array, find the index of root */
          /*YOUR CODE */

          // recursive step
          node->left = build(inorder, preorder, inorder_start, inorder_idx-1);
          node->right = build(inorder, preorder, inorder_idx+1, inorder_end);
          return node;
 }

int main(){
    int N,i;
    scanf("%d",&N);
    for(i=0;i<N;i++)
    {
        scanf("%d",&inorder[i]);
        pos[inorder[i]] = i;
    }
    for(i=0;i<N;i++)
    {
        scanf("%d",&preorder[i]);
    }
    post_order(build(inorder,preorder,0,N-1));
    printf("\n");
}
