#include<iostream>
#include<string.h>
//#include "function.h"
using namespace std;

class ListNode
{
    friend class List_stack; //make List_stack a friend
    public:
        ListNode( const int &info ) //constructor
        : data( info ), nextPtr( NULL ), prevPtr( NULL )
        {
        } //end ListNode constructor

    private:
        int data; //data
        ListNode *nextPtr; // next node in list
        ListNode *prevPtr;
}; //end class ListNode

class List_stack {
    public:
        List_stack();
        ~List_stack();
        void push(const int &);
        void pop();
        void print();
    private:
        ListNode *head;
        ListNode *tail;
};
List_stack::List_stack()
{
    head = NULL;
    tail = NULL;
}
List_stack::~List_stack()
{
    ListNode *np;
    while(head!=NULL)
    {
        np = head;
        head = head->nextPtr;
        delete np;
    }
}
void List_stack::push(const int &num)
{
    ListNode *np;
    np = new ListNode(num);
    if(head==NULL){
        np->nextPtr = NULL;
        np->prevPtr = NULL;
        head = np;
        tail = np;
    }
    else{
        tail->nextPtr = np;
        np->nextPtr = NULL;
        np->prevPtr = tail;
        tail = np;
    }
}
void List_stack::pop()
{
    ListNode *np;
    if(tail==head){
        np = tail;
        delete np;
        tail = NULL;
        head = NULL;
    }
    else{
        np = tail;
        tail = tail->prevPtr;
        delete np;
        tail->nextPtr = NULL;
    }
}
void List_stack::print()
{
    ListNode *np;
    np = tail;
    if(np!=NULL){
        cout<<np->data;
        np=np->prevPtr;
        while(np!=NULL){
            cout<<" "<<np->data;
            np = np->prevPtr;
        }
    }
}
int main(){
    List_stack L_stack;
    char command[10];
    int n;
    while(cin>>command){

        if(strcmp(command,"pop")==0){
            L_stack.pop();
        }else if(strcmp(command,"push")==0){
            cin >> n;
            L_stack.push(n);
        }else if(strcmp(command, "print") == 0){
            L_stack.print();
            cout << endl;
        }
    }
    return 0;
}
