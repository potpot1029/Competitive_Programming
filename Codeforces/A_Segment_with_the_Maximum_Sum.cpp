#include <bits/stdc++.h>
using namespace std;
#define MAXN 100010
int N;
long long tree[4*MAXN];
long long pref[4*MAXN], suff[4*MAXN], sum[4*MAXN];

void combine(int idx) {
    // max. sum segment
    int lidx = idx*2, ridx = idx*2+1;
    pref[idx] = max(pref[lidx], sum[lidx]+pref[ridx]);
    suff[idx] = max(suff[ridx], suff[lidx]+sum[ridx]);
    sum[idx] = sum[lidx] + sum[ridx];
    tree[idx] = max(0ll, max(max(tree[lidx], tree[ridx]), suff[lidx]+pref[ridx]));
}

void _build(long long *A, int idx, int tl, int tr) {
    if (tl == tr) {
        tree[idx] = max(0ll, A[tl]);
        pref[idx] = suff[idx] = sum[idx] = A[tl];
    }
    else {
        int tm = (tl + tr) / 2;
        _build(A, idx*2, tl, tm);
        _build(A, idx*2+1, tm+1, tr);

        combine(idx);
    }
}

void build(long long *A, int N) {
    _build(A, 1, 0, N-1);
}

void _update(int idx, int tl, int tr, int pos, long long val) {
    if (tl == tr) {
        tree[idx] = max(0ll, val);
        pref[idx] = suff[idx] = sum[idx] = val;
    }
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm) {
            _update(idx*2, tl, tm, pos, val);
        }
        else {
            _update(idx*2+1, tm+1, tr, pos, val);
        }

        combine(idx);
    }
}

void update(int pos, long long val) {
    _update(1, 0, N-1, pos, val);
}

long long query() {
    return tree[1];
}

int main() {
    ios::sync_with_stdio(0);
    int M;
    cin >> N >> M;

    long long A[N];
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    build(A, N);
    cout << query() << "\n";

    while (M--) {
        int pos;
        long long val;
        cin >> pos >> val;
        update(pos, val);
        cout << query() << "\n";
    }

    return 0;
}