#include <bits/stdc++.h>
using namespace std;

#define MAXN 100010
int N, K;
int A[MAXN];

int max_not_greater(int target) {
    int l = -1, r = N;

    while (l + 1 < r) {
        int m = (l + r) / 2;

        if (A[m] <= target) {
            l = m;
        }
        else {
            r = m; 
        }
    }
    return l;
}

int min_not_less(int target) {
    int l = -1, r = N;

    while (l + 1 < r) {
        int m = (l + r) / 2;

        if (A[m] < target) {
            l = m;
        }
        else {
            r = m; 
        }
    }
    return r;
}

int fast_search(int l, int r) {
    int l_bound = min_not_less(l);
    int r_bound = max_not_greater(r);

    return r_bound - l_bound + 1;
}

int main() {
    ios::sync_with_stdio(0);
    cin >> N;

    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }
    sort(A, A+N);

    cin >> K;
    while (K--) {
        int l, r;
        cin >> l >> r;

        cout << fast_search(l, r) << " \n"[K == 0];
    }
    return 0;
}