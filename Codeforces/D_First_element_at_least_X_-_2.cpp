#include <bits/stdc++.h>
using namespace std;
#define MAXN 100010
int N;
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

int _query(int idx, int tl, int tr, int x, int pos) {
    // cout << "current: " << idx << " " << tl << ", " << tr << "\n";
    if (tr < pos || tree[idx] < x) {
        return INT_MAX;
    }
    if (tl == tr) {
        return tl;
    }
    else {
        int tm = (tl + tr) / 2;
        int ans = INT_MAX;
        // cout << "left:" << tree[idx*2] << " right:" << tree[idx*2+1] << "\n";
        ans = min(ans, _query(idx*2, tl, tm, x, pos));
        if (ans != INT_MAX) {
            return ans;
        }
        ans = _query(idx*2+1, tm+1, tr, x, pos);
        return ans;
    }
}

int query(int x, int l) {
    int res = _query(1, 0, N-1, x, l);
    return res == INT_MAX ? -1 : res;
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
            int i, v;
            cin >> i >> v;
            update(i, v);
        }
        else {
            int x, l;
            cin >> x >> l;
            cout << query(x, l) << "\n";
        }
    }
    return 0;
}