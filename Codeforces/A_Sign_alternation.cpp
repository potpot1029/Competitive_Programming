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
        // cout << tl << " " << (tl % 2 == 0) << "\n";
        if (tl % 2 == 0) {
            tree[idx] = A[tl];
        }
        else {
            tree[idx] = -A[tl];
        }
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
        // cout << tl << " " << (tl % 2 == 0) << "\n";
        if (tl % 2 == 0) {
            tree[idx] = val;
        }
        else {
            tree[idx] = -val;
        }
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

int _query(int idx, int tl, int tr, int l, int r) {
    if (l > r) {
        return 0;
    }
    else if (l == tl && r == tr) {
        return tree[idx];
    }
    else {
        int tm = (tl + tr) / 2;
        int left_res = _query(idx*2, tl, tm, l, min(tm, r));
        int right_res = _query(idx*2+1, tm+1, tr, max(tm+1, l), r);

        return combine(left_res, right_res);
    }
}

int query(int l, int r) {
    if (l % 2 == 0) {
        return _query(1, 0, N-1, l, r);
    }
    else {
        return -_query(1, 0, N-1, l, r);
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin >> N;
    int A[N];
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    build(A, N);

    int M;
    cin >> M;
    while (M--) {
        int op;
        cin >> op;
        if (op == 0) {
            int i, j;
            cin >> i >> j;
            i--;

            update(i, j);
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