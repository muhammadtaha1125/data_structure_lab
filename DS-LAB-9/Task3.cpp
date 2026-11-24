#include <iostream>
#include <string>
using namespace std;

class Order {
public:
    int id, amount;
    string customer;
    Order *left, *right, *parent;

    Order(int i, string c, int a) {
        id = i;
        customer = c;
        amount = a;
        left = right = parent = NULL;
    }
};

class MaxHeap {
public:
    Order *root;

    MaxHeap() {
        root = NULL;
    }

    void insert(int id, string customer, int amount) {
        Order *n = new Order(id, customer, amount);

        if (root == NULL) {
            root = n;
            return;
        }

        Order *q[100];
        int front = 0, rear = 0;
        q[rear++] = root;

        while (front < rear) {
            Order *temp = q[front++];

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
               n->amount > n->parent->amount) {
            Order *p = n->parent;

            int tempId = n->id;
            n->id = p->id;
            p->id = tempId;

            string tempName = n->customer;
            n->customer = p->customer;
            p->customer = tempName;

            int tempAmount = n->amount;
            n->amount = p->amount;
            p->amount = tempAmount;

            n = p;
        }
    }

    int deleteMax() {
        if (root == NULL)
            return -1;

        int deletedAmount = root->amount;

        Order *q[100];
        int front = 0, rear = 0;
        Order *last = root;
        q[rear++] = root;

        while (front < rear) {
            Order *temp = q[front++];
            last = temp;

            if (temp->left != NULL)
                q[rear++] = temp->left;

            if (temp->right != NULL)
                q[rear++] = temp->right;
        }

        if (last == root) {
            delete root;
            root = NULL;
            return deletedAmount;
        }

        root->id = last->id;
        root->customer = last->customer;
        root->amount = last->amount;

        Order *p = last->parent;

        if (p->left == last)
            p->left = NULL;
        else
            p->right = NULL;

        delete last;

        Order *current = root;

        while (current != NULL) {
            Order *largest = current;

            if (current->left != NULL &&
                current->left->amount > largest->amount)
                largest = current->left;

            if (current->right != NULL &&
                current->right->amount > largest->amount)
                largest = current->right;

            if (largest == current)
                break;

            int tempId = current->id;
            current->id = largest->id;
            largest->id = tempId;

            string tempName = current->customer;
            current->customer = largest->customer;
            largest->customer = tempName;

            int tempAmount = current->amount;
            current->amount = largest->amount;
            largest->amount = tempAmount;

            current = largest;
        }

        return deletedAmount;
    }
};

int main() {
    MaxHeap h;

    int amounts[6];

    h.insert(1, "Ali", 500);
    h.insert(2, "Ahmed", 200);
    h.insert(3, "Sara", 800);
    h.insert(4, "Usman", 300);
    h.insert(5, "Ayesha", 700);
    h.insert(6, "Hassan", 100);

    for (int i = 0; i < 6; i++) {
        amounts[i] = h.deleteMax();
    }

    cout << "Order Amounts in Ascending Order:\n";

    for (int i = 5; i >= 0; i--) {
        cout << amounts[i] << " ";
    }

    return 0;
}
