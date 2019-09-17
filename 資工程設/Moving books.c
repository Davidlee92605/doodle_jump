#include <stdio.h>

#include <stdlib.h>


typedef struct _Node{

    int val;

    struct _Node* next;

} Node;


Node* table[25];

int position[25];


void resetBook(int p2) {
    Node *np,*nq;
    np = table[position[p2]];
    np = np->next;
    while(np->val!=p2){
        np =np->next;
    }
    //np = np->next;
    nq = np;
    while(np->next!=NULL){
        nq=np->next;
        position[nq->val]=nq->val;
        table[nq->val]->next = nq;
        np->next = nq->next;
        nq->next = NULL;
    }
}

void moveover(int p1,int p2){
    Node *np, *bnp ,*nb;
    np = table[position[p1]];
    nb = table[position[p2]];
   // nb = nb->next;
    while(np->next!=NULL){
        if(np->next->next==NULL){
            bnp = np;
        }
        np = np->next;
    }
    while(nb->next!=NULL){
        nb = nb->next;
    }
    bnp->next = NULL;
    nb->next = np;
    //np->next = NULL;
    position[p1] = position[p2];
}

void moveonto(int p1,int p2){
    Node *np, *bnp ,*nb ;
    np = table[position[p1]];
    nb = table[position[p2]];
    while(np->next!=NULL){
        if(np->next->next==NULL){
            bnp = np;
        }
        np = np->next;
    }
    while(nb->next!=NULL){
        nb = nb->next;
    }
    bnp->next = NULL;
    nb->next = np;
    //np->next = NULL;
    position[p1] = position[p2];
}

void pileover(int p1,int p2){
    Node *np,*bnp,*nb;
    np = table[position[p1]];
    //np = np->next;
    nb = table[position[p2]];
    while(np->val!=p1){
        if(np->next->val==p1){
            bnp = np;
        }
        np = np->next;
    }
    while(nb->next!=NULL){
        nb = nb->next;
    }
    bnp->next = NULL;
    nb->next = np;
    while(np!=NULL){
        position[np->val]=position[p2];
        np = np->next;
    }
}

void pileonto(int p1, int p2) {
    Node *np,*nb,*bnp;
    np = table[position[p1]];
    //np = np->next;
    nb = table[position[p2]];
    while(np->val!=p1){
        if(np->next->val==p1){
            bnp = np;
        }
        np = np->next;
    }
    while(nb->next!=NULL){
        nb = nb->next;
    }
    bnp->next = NULL;
    nb->next = np;
    while(np!=NULL){
        position[np->val]=position[p2];
        np = np->next;
    }
}

void initialize(int n) {
    Node *np;
    int i;
    for(i=0;i<n;i++){
        table[i] = (Node*)malloc(sizeof(Node));
        table[i]->next = (Node*)malloc(sizeof(Node));
        table[i]->val = 1000;
        position[i]= i;
        np = table[i];
        np = np->next;
        np->val = i;
        np->next = NULL;
    }
}


int main() {

    int n;

    int i;


    scanf("%d", &n);

    initialize(n);


    while(1){

        char input[100] = {0},input2[100] = {0};

        int p1, p2;

        scanf("%s", input);

        if(input[0] == 'e')

            break;

        scanf("%d", &p1);

        scanf("%s", input2);

        scanf("%d", &p2);

        if(position[p1] == position[p2])continue;

        else if(input[0]=='m'&&input2[1]=='n'){
            resetBook(p1);
            resetBook(p2);
            moveonto(p1,p2);
        }
        else if(input[0]=='m'&&input2[1]=='v'){
            resetBook(p1);
            moveover(p1,p2);
        }
        else if(input[0]=='p'&&input2[1]=='n'){
            resetBook(p2);
            pileonto(p1,p2);
        }
        else if(input[0]=='p'&&input2[1]=='v'){
            pileover(p1,p2);
        }

    }


    Node* tmp;

    for(i = 0; i < n; i++){

        printf("%d:", i);

        tmp = table[i]->next;

        while(tmp != NULL){

            printf(" %d", tmp->val);

            tmp = tmp->next;

        }

        printf("\n");

    }


        return 0;

}
