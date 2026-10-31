#include <bits/stdc++.h>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int _data, Node* _next = nullptr): data(_data), next(_next) {};
};

class LinkedList {
    Node* head;

    public:
    LinkedList(): head(nullptr) {};
    void insertFirst(int data) {
        head = new Node(data, head);
    }

    void insertPos(int data, int pos) {
        Node* temp = head;

        for (int i = 1; i < (pos - 1); i++) {
            temp = temp -> next;
        }
        Node* newNode = new Node(data, temp -> next);
        temp -> next = newNode;
    }

    void insertLast(int data) {
        Node* temp = head;
        
        while (temp -> next) {
            temp = temp -> next;
        }
        Node* newNode = new Node(data, nullptr);
        temp -> next = newNode;
    }

    void deleteFirst() {
        Node* temp = head;
        head = head -> next;
        delete temp;
    }

    void deletePos(int pos) {
        Node *temp = head;

        for (int i = 1; i < (pos - 1); i++) {
            temp = temp -> next;
            if (temp -> next == NULL) {
                return;
            }
        }
        Node *newNode = temp -> next;
        temp -> next = newNode -> next;
        delete newNode;
    }

    void deleteLast() {
        Node *temp = head;

        while (temp -> next -> next) {
            temp = temp -> next;
        }
        Node* newNode = temp -> next;
        temp -> next = NULL;
        delete newNode;
    }

    void print() {
        Node* temp = head;
        while (temp) {
            cout << temp -> data << ' ';
            temp = temp -> next;
        }
    }

    int search(int data) {
        int pos = 0;
        Node *temp = head;

        while (temp) {
            pos++;

            if (temp -> data == data) {
                return pos;
            }
            temp = temp -> next;
        }
    }
};

signed main() {
    LinkedList test;
    test.insertFirst(5);
    test.insertFirst(10);
    test.insertLast(9);
    test.deletePos(2);
    test.print();
}