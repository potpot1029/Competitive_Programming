#include <bits/stdc++.h>
using namespace std;
#define MAXN 100010
int N, M;
int A[4*MAXN];

struct Node {
    long long inv;
    int freq[41];

    Node() {
        inv = 0;
        memset(freq, 0, sizeof(freq));
    }
};
Node* tree[4*MAXN];

Node* combine(const Node* left, const Node* right) {
    // update frequencies
    Node* now = new Node();
    for (int i = 1; i <= 40; ++i) {
        now->freq[i] = left->freq[i] + right->freq[i];
    }

    // calculate inversions
    long long greater_than_right = 0, less_than_left = 0;

    for (int i = 1; i <= 40; ++i) {
        // calculate number of elements on the right < x_l
        for (int j = 1; j < i; ++j) {
            less_than_left += (long long) left->freq[i] * right->freq[j];
        }

        // or calculate number of elements on the left > x_r
        // for (int j = i+1; j <= 40; ++j) {
        //     greater_than_right += right->freq[i] * left->freq[j];
        // }
    }

    now->inv = left->inv + right->inv + less_than_left;
    return now;
}

void _build(int *A, int idx, int tl, int tr) {
    if (tl == tr) {
        tree[idx] = new Node();
        tree[idx]->freq[A[tl]]++;
    }
    else {
        int tm = (tl + tr) / 2;
        _build(A, idx*2, tl, tm);
        _build(A, idx*2+1, tm+1, tr);

        tree[idx] = combine(tree[idx*2], tree[idx*2+1]);
    }
}

void build(int *A, int N) {
    _build(A, 1, 0, N-1);
}

void _update(int idx, int tl, int tr, int pos, int val) {
    if (tl == tr) {
        tree[idx]->freq[A[pos]]--;
        tree[idx]->freq[val]++;
        A[pos] = val;
    }
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            _update(idx*2, tl, tm, pos, val);
        }
        else {
            _update(idx*2+1, tm+1, tr, pos, val);
        }

        tree[idx] = combine(tree[idx*2], tree[idx*2+1]);
    }
}

void update(int pos, int val) {
    _update(1, 0, N-1, pos, val);
}


Node* _query(int idx, int tl, int tr, int l, int r) {
    if (l > r) {
        return new Node();
    }
    else if (l == tl && r == tr) {
        return tree[idx];
    }
    else {
        int tm = (tl + tr) / 2;
        Node* left_res = _query(idx*2, tl, tm, l, min(tm, r));
        Node* right_res = _query(idx*2+1, tm+1, tr, max(tm+1, l), r);

        return combine(left_res, right_res);
    }
}

long long query(int l, int r) {
    return _query(1, 0, N-1, l, r)->inv;
}

int main() {
    ios::sync_with_stdio(0);
    memset(tree, 0, sizeof(tree));
    cin >> N >> M;

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    build(A, N);

    while (M--) {
        int op;
        cin >> op;
        if (op == 2) {
            int pos, v;
            cin >> pos >> v;
            pos--;

            update(pos, v);
        }
        else {
            int l, r;
            cin >> l >> r;
            l--, r--;

            cout << query(l, r) << "\n";
        }
    }
    
    return 0;
}