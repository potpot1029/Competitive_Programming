#include <bits/stdc++.h>
using namespace std;
#define MAXN 100000
int N;
int tree[4*MAXN];

int combine(int a, int b) {
    // operation
    return a | b;
}

void _build(string A, int idx, int tl, int tr) {
    if (tl == tr) {
        tree[idx] = 1 << (A[tl] - 'a');
    }
    else {
        int tm = (tl + tr) / 2;
        _build(A, idx*2, tl, tm);
        _build(A, idx*2+1, tm+1, tr);

        tree[idx] = combine(tree[idx*2], tree[idx*2+1]);
    }
}

void build(string A, int N) {
    _build(A, 1, 0, N-1);
}

void _update(int idx, int tl, int tr, int pos, char val) {
    if (tl == tr) {
        tree[idx] = 1 << (val - 'a');
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

void update(int pos, char val) {
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
    return _query(1, 0, N-1, l, r);
}

int main() {
    ios::sync_with_stdio(0);

    string s;
    cin >> s;
    N = s.size();

    build(s, N);

    int q;
    cin >> q;

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int pos;
            char c;
            cin >> pos >> c;
            update(pos-1, c);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << __builtin_popcount(query(l-1, r-1)) << "\n";
        }
    }

    return 0;
}