#include <bits/stdc++.h>
using namespace std;
#define MAXN 100010
int N;
long long tree[4*MAXN];

long long combine(long long a, long long b) {
    // operation
    return a + b;
}

void _update(int idx, int tl, int tr, int pos, long long val) {
    if (tl == tr) {
        tree[idx] += val;
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

long long _query(int idx, int tl, int tr, int l, int r) {
    if (l > r) {
        return 0;
    }
    else if (l == tl && r == tr) {
        return tree[idx];
    }
    else {
        int tm = (tl + tr) / 2;
        long long left_res = _query(idx*2, tl, tm, l, min(tm, r));
        long long right_res = _query(idx*2+1, tm+1, tr, max(tm+1, l), r);

        return combine(left_res, right_res);
    }
}

long long query(int x) {
    return _query(1, 0, N-1, 0, x);
}

int main() {
    ios::sync_with_stdio(0);
    int M;
    cin >> N >> M;
    memset(tree, 0ll, sizeof(tree));
    N++;

    while (M--) {
        int op;
        cin >> op;
        if (op == 1) {
            int l, r, v;
            cin >> l >> r >> v;

            update(l, v);
            update(r, -v);
        }
        else {
            int i;
            cin >> i;

            cout << query(i) << "\n";
        }
    }
    
    return 0;
}