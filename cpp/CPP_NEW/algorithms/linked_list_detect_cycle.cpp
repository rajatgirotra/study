/*
detect and break cycle in link list
*/
#include <iostream>
#include <algorithm>
#include <random>
#include <iterator>
#include <array>
using namespace std;

struct node {
    int data {0};
    node* next {nullptr};

    explicit node(int arg) : data(arg), next(nullptr) {}
};

node* pushItem(node* head, int data) {
    node* newNode = new node(data);
    newNode->next = head;
    return newNode;
}

void printList(node* head) {
    int i = 20;
    node* curr = head;
    // dont print more than 20 items (to prevent a link list with cycle to keep endlessly printing)
    while(curr != nullptr && --i > 0 ) {
        cout << curr->data << "   ";
        curr = curr->next;
    }
    cout << endl;
}

void detect_and_break_cycle(node* head) {
    node* f = head, *s= head, *begin = head;
    while(f != nullptr) {
        f = f->next;
        if(f == nullptr) {
            cout << "No cycle. We are done!\n";
            return;
        }
        f = f->next;
        s = s->next;
        if (f == s) {
            // there is a cycle.
            break;
        }
    }

    if(f==s) {
        cout << "Cycle exists\n";
        while(begin->next != s->next) {
            begin = begin->next;
            s = s->next;
        }
        s->next = nullptr;
        cout << "Cycle broken\n";
    }
}

int main() {
    node* head = nullptr;
    for(int i = 12; i >= 1; --i) {
        head = pushItem(head, i);
    }

    printList(head);

    // now introduce a cycle: make the end of the link list point to 6th element.
    cout << "Introducing cycle\n";
    node* curr = head;
    for(int i = 0; i < 5; ++i) {
        curr = curr->next;
     }
    //  cout << "curr pointing to: " << curr->data << endl;

    node* end = head;
    while(end->next != nullptr) {
        end = end->next;
    }
    end->next = curr; // cycle introduced
    
    cout << "List with cycle\n";
    printList(head);

    detect_and_break_cycle(head);

    cout << "List with cycle broken\n";
    printList(head);
}