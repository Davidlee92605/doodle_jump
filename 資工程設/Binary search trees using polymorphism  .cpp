#include <iostream>
#include <string.h>
#include "function.h"
#include <math.h>
using namespace std;

class BST{
public:
    BST():Height(0){}
    virtual ~BST() {}
    virtual void insert(const int &) = 0;
    virtual bool search(const int &) const = 0;
    virtual void print() const = 0;
    int height() const { return Height; }// An empty tree has height of 0. A tree with only root node has height of 1.

protected:
    int Height;
};

class Array_BST : public BST{
public:
    Array_BST();
    virtual ~Array_BST() {}
    virtual void insert(const int &) override; //root node is stored at index 1.
    virtual bool search(const int &) const override;
    virtual void print() const override{
        int k = pow(2, height());
        for (int i = 1; i <= k-1; i++) {
            if (array[i] != 0)
                cout << array[i] << " ";
        }
    }

private:
    int array[1025];
};

class ListNode{
    friend class List_BST; //make List_BST a friend

public:
    ListNode(const int &info):key( info ),left( NULL ),right( NULL ) //constructor
    {
    }//end ListNode constructor

private:
    int key;
    ListNode *left;
    ListNode *right;
};//end class ListNode

class List_BST : public BST{
public:
    List_BST();
    virtual ~List_BST()
    {
        deleteTree(root);
    }
    virtual void insert(const int &) override;
    virtual bool search(const int &) const override;
    virtual void print() const override{
        int i;
        for(i = 1; i <= Height; i++){
            printGivenLevel(root, i);
        }
    }

private:
    ListNode *root;
    // private member functions
    ListNode* createLeaf(int key) const; //new a ListNode and return its address
    /* clean a tree.*/
    void deleteTree(ListNode *root);

    void printGivenLevel(ListNode* Ptr, int level) const {
        if (Ptr == NULL)
            return;
        if (level == 1)
            cout << Ptr->key << " ";
        else if (level > 1)
        {
            printGivenLevel(Ptr->left, level-1);
            printGivenLevel(Ptr->right, level-1);
        }
    }
};
void BSTManipulator(BST& bstobj1,BST& bstobj2, char cmd ){
    int n;
    if (cmd == 'I') {
        cin >> n;
        bstobj1.insert(n);
        bstobj2.insert(n);
    }else if (cmd == 'S'){
        cin >> n;
        if (bstobj1.search(n)) {
            cout << "yes" << endl;
        }else{
            cout << "no" << endl;
        }

        if (bstobj2.search(n)) {
            cout << "yes" << endl;
        }else{
            cout << "no" << endl;
        }

    }else if (cmd == 'H'){
        cout << bstobj1.height() << endl;;
        cout << bstobj2.height() << endl;;

    }else if (cmd == 'P'){
        bstobj1.print();
        cout << endl;
        bstobj2.print();
        cout << endl;
    }
}

Array_BST::Array_BST()
{
    for(int i=0;i<1025;i++){
        array[i] = 0;
    }
}
List_BST::List_BST()
{
    root = NULL;
}
bool Array_BST::search(const int &key) const
{
    int index = 1;
    while(array[index]!=0){
        if(array[index]==key) return true;
        else if (key > array[index]) index = index*2 + 1;
        else if (key < array[index]) index = index*2;
    }
    return false;
}
bool List_BST::search(const int &key) const
{
    ListNode *temp = root;
    while(temp != NULL){
        if(temp->key == key) return true;
        else if(temp->key > key) temp = temp->left;
        else if(temp->key < key) temp = temp->right;
    }
    return false;
}
void Array_BST::insert(const int &key)
{
    int index = 1;
    int new_height = 0;
    while(array[index] != 0){
        if(array[index]==key){
            return;
        }
        else{
            if(key<array[index]) index = 2*index;
            else index = 2*index+1;
            new_height += 1;
        }
    }
    array[index] = key;
    new_height += 1;
    if(new_height > Height)
        Height = new_height;
}
void List_BST::insert(const int &x)
{
    int new_height = 0;
    if(root == NULL){
        root = createLeaf(x);
        new_height+=1;
    }
    else{
        ListNode *p = root;
        ListNode *r = NULL;
        while(p!=NULL){
            if(p->key == x)
                return;
            else{
                r = p;
                if(x < p->key){
                    p = p->left;
                }
                else{
                    p = p->right;
                }
                new_height+=1;
            }
        }
        if(x>r->key) r->right = createLeaf(x);
        else r->left = createLeaf(x);
        new_height += 1;
    }
    if(new_height>Height)
        Height = new_height;
}
ListNode* List_BST::createLeaf(int key) const
{
    ListNode *temp;
    temp = new ListNode(key);
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}
void List_BST::deleteTree(ListNode *temp)
{
    if(temp == NULL)return;
    deleteTree(temp->left);
    deleteTree(temp->right);
    delete temp;
}
int main(){
    Array_BST A_bst;
    List_BST B_bst;
    char cmd;

    while (cin >> cmd)
        BSTManipulator(A_bst, B_bst, cmd);

    return 0;
}
