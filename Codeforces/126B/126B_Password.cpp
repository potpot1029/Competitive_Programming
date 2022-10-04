#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007

namespace mod_op {
    long long mpow(long long base, long long exponent) {
        long long res = 1;
        while (exponent > 0) {
            if (exponent & 1) {
                res = (res * base) % MOD;
            }
            base = (base * base) % MOD;
            exponent = exponent >> 1;
        }
        return res;
    }

    long long minv(long long base) {
        return mpow(base, MOD - 2);
    }
}
using namespace mod_op;

class Hash {
    public:
        const int P1 = 31, P2 = 29;
        int n;
        long long inv1, inv2;
        vector<long long> p_pow1, p_pow2; 
        vector<long long> prefix1, prefix2;
        vector<long long> invs1, invs2;

        Hash(const string& s) {
            n = s.size();
            p_pow1 = vector<long long>(n),
            p_pow2 = vector<long long>(n);
            prefix1 = vector<long long>(n+1, 0);
            prefix2 = vector<long long>(n+1, 0);
            invs1 = vector<long long>(n);
            invs2 = vector<long long>(n);

            invs1[0] = invs2[0] = 1;
            inv1 = minv(P1), inv2 = minv(P2);
            for (int i = 1; i < n; ++i) {
                invs1[i] = (invs1[i-1] * inv1) % MOD;
            }
            for (int i = 1; i < n; ++i) {
                invs2[i] = (invs2[i-1] * inv2) % MOD;
            }

            p_pow1[0] = p_pow2[0] = 1;
            for (int i = 1; i < n; i++) {
                p_pow1[i] = (p_pow1[i-1] * P1) % MOD;
                p_pow2[i] = (p_pow2[i-1] * P2) % MOD;
            }          

            for (int i = 0; i < n; i++) {
                prefix1[i+1] = (prefix1[i] + (s[i] - 'a' + 1) * p_pow1[i]) % MOD;
                prefix2[i+1] = (prefix2[i] + (s[i] - 'a' + 1) * p_pow2[i]) % MOD;
            }
        }

        pair<long long, long long> get_hash(int left, int right) {
            if (left == 0) {
                return {prefix1[right+1], prefix2[right+1]};
            }
            long long hash1 = (prefix1[right+1] + MOD - prefix1[left]) % MOD * invs1[left] % MOD;
            long long hash2 = (prefix2[right+1] + MOD - prefix2[left]) % MOD * invs2[left] % MOD;
            return {hash1, hash2};
        }
};



int main() {
    ios::sync_with_stdio(0);
    string s;
    cin >> s;

    Hash hash_s(s);

    for (int len = hash_s.n-2; len >= 1; --len) {
        pair<long long, long long> prefix_hash = hash_s.get_hash(0, len-1);
        pair<long long, long long> suffix_hash = hash_s.get_hash(hash_s.n-len, hash_s.n-1);

        if (prefix_hash != suffix_hash)
            continue;

        for (int i = 1; i + len < hash_s.n; ++i) {
            pair<long long, long long> obelix_hash = hash_s.get_hash(i, i+len-1);

            if (prefix_hash == obelix_hash && obelix_hash == suffix_hash) {
                cout << s.substr(i, len) << "\n";
                return 0;
            }
        }
    }
    cout << "Just a legend\n";
    return 0;
}