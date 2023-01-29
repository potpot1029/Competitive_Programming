#include <bits/stdc++.h>
using namespace std;
unsigned long long W, H, N;

int f(unsigned long long x) {
    unsigned long long no_of_rec = (x / W) * (x / H);
    return (no_of_rec >= N);
}

int main() {
    ios::sync_with_stdio(0);
    cin >> W >> H >> N;

    // binary search for the answer
    unsigned long long l = 1, r = max(W, H) * N;
    while (l + 1 < r) {
        unsigned long long m = (l + r) / 2;
        // cout << "cur:" << m << "\n";

        if (f(m)) {
            r = m;
        }
        else {
            l = m;
        }
    }

    cout << r << "\n";
    return 0;
}