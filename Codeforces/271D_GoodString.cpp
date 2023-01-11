#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(0);
    /*
        Input
    */ 
    string s;
    int k;
    cin >> s;

    vector<bool> good_char(26, false);
    for (int i = 0; i < 26; ++i) {
        char c;
        cin >> c;

        good_char[i] = (c == '1' ? 1 : 0);
    }

    cin >> k;

    /*
        Calculating Answer
        1. Compute the number of bad characters for each prefix
        2. Compute the hash1 value for each prefix
        3. Compute for each substring s[l..r]
            a. the number of bad characters: bad_char[r+1]-bad_char[l]
            b. the hash1 value: hash1[r+1]-hash1[l] * p^(n-l+1)
    */
    int n = (int) s.size();
    vector<int> bad_char(n+1, 0);
    vector<long long> hash1(n+1, 0), hash2(n+1, 0);
    set<pair<int,int>> distinct_hash;

    for (int i = 0; i < n; ++i)
        bad_char[i+1] = bad_char[i] + (good_char[s[i]-'a'] ? 0 : 1);

    vector<long long> p_pow1(n), p_pow2(n);
    const int p1 = 31, p2 = 29;
    const int MOD = 1e9 + 9;
    p_pow1[0] = p_pow2[0] = 1;
    for (int i = 1; i < n; i++) {
        p_pow1[i] = (p_pow1[i-1] * p1) % MOD;
        p_pow2[i] = (p_pow2[i-1] * p2) % MOD;
    }

    for (int i = 0; i < n; i++) {
        hash1[i+1] = (hash1[i] + (s[i] - 'a' + 1) * p_pow1[i]) % MOD;
        hash2[i+1] = (hash2[i] + (s[i] - 'a' + 1) * p_pow2[i]) % MOD;
    }

    for (int len = 1; len <= n; ++len) {
        for (int l = 0; l + len <= n; ++l) {
                int cur_bad_char = bad_char[l+len] - bad_char[l];
                long long cur_hash1 = (hash1[l+len] + MOD - hash1[l]) % MOD;
                cur_hash1 = (cur_hash1 * p_pow1[n-l-1]) % MOD;
                long long cur_hash2 = (hash2[l+len] + MOD - hash2[l]) % MOD;
                cur_hash2 = (cur_hash2 * p_pow2[n-l-1]) % MOD;
                
                if (cur_bad_char <= k) {
                    // cout << l << " " << l+len-1 << " " << cur_bad_char << " " << cur_hash << "\n";
                    distinct_hash.insert({cur_hash1, cur_hash2});
                }
        }
    }

    /*
        Output answer: size of distinct_hash
    */
    cout << distinct_hash.size() << "\n";
    return 0;
}