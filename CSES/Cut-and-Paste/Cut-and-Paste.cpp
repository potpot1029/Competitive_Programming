#include <bits/stdc++.h>
using namespace std;

struct Node {
    char val;
    int pri;
    int size;
    Node *left, *right;
    Node(char c) : val(c), pri(rand()), size(1), left(NULL), right(NULL) {};
} *root;

int size(Node *node) {
    return node ? node->size : 0;
}

void update_size(Node *node) {
    node->size = 1 + size(node->left) + size(node->right);   
}

void split(Node *treap, Node *&left, Node *&right, int key) {
    if (!treap) {
        left = right = NULL;
        return;
    }

    int cur_size = size(treap->left);
    if (cur_size <= key) {
        split(treap->right, treap->right, right, key - cur_size - 1);
        left = treap;
    }
    else {
        split(treap->left, left, treap->left, key);
        right = treap;
    }
    update_size(treap);
}

void merge(Node *&treap, Node *left, Node *right) {
    if (!left || !right) {
        treap = left ? left : right;
        return;
    }

    if (left->pri > right->pri) {
        merge(left->right, left->right, right);
        treap = left;
    }
    else {
        merge(right->left, left, right->left);
        treap = right;
    }
    update_size(treap);
}

ostream& operator<<(ostream& os, const Node *node) {
    if (!node)
        return os;
    os << node->left;
    os << node->val;
    os << node->right;
    return os;
}

int main() {
    ios::sync_with_stdio(0);
    int N, M;
    string S;
    cin >> N >> M; 
    cin >> S;

    for (char c : S) {
        merge(root, root, new Node(c));
    }
    // cout << root << "\n";

    while (M--) {
        int a, b;
        cin >> a >> b;
        a--, b--;

        // cut a substring
        Node *p1, *p2, *p3, *p4;
        split(root, p1, p2, a-1);
        split(p2, p3, p4, b-a);

        // paste it to the end of the string
        merge(root, p1, p4);
        merge(root, root, p3);
    }

    cout << root << "\n";
    return 0;
}