#include <iostream>
#include <string>
using namespace std;

class Student {
public:
    string name;
    int roll;
    int marks;
    Student *left, *right, *parent;

    Student(string n, int r, int m) {
        name = n;
        roll = r;
        marks = m;
        left = right = parent = NULL;
    }
};

class MaxHeap {
public:
    Student *root;

    MaxHeap() {
        root = NULL;
    }

    void insert(string name, int roll, int marks) {
        Student *n = new Student(name, roll, marks);

        if (root == NULL) {
            root = n;
            return;
        }

        Student *q[100];
        int front = 0, rear = 0;
        q[rear++] = root;

        while (front < rear) {
            Student *temp = q[front++];

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
               n->marks > n->parent->marks) {
            Student *p = n->parent;

            string nameTemp = n->name;
            n->name = p->name;
            p->name = nameTemp;

            int tempRoll = n->roll;
            n->roll = p->roll;
            p->roll = tempRoll;

            int tempMarks = n->marks;
            n->marks = p->marks;
            p->marks = tempMarks;

            n = p;
        }
    }

    void display() {
        if (root == NULL) {
            cout << "Heap is empty\n";
            return;
        }

        Student *q[100];
        int front = 0, rear = 0;
        q[rear++] = root;

        while (front < rear) {
            Student *temp = q[front++];

            cout << temp->name << " "
                 << temp->roll << " "
                 << temp->marks << endl;

            if (temp->left != NULL)
                q[rear++] = temp->left;

            if (temp->right != NULL)
                q[rear++] = temp->right;
        }
    }

    void deleteMax() {
        if (root == NULL)
            return;

        cout << "Deleted student: "
             << root->name << " "
             << root->marks << endl;

        Student *q[100];
        int front = 0, rear = 0;
        Student *last = root;
        q[rear++] = root;

        while (front < rear) {
            Student *temp = q[front++];

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
        root->roll = last->roll;
        root->marks = last->marks;

        Student *p = last->parent;

        if (p->left == last)
            p->left = NULL;
        else
            p->right = NULL;

        delete last;

        Student *current = root;

        while (current != NULL) {
            Student *largest = current;

            if (current->left != NULL &&
                current->left->marks > largest->marks)
                largest = current->left;

            if (current->right != NULL &&
                current->right->marks > largest->marks)
                largest = current->right;

            if (largest == current)
                break;

            string nameTemp = current->name;
            current->name = largest->name;
            largest->name = nameTemp;

            int tempRoll = current->roll;
            current->roll = largest->roll;
            largest->roll = tempRoll;

            int tempMarks = current->marks;
            current->marks = largest->marks;
            largest->marks = tempMarks;

            current = largest;
        }
    }
};

int main() {
    MaxHeap h;

    h.insert("Ali", 101, 85);
    h.insert("Ahmed", 102, 92);
    h.insert("Sara", 103, 78);
    h.insert("Usman", 104, 95);
    h.insert("Ayesha", 105, 88);
    h.insert("Hassan", 106, 80);

    cout << "Student Heap:\n";
    h.display();

    h.deleteMax();

    cout << "\nUpdated Heap:\n";
    h.display();

    return 0;
}
