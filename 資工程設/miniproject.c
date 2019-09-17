#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAXLEN 256
#define TBLSIZE 65535

/*Something like Python
>> y = 2
>> z = 2
>> x = 3*y + 4/(2*z)

*/

/*
the only type: integer
everything is an expression
  statement   := END | expr END
  expr        := term expr_tail
  expr_tail   := ADDSUB term expr_tail | NIL
  term        := factor term_tail
  term_tail := MULDIV factor term_tail | NIL
  factor      := INT | ADDSUB INT | ADDSUB ID | ID ASSIGN expr | ID | LPAREN expr RPAREN
*/

//lex.h
typedef enum {UNKNOWN, END, INT, ID, ADDSUB, MULDIV, ASSIGN,
LPAREN, RPAREN, ENDFILE} TokenSet;

typedef struct _Node {
    char lexeme[MAXLEN];
    TokenSet data;
    int val;
    struct _Node *left, *right;
} BTNode;


 int match (TokenSet token);
 void advance(void);
 char* getLexeme(void);
//codeGen.h
 int evaluateTree(BTNode *root);
 void printPrefix(BTNode *root);
//parser.h
typedef enum {MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, REGFULL} ErrorType;

typedef struct {
    char name[MAXLEN];
    int val;
} Symbol;
Symbol table[TBLSIZE];





 int getval(char *nigga);
 int setval(char *str, int val);
 BTNode* makeNode(TokenSet tok, const char *lexe);
 void freeTree(BTNode *root);
 BTNode* factor(void);
 BTNode* term(void);
 BTNode* expr(void);
 void statement(void);
 void error(ErrorType errorNum);

//lex.c
static TokenSet getToken(void);
static TokenSet lookahead = UNKNOWN;
static char lexeme[MAXLEN];
//by myself
bool reg[8] = {false, false, false, false, false, false, false, false};
bool varyet = false;
bool assyet = false;
int end = 0;

TokenSet getToken(void)
{
    int i;
    char c;

    while ( (c = fgetc(stdin)) == ' ' || c== '\t' );  // ©¿²¤ªÅ¥Õ¦r¤¸

    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i<MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (c == '+' || c == '-') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return ADDSUB;
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '\n') {
        if(assyet == false)
        {
            //printf("SHIT22222\n");
            error(NOTNUMID);
        }
        lexeme[0] = '\0';
        return END;
    } else if (c == '=') {
        assyet = true;
        strcpy(lexeme, "=");
        return ASSIGN;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (isalpha(c) || c == '_') {
        if(assyet == false && varyet == true)
        {
            //printf("SHIT\n");
            error(NOTNUMID);
        }
        varyet = true;
        lexeme[0] = c;
        while ( (c = fgetc(stdin)) == ' ' || c== '\t' );
        i = 1;
        while (isalpha(c) || isdigit(c) || c == '_') {
            error(MISPAREN);
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
            return UNKNOWN;
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else if (c == EOF) {
        end = 1;
        return END;
    } else {
        return UNKNOWN;
    }
}

void advance(void)
{
    lookahead = getToken();
}

int match(TokenSet token)
{
    if (lookahead == UNKNOWN) advance();
    return token == lookahead;
}

char* getLexeme(void)
{
    return lexeme;
}
//lex.c down

//parser.c
int sbcount = 0;
int getval(char *nigga)
{
    int use_reg = 0;
    int value;

    if (match(INT)) {
        use_reg = unused();
        if(use_reg == -1)
        {
            error(REGFULL);
        }
        reg[use_reg] = true;
        value = atoi(getLexeme());
        printf("MOV r%d %d\n", use_reg, value);
    } else if (match(ID) || nigga!= NULL) { //&&&&&&&???
        if(strcmp(nigga, "x") == 0)
        {
            use_reg = unused();
            if(use_reg == -1)
            {
                error(REGFULL);
            }
            reg[use_reg] = true;
            printf("MOV r%d [0]\n", use_reg);
        }
        else if(strcmp(nigga, "y") == 0)
        {
            use_reg = unused();
            if(use_reg == -1)
            {
                error(REGFULL);
            }
            reg[use_reg] = true;
            printf("MOV r%d [4]\n", use_reg);
        }
        else //if(strcmp(nigga, "z") == 0)
        {
            use_reg = unused();
            if(use_reg == -1)
            {
                error(REGFULL);
            }
            reg[use_reg] = true;
            printf("MOV r%d [8]\n", use_reg);
        }
    }
    return use_reg;
}
int setval(char *str, int val)
{
    int i, retval;
    i = 0;
    while (i<sbcount) {
        if (strcmp(str, table[i].name)==0) {
            table[i].val = val;
            retval = val;
            break;
        } else {
            i++;
        }
    }
    return retval;
}
/* create a node without any child.*/
BTNode* makeNode(TokenSet tok, const char *lexe){
    BTNode *node = (BTNode*) malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}
/* clean a tree.*/
void freeTree(BTNode *root){
    if (root!=NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
/*factor := INT | ADDSUB INT | ADDSUB ID | ID ASSIGN expr | ID | LPAREN expr RPAREN*/
BTNode* factor(void)
{
    BTNode* retp = NULL;
    char tmpstr[MAXLEN];

    if (match(INT)) {
        retp =  makeNode(INT, getLexeme());
        retp->val = getval(retp->lexeme);
        advance();
    } else if (match(ID)) {
        BTNode* right = makeNode(ID, getLexeme());
        right->val = getval(right->lexeme);
        strcpy(tmpstr, getLexeme());
        advance();
        if (match(ASSIGN)) {
            retp = makeNode(ASSIGN, getLexeme());
            advance();
            retp->right = right;
            retp->left = expr();
            //printf("MOV r%d r%d\n", retp->left->val, retp->right->val);
            //reg[retp->right->val] = false;
            if(strcmp(tmpstr, "x") == 0)
            {
                printf("MOV [0] r%d\n", retp->left->val);
                reg[retp->left->val] = false;
            }
            else if(strcmp(tmpstr, "y") == 0)
            {
                printf("MOV [4] r%d\n", retp->left->val);
                reg[retp->left->val] = false;
            }
            else if(strcmp(tmpstr, "z") == 0)
            {
                printf("MOV [8] r%d\n", retp->left->val);
                reg[retp->left->val] = false;
            }
            //reg[retp->left->val] = false;
            varyet = false;
            assyet = false;
        } else {
            retp = right;
        }
    } else if (match(ADDSUB)) {
        strcpy(tmpstr, getLexeme());
        advance();
        if (match(ID) || match(INT)) {
            retp = makeNode(ADDSUB, tmpstr);
            if (match(ID))
            {
                retp->right = makeNode(ID, getLexeme());
                retp->right->val = getval(retp->lexeme);
            }
            else
            {
                retp->right = makeNode(INT, getLexeme());
                retp->right->val = getval(retp->right->lexeme);
            }
            retp->left = makeNode(INT, "0");
            retp->left->val = unused();
            reg[retp->left->val] = true;
            if(strcmp(tmpstr, "-") == 0)
            {
                printf("MOV r%d 0\n", retp->left->val);
                printf("SUB r%d r%d\n", retp->left->val, retp->right->val);
                //printf("MOV r%d -%d\n", retp->left->val, atoi(retp->right->lexeme));
            }/*else{
                printf("MOV r%d, 0\n", retp->left->val);
                printf("ADD r%d, r%d\n", retp->left->val, retp->right->val);
            }*/

            reg[retp->right->val] = false;
            advance();
            retp = retp->left;
        } else {
            //printf("SHIT\n");
            error(NOTNUMID);
        }
    } else if (match(LPAREN)) {
        advance();
        retp = expr();
        if (match(RPAREN)) {
            advance();
        } else {
            error(MISPAREN);
        }
    } else {
        //printf("SHIT\n");
        error(NOTNUMID);
    }
    return retp;
}
/*  term        := factor term_tail
    term_tail := MULDIV factor term_tail | NIL*/
BTNode* term(void)
{
    BTNode *retp, *left;
    retp = left = factor();

    while (match(MULDIV)) {
        retp = makeNode(MULDIV, getLexeme());
        if(strcmp(retp->lexeme, "*") == 0)
        {
            advance();
            retp->right = factor();
            retp->left = left;
            //left = retp;
            reg[retp->left->val] = true;
            printf("MUL r%d r%d\n", retp->left->val, retp->right->val);
            reg[retp->right->val] = false;
        }
        else if(strcmp(retp->lexeme, "/") == 0)
        {
            advance();
            retp->right = factor();
            retp->left = left;
            //left = retp;
            reg[retp->left->val] = true;
            printf("DIV r%d r%d\n", retp->left->val, retp->right->val);
            reg[retp->right->val] = false;
        }
    }
    retp = left;
    return retp;
}
/*  expr        := term expr_tail
  expr_tail   := ADDSUB term expr_tail | NIL*/
BTNode* expr(void)
{
    BTNode *retp, *left;
    retp = left = term();
    while (match(ADDSUB)) {
        retp = makeNode(ADDSUB, getLexeme());
        if(strcmp(retp->lexeme, "+") == 0)
        {
            advance();
            retp->right = term();
            retp->left = left;
            reg[retp->left->val] = true;
            printf("ADD r%d r%d\n", retp->left->val, retp->right->val);
            reg[retp->right->val] = false;
        }
        else if(strcmp(retp->lexeme, "-") == 0)
        {
            advance();
            retp->right = term();
            retp->left = left;
            reg[retp->left->val] = true;
            printf("SUB r%d r%d\n", retp->left->val, retp->right->val);
            reg[retp->right->val] = false;
        }

        //left = retp;
    }
    retp = left;
    return retp;
}
/*statement   := END | expr END*/
void statement(void)
{
    BTNode* retp;

    if (match(END)) {
        //printf(">> ");
        advance();
    } else {
        retp = expr();
        if (match(END)) {
            freeTree(retp);
            //printf(">> ");
            advance();
        }
    }
}
void error(ErrorType errorNum)
{
    /*switch (errorNum) {
    case MISPAREN:
        fprintf(stderr, "Mismatched parenthesis\n");
        break;
    case NOTNUMID:
        fprintf(stderr, "Number or identifier expected\n");
        break;
    case NOTFOUND:
        fprintf(stderr, "%s not defined\n", getLexeme());
        break;
    case RUNOUT:
        fprintf(stderr, "Out of memory\n");
    }*/
    printf("EXIT 1\n");
    exit(0);
}
//parser.c down

//codeGen.c
int evaluateTree(BTNode *root)
{
    static int i=0;
    static int start = 0;
    int retval = 0, lv, rv;
    if (root != NULL)
    {
        switch (root->data)
        {
        case ID:
        case INT:
            retval = root->val;
            if(start == 1)
            {
                printf("MOV r%d %d\n", i++, root->val);
            }
            start = 1;
            break;
        case ASSIGN:
        case ADDSUB:
        case MULDIV:
            lv = evaluateTree(root->left);
            rv = evaluateTree(root->right);
            if (strcmp(root->lexeme, "+") == 0)
                retval = lv + rv;
            else if (strcmp(root->lexeme, "-") == 0)
                retval = lv - rv;
            else if (strcmp(root->lexeme, "*") == 0)
                retval = lv * rv;
            else if (strcmp(root->lexeme, "/") == 0)
                retval = lv / rv;
            else if (strcmp(root->lexeme, "=") == 0)
                retval = setval(root->left->lexeme, rv);
            break;
        default:
            retval = 0;
        }
    }
    return retval;
}


/* print a tree by pre-order. */
void printPrefix(BTNode *root)
{
    if (root != NULL)
    {
        printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}
//codeGen.c down

int unused(void)
{
    int i;
    for(i=0; i<7; i++)
    {
        if(reg[i] == false)
        {
            return i;
        }
    }
    return -1;
}

//main.c
int main()
{
    //printf(">> ");
    while (1) {
        statement();
        if(end) break;
    }

    printf("MOV r0 [0]\n");
    printf("MOV r1 [4]\n");
    printf("MOV r2 [8]\n");
    printf("EXIT 0\n");
    return 0;
}




