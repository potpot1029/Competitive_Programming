struct Node {
    // may change the data type of val.
    int val;
    int pri, size;
    Node *left, *right;
    Node(int c) : val(c), pri(random()), size(1), left(NULL), right(NULL) {};
} *root;

int size(Node *node){
    return node ? node->size : 0;
}

void update_size(Node *node) {
    node->size = 1 + size(node->left) + size(node->right);
}

/**
 * Split a treap into two and 
 * store them in left and right
*/
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


/**
 * Merge two treaps left and right, and
 * store it in treap.
*/
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
