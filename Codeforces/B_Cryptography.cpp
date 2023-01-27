#include <bits/stdc++.h>
using namespace std;
#define MAXN 200010
int N, M, R;

struct matrix {
    int a[2][2];
    int null;

    matrix() {
        memset(a, 0, sizeof(a));
        null = 1;
    }
};
matrix* tree[4*MAXN];

ostream& operator<<(ostream& os, const matrix* m) {
    if (m->null)
        return os;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            os << m->a[i][j] << " ";
        }
        cout << "\n";
    }
    return os;
}

matrix* combine(matrix *a, matrix *b) {
    // operation
    if (a->null) {
        // cout << "testa\n";
        return b;
    }
    if (b->null) {
        // cout << "testb\n";
        return a;
    }

    matrix* c = new matrix();
    c->null = 0;

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            c->a[i][j] = 0;
            for (int k = 0; k < 2; ++k) {
                c->a[i][j] = (c->a[i][j] + (a->a[i][k] * b->a[k][j]) % R) % R;
            }
        }
    }
    return c;
}

void _build(matrix* A[], int idx, int tl, int tr) {
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

void build(matrix* A[], int N) {
    _build(A, 1, 0, N-1);
}

matrix* _query(int idx, int tl, int tr, int l, int r) {
    if (l > r) {
        return new matrix();
    }
    else if (l == tl && r == tr) {
        return tree[idx];
    }
    else {
        int tm = (tl + tr) / 2;
        matrix* left_res = _query(idx*2, tl, tm, l, min(tm, r));
        matrix* right_res = _query(idx*2+1, tm+1, tr, max(tm+1, l), r);

        // cout << "idx:" << idx << " l,r:" << tl << " " << tr << "\n" << left_res << right_res << "\n";
        return combine(left_res, right_res);
    }
}

matrix* query(int l, int r) {
    return _query(1, 0, N-1, l, r);
}



int main() {
    ios::sync_with_stdio(0);
    cin >> R >> N >> M;

    matrix* A[N];
    for (int i = 0; i < N; ++i) {
        A[i] = new matrix();
        A[i]->null = 0;
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 2; ++k) {
                cin >> A[i]->a[j][k];
            }
        }

    }
    build(A, N);

    // for (int i = 0; i < N; ++i) {
    //     cout << A[i] << "\n";
    // }
    
    while (M--) {
        int l, r;
        cin >> l >> r;
        l--, r--;

        cout << query(l, r) << "\n";
    }
    return 0;
}