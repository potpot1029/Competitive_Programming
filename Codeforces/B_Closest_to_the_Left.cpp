#include <bits/stdc++.h>
using namespace std;

int binary_search(int *A, int N, int target) {
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
    return l+1;
}

int main() {
    ios::sync_with_stdio(0);
    int N, K;
    cin >> N >> K;

    int A[N];
    for (int i = 0; i < N; ++i) {
        cin >> A[i];
    }

    while (K--) {
        int target;
        cin >> target;

        cout << binary_search(A, N, target) << "\n";
    }
    return 0;
}