#include <bits/stdc++.h>
using namespace std;

bool binary_search(int *A, int N, int target) {
    int l = 0, r = N-1;

    while (l <= r) {
        int m = (l + r) / 2;

        if (A[m] < target) {
            l = m + 1;
        }
        else if (A[m] > target) {
            r = m - 1;
        }
        else {
            return true;
        }
    }
    return false;
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

        cout << (binary_search(A, N, target) ? "YES" : "NO") << "\n";
    }
    
    return 0;
}