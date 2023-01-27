#include <bits/stdc++.h>
using namespace std;

#define MAXN 200010
int N, M;

struct Node {
    long long sum;
    long long max_pref;

    Node () {
        sum = max_pref = 0;
    }

    Node (long long x) {
        sum = x;
        max_pref = max(0ll, x);
    }
};
Node* tree[4*MAXN];


Node* combine(Node* a, Node* b) {
    Node* c = new Node();

    // update sum
    c->sum = a->sum + b->sum;

    // update maximum prefix sum
    c->max_pref = max(0ll, max(a->max_pref, a->sum + b->max_pref));

    return c;
}

void _build(long long *A, int idx, int tl, int tr) {
    if (tl == tr) {
        tree[idx] = new Node(A[tl]);
    }
    else {
        int tm = (tl + tr) / 2;
        _build(A, idx*2, tl, tm);
        _build(A, idx*2+1, tm+1, tr);

        tree[idx] = combine(tree[idx*2], tree[idx*2+1]);
    }
}

void build(long long *A, int N) {
    _build(A, 1, 0, N-1);
}

void _update(int idx, int tl, int tr, int pos, long long val) {
    if (tl == tr) {
        tree[idx] = new Node(val);
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

void update(int pos, long long val) {
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
    return _query(1, 0, N-1, l, r)->max_pref;
}

int main() {
    ios::sync_with_stdio(0);
    cin >> N >> M; 
    long long A[N];
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    build(A, N);

    while (M--) {
        int op;
        cin >> op;

        if (op == 1) {
            int k;
            long long u;
            cin >> k >> u;
            k--;
            update(k, u);
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