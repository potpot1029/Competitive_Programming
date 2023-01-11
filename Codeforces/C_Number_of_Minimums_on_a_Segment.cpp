#include <bits/stdc++.h>
using namespace std;
#define MAXN 100010
int N;
pair<int, int> tree[4*MAXN]; // {val, cnt}

pair<int, int> combine(pair<int, int> a, pair<int, int> b) {
    // minimum and no of minimum 
    if (a.first == b.first) {
        return make_pair(a.first, a.second + b.second);
    }
    else if (a.first < b.first) {
        return a;
    }
    else {
        return b;
    }
}

void _build(int *A, int idx, int tl, int tr) {
    if (tl == tr) {
        tree[idx] = make_pair(A[tl], 1);
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
        tree[idx] = make_pair(val, 1);
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

pair<int, int> _query(int idx, int tl, int tr, int l, int r) {
    if (l > r) {
        return make_pair(INT_MAX, 0);
    }
    else if (l == tl && r == tr) {
        return tree[idx];
    }
    else {
        int tm = (tl + tr) / 2;
        pair<int, int> left_res = _query(idx*2, tl, tm, l, min(tm, r));
        pair<int, int> right_res = _query(idx*2+1, tm+1, tr, max(tm+1, l), r);

        return combine(left_res, right_res);
    }
}

pair<int, int> no_of_min(int l, int r) {
    return _query(1, 0, N-1, l, r);
}

ostream& operator<<(ostream& os, const pair<int, int> pii) {
    os << pii.first << " " << pii.second;
    return os;
}

int main() {
    ios::sync_with_stdio(0);
    int M;
    cin >> N >> M;

    int A[N];
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    build(A, N);

    while (M--) {
        int op;
        cin >> op;

        if (op == 1) {
            int i, val;
            cin >> i >> val;
            update(i, val);
        }
        else {
            int l, r;
            cin >> l >> r;
            cout << no_of_min(l, r-1) << "\n";
        }
    }
    return 0;
}