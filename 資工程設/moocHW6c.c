#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define STR_EXPAND(tok) #tok
#define STR(tok) STR_EXPAND(tok)
#define STR_LEN 20

/* incomplete struct Atom */
struct Atom;

/* a pair of atom */
typedef struct Pair {
    struct Atom *left;
    struct Atom *right;
} Pair;

/* a list of atoms */
typedef struct List {
    struct Atom *data;
    struct List *next;
} List;

/* an atom can be a string, an int, a pair of atoms, or a list */
typedef struct Atom {
    char str[STR_LEN+1];
    int val;
    Pair *pair;
    List *lst;
    int dtype; /* 0 for string, 1 for int, 2 for pair, 3 for list*/
} Atom;



/* functions for creating an atom */
Atom* atom_str(char *str);
Atom* atom_val(int val);

Atom* copy_atom(Atom *aptr);
void print_atom(Atom *aptr);
void free_atom(Atom *atpr);

/* convert an atom to a single-atom list */
List* atom_to_list(Atom *a);

/* this function is important */
/* useful for creating a new copy of an existing list */
List* cons(Atom *a, List *b);

void print_list(List *lptr);
void free_list(List *lptr);
int length(List *lptr);
List* read_list_helper(List *l, int n);
List* read_list(void);

Atom* head(List *lptr);
List* tail(List *lptr);

List* zip(List *lptr1, List *lptr2);
Pair* unzip(List *lptr);

List* take(int n, List *l);
List* drop(int n, List *l);

Pair* pair_list(List *lptr1, List *lptr2);
Pair* split_at(int n, List *l);

void print_pair(Pair* p);
void free_pair(Pair* p);

int main(void)
{
    List *s1;
    Pair *p1;
    Atom *tmp;

    s1 = read_list();

    p1 = split_at(length(s1)/2, s1);
    tmp = p1->left;
    p1->left = p1->right;
    p1->right = tmp;



    print_pair(p1);
    printf("\n");


    return 0;
}

List* read_list_helper(List *l, int n)
{
    Atom *a;
    int x;
    char str[STR_LEN+1];
    List *l1, *l2;

    if (n==0) {
        return l;
    } else {
        if (scanf("%d", &x)==1) {
            a = atom_val(x);
        } else {
            scanf("%"STR(STR_LEN)"s", str);
            while(!isspace(getchar()));
            a = atom_str(str);
        }
        l1 = read_list_helper(l, n-1);
        l2 = cons(a, l1);
        free_list(l1);
        return l2;
    }
}

List* read_list(void)
{
    int ndata;

    scanf("%d", &ndata);

    return read_list_helper(NULL, ndata);
}
/* Given a string, create a new atom */
Atom* atom_str(char *str)
{
    Atom *aptr = (Atom*) malloc(sizeof(Atom));
    if (str==NULL) {
        aptr->str[0] = 'Θ';
    } else {
        strncpy(aptr->str, str, STR_LEN);
    }
    aptr->val = 0;
    aptr->pair = NULL;
    aptr->lst = NULL;
    aptr->dtype = 0;
    return aptr;
}

/* Given a value, create a new atom */
Atom* atom_val(int val)
{
    Atom *aptr = (Atom*) malloc(sizeof(Atom));
    aptr->str[0] = 'Θ';
    aptr->val = val;
    aptr->pair = NULL;
    aptr->lst = NULL;
    aptr->dtype = 1;
    return aptr;
}


Atom* copy_atom(Atom *aptr)
{
    Atom *aptr_new;

    aptr_new = (Atom*) malloc(sizeof(Atom));

    if (aptr_new==NULL) return NULL;
    if (aptr==NULL) return NULL;

    aptr_new->dtype = aptr->dtype;

    if (aptr->dtype == 0) {
        strncpy(aptr_new->str, aptr->str, STR_LEN);
    } else if (aptr->dtype == 1) {
        aptr_new->val = aptr->val;
    } else if (aptr->dtype == 2) {
        if (aptr->pair == NULL) {
            aptr_new->pair = NULL;
        } else {
            aptr_new->pair = (Pair *) malloc(sizeof(Pair));
            aptr_new->pair->left = copy_atom(aptr->pair->left);
            aptr_new->pair->right = copy_atom(aptr->pair->right);
        }
    } else if (aptr->dtype == 3) {
        if (aptr->lst==NULL) {
            aptr_new->lst = NULL;
        } else {
            aptr_new->lst = cons(head(aptr->lst), tail(aptr->lst));
        }
    }
    return aptr_new;
}

void print_atom(Atom *aptr)
{
    if (aptr==NULL) {
        printf("Empty");
        return;
    }
    switch (aptr->dtype) {
    case 0:
        printf("\"%s\"", aptr->str);
        break;
    case 1:
        printf("%d", aptr->val);
        break;
    case 2:
        print_pair(aptr->pair);
        break;
    case 3:
        print_list(aptr->lst);
        break;
    default:
        printf("Undefined.");
    }

}
/* Given an atom, create a list containing the atom. */
List* atom_to_list(Atom *a)
{
    List *b;
    b = (List*) malloc(sizeof(List));
    b->next = NULL;
    b->data = copy_atom(a);
    return b;
}

/* create a new list and add the atom to the head */
List* cons(Atom *a, List *b)
{
    List *c;

    c = atom_to_list(a);
    if (b!=NULL) {
        c->next = cons(head(b), tail(b));
    }

    return c;
}

void print_list(List *lptr)
{
    printf("[");
    while (lptr!=NULL) {
        print_atom(lptr->data);
        if (lptr->next != NULL)
            printf(",");
        lptr = lptr->next;
    }
    printf("]");
}

int len_helper(List *lptr, int len)
{
    if (lptr==NULL) return len;
    else return len_helper(lptr->next, len+1);
}
int length(List *lptr)
{
    return len_helper(lptr, 0);
}

void free_atom(Atom *aptr)
{
    if (aptr != NULL) {
        if (aptr->dtype==2) {
            free_pair(aptr->pair);
        } else if (aptr->dtype==3) {
            free_list(aptr->lst);
        }
        free(aptr);
    }
}

void free_list(List *lptr)
{
    List *p;
    if (lptr!=NULL) {
        p = tail(lptr);
        if (head(lptr)!=NULL) {
            free_atom(head(lptr));
        }
        free_list(p);
    }
}

Atom* head(List *lptr)
{
    return lptr->data;
}

List* tail(List *lptr)
{
    return (lptr==NULL) ? NULL : lptr->next;
}


List* take(int n, List *lptr)
{
    /*
    判斷 n 的值決定是否繼續
    利用 cons 搭配 take 的遞迴呼叫  建構出回傳的 list
    */
}

List* drop(int n, List *lptr)
{
    /*
    判斷 n 的值決定是否繼續
    利用 cons 搭配 drop 的遞迴呼叫  建構出回傳的 list
    */

}

Pair* pair_list(List *lptr1, List *lptr2)
{
    Pair *p;
    Atom a;

    p = (Pair*)malloc(sizeof(Pair));
    a.dtype = 3;

    a.lst = lptr1;
    p->left = copy_atom(&a);

    a.lst = lptr2;
    p->right = copy_atom(&a);

    return p;
}


Pair* split_at(int n, List *lptr)
{
    Pair *p;
    Atom a;
    /* 參考 pair_list 的寫法
    利用 take 和 drop 還有 copy_atom
    做出 split_at
    */


    return p;
}

void print_pair(Pair *p)
{
    printf("(");
    print_atom(p->left);
    printf(",");
    print_atom(p->right);
    printf(")");
}

void free_pair(Pair* p)
{
    if (p!=NULL) {
        free_atom(p->left);
        free_atom(p->right);
        free(p);
    }
}
