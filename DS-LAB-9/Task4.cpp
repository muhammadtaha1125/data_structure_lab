#include <iostream>
#include <string>
using namespace std;

class Medicine {
public:
    string name;
    int id, expiry;
    Medicine *left, *right, *parent;

    Medicine(string n, int i, int e) {
        name = n;
        id = i;
        expiry = e;
        left = right = parent = NULL;
    }
};

class MinHeap {
public:
    Medicine *root;

    MinHeap() {
        root = NULL;
    }

    void insert(string name, int id, int expiry) {
        Medicine *n = new Medicine(name, id, expiry);

        if (root == NULL) {
            root = n;
            return;
        }

        Medicine *q[100];
        int front = 0, rear = 0;
        q[rear++] = root;

        while (front < rear) {
            Medicine *temp = q[front++];

            if (temp->left == NULL) {
                temp->left = n;
                n->parent = temp;
                break;
            } else {
                q[rear++] = temp->left;
            }

            if (temp->right == NULL) {
                temp->right = n;
                n->parent = temp;
                break;
            } else {
                q[rear++] = temp->right;
            }
        }

        while (n->parent != NULL &&
               n->expiry < n->parent->expiry) {
            Medicine *p = n->parent;

            string tempName = n->name;
            n->name = p->name;
            p->name = tempName;

            int tempId = n->id;
            n->id = p->id;
            p->id = tempId;

            int tempExpiry = n->expiry;
            n->expiry = p->expiry;
            p->expiry = tempExpiry;

            n = p;
        }
    }

    void display() {
        if (root == NULL) {
            cout << "Heap is empty\n";
            return;
        }

        Medicine *q[100];
        int front = 0, rear = 0;
        q[rear++] = root;

        while (front < rear) {
            Medicine *temp = q[front++];

            cout << temp->name << " "
                 << temp->id << " "
                 << temp->expiry << endl;

            if (temp->left != NULL)
                q[rear++] = temp->left;

            if (temp->right != NULL)
                q[rear++] = temp->right;
        }
    }

    void deleteMin() {
        if (root == NULL)
            return;

        cout << "Deleted Medicine: "
             << root->name << " "
             << root->expiry << endl;

        Medicine *q[100];
        int front = 0, rear = 0;
        Medicine *last = root;
        q[rear++] = root;

        while (front < rear) {
            Medicine *temp = q[front++];
            last = temp;

            if (temp->left != NULL)
                q[rear++] = temp->left;

            if (temp->right != NULL)
                q[rear++] = temp->right;
        }

        if (last == root) {
            delete root;
            root = NULL;
            return;
        }

        root->name = last->name;
        root->id = last->id;
        root->expiry = last->expiry;

        Medicine *p = last->parent;

        if (p->left == last)
            p->left = NULL;
        else
            p->right = NULL;

        delete last;

        Medicine *current = root;

        while (current != NULL) {
            Medicine *smallest = current;

            if (current->left != NULL &&
                current->left->expiry < smallest->expiry)
                smallest = current->left;

            if (current->right != NULL &&
                current->right->expiry < smallest->expiry)
                smallest = current->right;

            if (smallest == current)
                break;

            string tempName = current->name;
            current->name = smallest->name;
            smallest->name = tempName;

            int tempId = current->id;
            current->id = smallest->id;
            smallest->id = tempId;

            int tempExpiry = current->expiry;
            current->expiry = smallest->expiry;
            smallest->expiry = tempExpiry;

            current = smallest;
        }
    }
};

int main() {
    MinHeap h;

    h.insert("Panadol", 301, 20270115);
    h.insert("Brufen", 302, 20261220);
    h.insert("Calpol", 303, 20271210);
    h.insert("Augmentin", 304, 20261130);
    h.insert("Disprin", 305, 20270325);
    h.insert("VitaminC", 306, 20261215);

    cout << "Medicine Heap:\n";
    h.display();

    h.deleteMin();

    cout << "\nUpdated Medicine Heap:\n";
    h.display();

    return 0;
}
