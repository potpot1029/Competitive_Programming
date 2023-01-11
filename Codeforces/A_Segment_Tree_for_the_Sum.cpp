#include <bits/stdc++.h>
using namespace std;
#define MAXN 100010
int N, M;
long long tree[4*MAXN], A[MAXN];

void _build(int idx, int tl, int tr) {
    if (tl == tr) {
        tree[idx] = A[tl];
        return;
    }

    int tm = (tl + tr) / 2;
    _build(idx*2, tl, tm);
    _build(idx*2+1, tm+1, tr);

    // sum
    tree[idx] = tree[idx*2] + tree[idx*2+1];
}

void build() {
    _build(1, 0, N-1);
}

void _update(int idx, int tl, int tr, int pos, int val) {
    if (tl == tr) {
        tree[idx] = val;
        return;
    }

    int tm = (tl + tr) / 2;
    if (tm >= pos)
        _update(idx*2, tl, tm, pos, val);
    else
        _update(idx*2+1, tm+1, tr, pos, val);

    // sum
    tree[idx] = tree[idx*2] + tree[idx*2+1];
}

void update(int i, int val) {
    _update(1, 0, N-1, i, val);
}

long long _query(int idx, int tl, int tr, int l, int r) {
    if (l > r) 
        return 0;
    else if (l == tl && r == tr)
        return tree[idx];
    
    int tm = (tl + tr) / 2;
    return _query(idx*2, tl, tm, l, min(tm, r)) + _query(idx*2+1, tm+1, tr, max(tm+1, l), r);
}

long long sum(int l, int r) {
    return _query(1, 0, N-1, l, r);
}

int main() {
    ios::sync_with_stdio(0);
    cin >> N >> M;

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    build();

    while (M--) {
        int op;
        cin >> op;

        if (op == 1) {
            int i;
            long long v; 
            cin >> i >> v;
            update(i, v);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << sum(l, r-1) << "\n";
        }
    }

    return 0;
}