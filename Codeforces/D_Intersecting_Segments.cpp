#include <bits/stdc++.h>
using namespace std;
#define MAXN 200010
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
    int M;
    cin >> M;
    N = 2 * M;

    int A[N], left[M+1], cnt[M+1];
    memset(A, 0, sizeof(A));
    memset(left, -1, sizeof(left));
    memset(cnt, 0, sizeof(cnt));
    build(A, N);
    
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    // processing - type 1
    for (int i = 0; i < N; ++i) {
        if (left[A[i]] == -1) {
            left[A[i]] = i;
            update(i, 1);
        }
        else {
            cnt[A[i]] += query(left[A[i]]+1, i-1);
            update(left[A[i]], 0);
        }
    }

    // processing - type 2
    memset(left, -1, sizeof(left));
    reverse(A, A+N);
    for (int i = 0; i < N; ++i) {
        if (left[A[i]] == -1) {
            left[A[i]] = i;
            update(i, 1);
        }
        else {
            cnt[A[i]] += query(left[A[i]]+1, i-1);
            update(left[A[i]], 0);
        }
    }

    // output
    for (int i = 1; i <= M; ++i) {
        cout << cnt[i] << " \n"[i == M];
    }

    return 0;
}