#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

int height(Node* n) {
    if (n == NULL) return 0;
    return n->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

Node* newNode(int data) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

void updateHeight(Node* n) {
    n->height = 1 + max(height(n->left), height(n->right));
}

int getBalance(Node* n) {
    if (n == NULL) return 0;
    return height(n->left) - height(n->right);
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

Node* insert(Node* node, int data) {
    if (node == NULL)
        return newNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node;

    updateHeight(node);

    int balance = getBalance(node);

    if (balance > 1 && data < node->left->data)
        return rotateRight(node);

    if (balance < -1 && data > node->right->data)
        return rotateLeft(node);

    if (balance > 1 && data > node->left->data) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (balance < -1 && data < node->right->data) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->right);
        printf("%d ", root->data);
        inorder(root->left);
    }
}

void preorder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

int main() {
    int arr[] = {32, 51, 27, 83, 96, 11, 45, 75, 66};
    int n = 9;
    Node* root = NULL;

    printf("=== CAY CAN BANG AVL ===\n\n");
    printf("Day so dau vao: ");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n\n");

    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);

    printf("Inorder   (Tang dan): ");
    inorder(root);
    printf("\n");

    printf("Preorder  (Goc-T-P) : ");
    preorder(root);
    printf("\n");

    printf("Postorder (T-P-Goc) : ");
    postorder(root);
    printf("\n");

    printf("\nNode goc: %d\n", root->data);
    printf("Chieu cao: %d\n", root->height);

    return 0;
}s