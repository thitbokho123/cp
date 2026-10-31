#include <bits/stdc++.h>
using namespace std;

class Node {
    public:
        int data;
        Node* left;
        Node* right;
        Node(int _data, Node* _left = NULL, Node* _right = NULL): data(_data), left(_left), right(_right) {}
};

void traverseInorder(Node *head) {
    if (head == NULL) return;
    traverseInorder(head -> left);
    cout << head -> data << ' ';
    traverseInorder(head -> right);
}

Node* search(Node *head, int data) {
    if (head == NULL) {
        return NULL;
    }
    if (data < head -> data) {
        return search(head -> left, data);
    } else if (data > head -> data) {
        return search(head -> right, data);
    } else {
        return head;
    }
}

void insert(Node *&head, int data) {
    if (head == NULL) {
        head = new Node(data);
        return;
    }
    if (data < head -> data) {
        insert(head -> left, data);
    } else if (data > head -> data) {
        insert(head -> right, data);
    }
}

Node* findMax(Node *head) {
    while (head -> right) {
        head = head -> right;
    }
    return head;
}

void remove(Node *&head, int data) {
    if (head == NULL) return;
    if (data < head -> data) {
        remove(head -> left, data);
    } else if (data > head -> data) {
        remove(head -> right, data);
    } else {
        if (head -> right == NULL && head -> left == NULL) {
            delete head;
        } else if (head -> right == NULL) {
            Node *temp = head;
            head = head -> left;
            delete temp;
        } else if (head -> left == NULL) {
            Node *temp = head;
            head = head -> right;
            delete temp;
        } else {
            Node *temp = findMax(head -> left);
            head -> data = temp -> data;
            remove(head -> left, temp -> data);
        }
    }
}

int main() {
    Node* test = NULL;
    insert(test, 1);
    insert(test, 2);
    insert(test, 4);
    insert(test, 3);
    remove(test, 2);
    traverseInorder(test);
}



