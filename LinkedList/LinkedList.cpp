#include <iostream>
using namespace std;

struct Node{    
    public:
        int data;
        Node* next; // may be null
};

class Queue{
    public:
      void insertFront(int data);
      void removeFront();
      void insertAny(Node *n, int data); //after Node n
      void removeAny(Node *n); //after Node n   
      void traverse(); // traverse the queue
      bool compare(Queue q1, Queue q2);
      void copy();
      void deleteQ();
    private:
        Node *front;
        Node *back;
        int size;
};

void Queue::insertFront(int newData){
    Node *n = new Node;
    n->data = newData;
    front = n;
    size++;
}

void Queue::removeFront(){
    Node *n = front;
    front = n->next;
    delete n;
    size--;
}

void Queue::insertAny(Node *p, int newdata){
    Node *n = new Node;
    n->data = newdata;

    if(p->next == nullptr){
        back = n;
    }
    else{
        n->next = p->next;
        p->next = n;
    }
    size++;
}

void Queue::removeAny(Node *p){
    Node *n = p->next;
    if(p->next == nullptr){
        back = p;
        delete p;
    }
    else{
        p->next = n->next;
        delete n;
    }   
    size--;
}

void Queue::traverse(){
    Node *n = front;
    while(n)
        n = n->next;
}

bool Queue::compare(Queue q1, Queue q2){
    Node *n1 = q1.front;
    Node *n2 = q2.front;

    while(n1 && n2){
        if(n1->data != n2->data){
            return false;
        }
        n1 = n1->next;
        n2 = n2->next;
    }
    return (n1 == n2);
}

void Queue::deleteQ(){
    Node *n = front;
    while(n){
        n = n->next;
        delete front;
        front = n;
    }
}

