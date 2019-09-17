#include<iostream>
#include<string.h>
#include "function.h"

using namespace std;

class ListNode
{
    friend class List_queue; //make List_queue a friend
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

class List_queue {
    public:
        List_queue();
        ~List_queue();
        void enqueue(const int &);
        void dequeue();
        void print();
    private:
        ListNode *head;
        ListNode *tail;
};
List_queue::List_queue()
{
    head = NULL;
    tail = NULL;
}
List_queue::~List_queue()
{
    ListNode *np;
    while(head!=NULL)
    {
        np = head;
        head = head->nextPtr;
        delete np;
    }
}
void List_queue::enqueue(const int&num)
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
        np->prevPtr = tail;
        np->nextPtr = NULL;
        tail = np;
    }
}
void List_queue::dequeue()
{
    ListNode *np;
    if(head!=NULL){
        np = head;
        head = head->nextPtr;
        delete np;
    }
}
void List_queue::print()
{
    ListNode *np;
    np = head;
    while(np!=NULL){
        if(np->nextPtr==NULL){
            cout<<np->data;
        }
        else{
            cout<<np->data<<" ";
        }
        np = np->nextPtr;
    }
}
int main(){
    List_queue L_queue;
    char command[10];
    int n;
    while(cin>>command){

        if(strcmp(command,"dequeue")==0){
            L_queue.dequeue();
        }else if(strcmp(command,"enqueue")==0){
            cin >> n;
            L_queue.enqueue(n);
        }else if(strcmp(command, "print") == 0){
            L_queue.print();
            cout << endl;
        }
    }
    return 0;
}
