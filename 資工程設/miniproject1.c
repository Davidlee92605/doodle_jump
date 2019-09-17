#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TBLSIZE 65535
#define MAXLEN 256

typedef enum {MISPAREN, NOTNUMID, NOTFOUND, RUNOUT, NAN, REGFULL} ErrorType;
typedef enum {UNKNOWN, END, INT, ID, ADDSUB, MULDIV, ASSIGN, LPAREN, RPAREN} TokenSet;
typedef struct {
    char name[MAXLEN];
    int val;
}Symbol;

typedef struct _Node{
    char lexeme[MAXLEN];
    TokenSet token;
    int val;
    struct _Node *left, *right;
}BTNode;

Symbol table[TBLSIZE];

int reg[8];
int end=0;
int var=0;
int assign_use=0;//if appear '=' change to 1;
//int sbcount=0;
static TokenSet lookahead=UNKNOWN;
static char lexeme[MAXLEN];

//Function Declaration
BTNode* expr(void);//handle + -
BTNode* term(void);//handle * /
BTNode* factor(void);
BTNode* makeNode(TokenSet token, const char *lexe);

int match(TokenSet token);
int getval(char *str);
//int setval(char*, int);
int unreg(void);
char* getLexeme(void);
static TokenSet getToken(void);
int unused(void);

void advance(void);//read next
void statement(void);
void freeTree(BTNode *root);
void error(ErrorType errorNum);
//Given
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
    }
    else if (c == '+' || c == '-') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return ADDSUB;
    }
    else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    }
    else if (c == '\n') {
        if(assign_use==0)    error(NOTNUMID);//no '='
        lexeme[0] = '\0';
        return END;
    }
    else if (c == '=') {
        assign_use = 1;
        strcpy(lexeme, "=");
        return ASSIGN;
    }
    else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    }
    else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    }
    else if (isalpha(c) || c == '_') {
        if(assign_use==0&&var==1)    error(NOTNUMID);
        var = 1;
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
    }
    else if(c ==EOF ){
        end = 1;
        return END;
    }
    else {
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

//expr        := term expr_tail
//expr_tail   := ADDSUB term expr_tail | NiL
BTNode* expr(void)
{
    BTNode *retp, *left;
    left=term();
    retp=left;
    while(match(ADDSUB)){
        retp=makeNode(ADDSUB, getLexeme());
        if(strcmp(retp->lexeme, "+")==0){
            advance();
            retp->right=term();
            retp->left=left;
            reg[retp->left->val]=1;//be used
            printf("ADD r%d r%d\n", retp->left->val, retp->right->val);
            reg[retp->right->val]=0;
        }
        else if(strcmp(retp->lexeme, "-")==0){
            advance();
            retp->right=term();
            retp->left=left;
            reg[retp->left->val]=1;
            printf("SUB r%d r%d\n", retp->left->val, retp->right->val);
            reg[retp->right->val]=0;
        }
    }
    retp=left;
    return retp;
}
//term        := factor term_tail
//term_tail   := MULDIV factor term_tail | NiL
BTNode* term(void)
{
    BTNode *retp, *left;
    left=factor();
    retp=left;
    while(match(MULDIV)){
        retp=makeNode(MULDIV, getLexeme());
        if(strcmp(retp->lexeme, "*")==0){
            advance();
            retp->right=factor();
            retp->left=left;
            reg[retp->left->val]=1;
            printf("MUL r%d r%d\n", retp->left->val, retp->right->val);
            reg[retp->right->val]=0;
        }
        else if(strcmp(retp->lexeme, "/")==0){
            advance();
            retp->right=factor();
            retp->left=left;
            reg[retp->left->val]=1;
            printf("DIV r%d r%d\n", retp->left->val, retp->right->val);
            reg[retp->right->val]=0;
        }
    }
    retp=left;
    return retp;
}

//factor      := INT | ADDSUB INT | ID | ADDSUB ID| LPAREN expr RPAREN| ID ASSIGN expr
BTNode* factor(void)
{
    BTNode* retp=NULL;
    char tmp[MAXLEN];

    if(match(INT)){
        retp=makeNode(INT, getLexeme());
        retp->val=getval(retp->lexeme);
        advance();
    }
	else if(match(ID)){
        BTNode* left=makeNode(ID, getLexeme());
        left->val=getval(left->lexeme);
        strcpy(tmp, getLexeme());
        advance();
        if(match(ASSIGN)){
            retp=makeNode(ASSIGN, getLexeme());
            advance();
            retp->right=expr();
            retp->left=left;
            printf("MOV r%d r%d\n", retp->left->val, retp->right->val);
            reg[retp->right->val]=0;
            if(strcmp(tmp, "x")==0){
                printf("MOV [0] r%d\n", retp->left->val);
            }//x = ?
			else if(strcmp(tmp, "y")==0){
                printf("MOV [4] r%d\n", retp->left->val);
            }//y = ?
			else if(strcmp(tmp, "z")==0){
                printf("MOV [8] r%d\n", retp->left->val);
            }//z = ?
            reg[retp->left->val]=0;
            var=0;
            assign_use=0;
        }
        else{
            retp=left;
        }
    }
	else if(match(ADDSUB)){
        strcpy(tmp, getLexeme());
        advance();
        if(match(ID)||match(INT)){
            retp=makeNode(ADDSUB, tmp);
            if(match(ID)){
                retp->right=makeNode(ID, getLexeme());
                retp->right->val=getval(retp->lexeme);
            }
            else{
                retp->right=makeNode(INT, getLexeme());
                retp->right->val=getval(retp->right->lexeme);
            }
            retp->left=makeNode(INT, "0");
            retp->left->val=unused();
            reg[retp->left->val]=1;
            if(strcmp(tmp, "-")==0){
                printf("MOV r%d 0\n", retp->left->val);
                printf("SUB r%d r%d\n", retp->left->val, retp->right->val);
            }
            else{
                printf("MOV r%d 0\n", retp->left->val);
                printf("ADD r%d r%d\n", retp->left->val, retp->right->val);
            }

            reg[retp->right->val]=0;
            advance();
            retp=retp->left;
        }
        else{
            error(NOTNUMID);
        }
    }else if(match(LPAREN)){
        advance();
        retp=expr();
        if(match(RPAREN)){
            advance();
        }
        else{
            error(MISPAREN);
        }
    }
    else{
        error(NOTNUMID);
    }
    return retp;
}

void error(ErrorType errorNum)
{
    printf("EXIT 1\n");
    exit(0);
}

//statement   := ENDFILE | END | expr END
void statement(void)
{
    BTNode* retp;
    if(match(END)){
        advance();
    }
    else{
        retp=expr();
        if(match(END)){
            freeTree(retp);
            advance();
        }
    }
}

//Given
BTNode* makeNode(TokenSet tok, const char *lexe)
{
    BTNode *node = (BTNode*) malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->token= tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(BTNode *root)
{
    if (root!=NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}



int getval(char *str)
{
    int reg_used=0, value;

    if (match(INT)) {
        reg_used = unused();
        if(reg_used==-1) error(REGFULL);
        reg[reg_used] = 1;
        value = atoi(getLexeme());
        printf("MOV r%d %d\n", reg_used, value);
    }
    else if (match(ID)||str!=NULL) {
        if(strcmp(str, "x")==0){
            reg_used = unused();
            if(reg_used==-1) error(REGFULL);
            reg[reg_used] = 1;
            printf("MOV r%d [0]\n", reg_used);
        }
        else if(strcmp(str, "y")==0){
            reg_used = unused();
            if(reg_used==-1) error(REGFULL);
            reg[reg_used] = 1;
            printf("MOV r%d [4]\n", reg_used);
        }
        else {
            reg_used = unused();
            if(reg_used==-1) error(REGFULL);
            reg[reg_used] = 1;
            printf("MOV r%d [8]\n", reg_used);
        }
    }
    return reg_used;
}

/*int setval(char *str, int val){
    int i, reg_used = 0;
    i = 0;
    while (i<sbcount) {
        if (strcmp(str, table[i].name)==0) {
            table[i].val = val;
            reg_used = val;
            break;
        } else {
            i++;
        }
    }
    return reg_used;
}*/
//Given End


//Given end

int unused(void)
{
    int i;
    for( i=0; i<7; i++){
        if(!reg[i]){
            return i;
        }
    }
    return -1;
}


int main(void)
{
    while(1){
        statement();
        if(end) break;
    }

    printf("MOV r0 [0]\n");
    printf("MOV r1 [4]\n");
    printf("MOV r2 [8]\n");
    printf("EXIT 0\n");
    return 0;
}





