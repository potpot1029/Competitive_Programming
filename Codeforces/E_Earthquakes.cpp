#include <bits/stdc++.h>
using namespace std;
#define MAXN 100010
int N, M;
int tree[4*MAXN];

int combine(int a, int b) {
    // operation
    return min(a, b);
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

int _query(int idx, int tl, int tr, int l, int r, int p) {
    if (l > r || tree[idx] > p) {
        return 0;
    }
    else if (tl == tr) {
        // cout << "pos:" << tl << " val:" << tree[idx] << "\n";
        update(tl, INT_MAX);
        return 1;
    }
    else {
        int tm = (tl + tr) / 2;
        int left_res = _query(idx*2, tl, tm, l, min(tm, r), p);
        int right_res = _query(idx*2+1, tm+1, tr, max(tm+1, l), r, p);

        return left_res + right_res;
    }
}

int query(int l, int r, int p) {
    return _query(1, 0, N-1, l, r, p);
}

int main() {
    ios::sync_with_stdio(0);
    cin >> N >> M;
    for (int i = 0; i < N; ++i) {
        update(i, INT_MAX);
    }

    while (M--) {
        int op;
        cin >> op;

        if (op == 1) {
            int i, h;
            cin >> i >> h;

            update(i, h);
        }
        else {
            int l, r, p;
            cin >> l >> r >> p;

            cout << query(l, r-1, p) << "\n";
        }
    }
    return 0;
}