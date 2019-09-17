#include<stdio.h>
#include<stdlib.h>

typedef struct vector{
 long long int dim;
 long long int value;
 struct vector *next;
}Vector;

Vector* read_vector(){
 Vector *np, *vtr;
 long long int a, b;

 vtr = (Vector *)malloc(sizeof(Vector));
 np = vtr;
 scanf("%lld:%lld", &a, &b);
 np->dim = a;
 np->value = b;
 while(1){
  scanf("%lld:%lld", &a, &b);
  if(a == 0 && b==0)break;
  else{
   np->next = (Vector *)malloc(sizeof(Vector));
   np = np->next;
   np->dim = a;
   np->value = b;
  }
 }
 np->next = NULL;

 return vtr;
}

void free_vector(Vector *vtr){
 Vector *np, *nq;
 np = vtr;
 while(np!=NULL){
  nq = np;
  np = np->next;
  free(nq);
 }
}

void print_vector(Vector *vtr){
 Vector *np;
 np = vtr;
 while(np!=NULL){
  printf("dim: %lld, value: %lld", np->dim, np->value);
  np = np->next;
 }
}

int main(void){
 Vector *one, *two, *np, *nq;
 long long int ans = 0;

 one = read_vector();
 two = read_vector();

// print_vector(one);
// print_vector(two);


 np = one;
 nq = two;
 while(np!=NULL){
  while(nq!=NULL){
   if(np->dim == nq->dim){
    ans+=(np->value)*(nq->value);
   }
   nq = nq->next;
  }
  nq = two;
  np = np->next;
 }

 printf("%lld\n", ans);
 free_vector(one);
 free_vector(two);

 return 0;
}
