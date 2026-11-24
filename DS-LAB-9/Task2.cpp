#include <iostream>
#include <string>
using namespace std;

class Patient {
public:
    string name;
    int id, priority;
    Patient *left, *right, *parent;

    Patient(string n, int i, int p) {
        name = n;
        id = i;
        priority = p;
        left = right = parent = NULL;
    }
};

class MaxHeap {
public:
    Patient *root;

    MaxHeap() {
        root = NULL;
    }

    void insert(string name, int id, int priority) {
        Patient *n = new Patient(name, id, priority);

        if (root == NULL) {
            root = n;
            return;
        }

        Patient *q[100];
        int front = 0, rear = 0;
        q[rear++] = root;

        while (front < rear) {
            Patient *temp = q[front++];

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
               n->priority > n->parent->priority) {
            Patient *p = n->parent;

            string tempName = n->name;
            n->name = p->name;
            p->name = tempName;

            int tempId = n->id;
            n->id = p->id;
            p->id = tempId;

            int tempPriority = n->priority;
            n->priority = p->priority;
            p->priority = tempPriority;

            n = p;
        }
    }

    void display() {
        if (root == NULL) {
            cout << "Heap is empty\n";
            return;
        }

        Patient *q[100];
        int front = 0, rear = 0;
        q[rear++] = root;

        while (front < rear) {
            Patient *temp = q[front++];

            cout << temp->name << " "
                 << temp->id << " "
                 << temp->priority << endl;

            if (temp->left != NULL)
                q[rear++] = temp->left;

            if (temp->right != NULL)
                q[rear++] = temp->right;
        }
    }

    void deleteMax() {
        if (root == NULL)
            return;

        cout << "Patient treated: "
             << root->name << endl;

        Patient *q[100];
        int front = 0, rear = 0;
        Patient *last = root;
        q[rear++] = root;

        while (front < rear) {
            Patient *temp = q[front++];
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
        root->priority = last->priority;

        Patient *p = last->parent;

        if (p->left == last)
            p->left = NULL;
        else
            p->right = NULL;

        delete last;

        Patient *current = root;

        while (current != NULL) {
            Patient *largest = current;

            if (current->left != NULL &&
                current->left->priority > largest->priority)
                largest = current->left;

            if (current->right != NULL &&
                current->right->priority > largest->priority)
                largest = current->right;

            if (largest == current)
                break;

            string tempName = current->name;
            current->name = largest->name;
            largest->name = tempName;

            int tempId = current->id;
            current->id = largest->id;
            largest->id = tempId;

            int tempPriority = current->priority;
            current->priority = largest->priority;
            largest->priority = tempPriority;

            current = largest;
        }
    }
};

int main() {
    MaxHeap h;

    h.insert("Ali", 201, 3);
    h.insert("Ahmed", 202, 8);
    h.insert("Sara", 203, 5);
    h.insert("Usman", 204, 10);
    h.insert("Ayesha", 205, 6);
    h.insert("Hassan", 206, 4);

    cout << "All Patients:\n";
    h.display();

    cout << "\nHighest Priority Patient:\n";
    if (h.root != NULL)
        cout << h.root->name << " "
             << h.root->priority << endl;

    h.deleteMax();

    cout << "\nUpdated Patients:\n";
    h.display();

    cout << "\nNext Patient:\n";
    if (h.root != NULL)
        cout << h.root->name << " "
             << h.root->priority << endl;

    return 0;
}
