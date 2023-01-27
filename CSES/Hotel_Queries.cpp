#include <bits/stdc++.h>
using namespace std;

#define MAXN 200010
int N, M;
int tree[4*MAXN];

int combine(int a, int b) {
    // operation
    return max(a, b);
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

void _update(int idx, int tl, int tr, int pos, int val) {
    if (tl == tr) {
        tree[idx] = val;
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

int _query(int idx, int tl, int tr, int p) {
    if (tree[idx] < p) {
        return 0;
    }
    else if (tl == tr) {
        update(tl, tree[idx] - p);
        return tl+1;
    }
    else {
        int tm = (tl + tr) / 2;
        int left_res = _query(idx*2, tl, tm, p);

        if (!left_res) {
            return _query(idx*2+1, tm+1, tr, p);
        }
        else {
            return left_res;
        }

    }
}

int query(int p) {
    return _query(1, 0, N-1, p);
}

int main() {
    ios::sync_with_stdio(0);
    cin >> N >> M;
    int A[N];
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    build(A, N);

    while (M--) {
        int r;
        cin >> r;
        
        cout << query(r) << " \n"[M == 0];
    }
    return 0;
}