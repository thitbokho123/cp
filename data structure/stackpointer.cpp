#include <bits/stdc++.h>
using namespace std;

typedef int item;

struct Node {
    item Data;
    Node *Next;
};

struct Stack {
    Node *Top;
};

void init(Stack &s) {
    s.Top = NULL;
}

bool isempty(Stack s) {
    return (s.Top == NULL);
}

int len(Stack s) {
    int cnt = 0;
    Node *P = s.Top;
    while (P != NULL) {
        cnt++;
        P = P->Next;
    }
    return cnt;
}

Node *Makenode(item x) {
    Node *P = (Node *)malloc(sizeof(Node));
    P->Next = NULL;
    P->Data = x;
    return P;
}

void Push(Stack &s, item x) {
    Node *P = Makenode(x);
    P->Next = s.Top;
    s.Top = P;
}

item Peak(Stack s) {
    if (!isempty(s))
        return s.Top->Data;
    return -1; // Return -1 if the stack is empty
}

item Pop(Stack &s) {
    if (isempty(s)) return -1; // Return -1 if the stack is empty
    item x = s.Top->Data;
    Node *temp = s.Top; // Temporary pointer to hold the top node
    s.Top = s.Top->Next; // Move to the next node
    free(temp); // Free memory of the removed node
    return x;
}

int main() {
    Stack s;
    init(s);
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        item a;
        cin >> a;
        Push(s, a);
    }

    char cont;
    do {
        cout << "\nChoose:\n1.Check empty\n2.Check length\n3.Get\n4.Pop\n5.Push\n";
        cout << "You choose: ";
        int z;
        cin >> z;

        switch (z) {
            case 1:
                cout << (isempty(s) ? "YES\n" : "NO\n");
                break;
            case 2:
                cout << "Stack length: " << len(s) << '\n';
                break;
            case 3:
                if (!isempty(s)) cout << "Top element: " << Peak(s) << '\n';
                else cout << "Stack is empty!\n";
                break;
            case 4:
                if (!isempty(s)) {
                    cout << "Popped: " << Pop(s) << '\n';
                } else {
                    cout << "Stack is empty!\n";
                }
                break;
            case 5:
                int m;
                cout << "Enter value to push: ";
                cin >> m;
                Push(s, m);
                cout << "Pushed successfully.\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

        cout << "\nContinue? (y/n): ";
        cin >> cont;

    } while (cont == 'y' || cont == 'Y');

    cout << "\nStack elements (from top to bottom): ";
    Node *P = s.Top;
    while (P != NULL) {
        cout << P->Data << ' ';
        P = P->Next;
    }
    cout << '\n';

    return 0;
}
