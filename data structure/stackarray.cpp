#include <bits/stdc++.h>
using namespace std;

typedef int item;
#define mx 100001

struct Stack {
    int top;
    item Data[mx];
};

void init(Stack &s) {
    s.top = 0;
}

bool emptyy(Stack s) {
    return (s.top == 0);
}

bool full(Stack s) {
    return (s.top == mx);
}

void pushh(Stack &s, item x) {
    if (!full(s)) {
        s.Data[s.top] = x;
        s.top++;
    }
}

item gett(Stack &s) {
    if (!emptyy(s)) {
        return s.Data[s.top - 1];
    }
    return -1;  // Trả về giá trị đặc biệt nếu stack rỗng
}

void popp(Stack &s) {
    if (!emptyy(s)) {
        s.top--;
    }
}

int main() {
    int n;
    cin >> n;
    Stack s;
    init(s);

    cout << "Enter " << n << " elements:\n";
    for (int i = 0; i < n; i++) {
        item a;
        cin >> a;
        pushh(s, a);
    }

    char cont;
    do {
        cout << "\nChoose:\n1.Check empty\n2.Check full\n3.Get\n4.Pop\n5.Push\n";
        cout << "You choose: ";
        int z;
        cin >> z;

        switch (z) {
            case 1:
                if (emptyy(s)) cout << "YES\n";
                else cout << "NO\n";
                break;
            case 2:
                if (full(s)) cout << "YES\n";
                else cout << "NO\n";
                break;
            case 3:
                if (!emptyy(s)) cout << "Top element: " << gett(s) << '\n';
                else cout << "Stack is empty!\n";
                break;
            case 4:
                if (!emptyy(s)) {
                    popp(s);
                    cout << "Popped successfully.\n";
                } else {
                    cout << "Stack is empty!\n";
                }
                break;
            case 5:
                int m;
                cout << "Enter value to push: ";
                cin >> m;
                if (!full(s)) {
                    pushh(s, m);
                    cout << "Pushed successfully.\n";
                } else {
                    cout << "Stack is full!\n";
                }
                break;
            default:
                cout << "Invalid choice!\n";
        }

        cout << "\nContinue? (y/n): ";
        cin >> cont;

    } while (cont == 'y' || cont == 'Y');

    cout << "\nStack elements (from top to bottom): ";
    for (int i = s.top - 1; i >= 0; i--) {
        cout << s.Data[i] << ' ';
    }
    cout << '\n';

    return 0;
}
