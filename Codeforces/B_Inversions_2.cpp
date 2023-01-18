#include <bits/stdc++.h>
using namespace std;
#define MAXN 100010
int N;
int tree[4*MAXN];

int combine(int a, int b) {
    // operation
    return a + b;
}

void _build(int *A, int idx, int tl, int tr) {
    if (tl == tr) {
        tree[idx] = A[tl];
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

void _update(int idx, int tl, int tr, int pos) {
    if (tl == tr) {
        tree[idx] ^= 1;
    }
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            _update(idx*2, tl, tm, pos);
        }
        else {
            _update(idx*2+1, tm+1, tr, pos);
        }

        tree[idx] = combine(tree[idx*2], tree[idx*2+1]);
    }
}

void update(int pos) {
    _update(1, 0, N-1, pos);
}

int _query(int idx, int tl, int tr, int k) {
    if (tl == tr) {
        return tl;
    }
    else {
        int tm = (tl + tr) / 2;
        if (k < tree[idx*2+1]) {
            return _query(idx*2+1, tm+1, tr, k);
        }
        else {
            return _query(idx*2, tl, tm, k-tree[idx*2+1]);
        }
    }
}

int query(int k) {
    return _query(1, 0, N-1, k);
}

int main() {
    ios::sync_with_stdio(0);
    cin >> N;

    // initialize tree to all one
    int ones[N];
    for (int i = 0; i < N; ++i) {
        ones[i] = 1;
    }
    build(ones, N);
    
    int a[N], p[N];
    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }

    for (int i = N-1; i >= 0; --i) {
        p[i] = query(a[i]);
        update(p[i]);
    }

    for (int i = 0; i < N; ++i) {
        cout << p[i]+1 << " \n"[i == N-1];
    }

    return 0;
}