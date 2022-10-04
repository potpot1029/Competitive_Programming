/**
 * Modified from: https://cp-algorithms.com/string/string-hashing.html#determine-the-number-of-different-substrings-in-a-string
 * TODO:
 * - [ ] generic method
 *      - [ ] give the numerical value of each elements 
 * - [ ] good P values
**/
pair<vector<long long>, vector<long long>> calculate_prefix_hash(string const& s) {
    int n = s.size();

    const int P1 = 31, P2 = 29;
    const int MOD = 1e9 + 9;
    vector<long long> p_pow1(n), p_pow2(n);
    p_pow1[0] = p_pow2[0] = 1;
    for (int i = 1; i < n; i++) {
        p_pow1[i] = (p_pow1[i-1] * P1) % MOD;
        p_pow2[i] = (p_pow2[i-1] * P2) % MOD;
    }

    vector<long long> h1(n + 1, 0), h2(n + 1, 0);
    for (int i = 0; i < n; i++) {
        h1[i+1] = (h1[i] + (s[i] - 'a' + 1) * p_pow1[i]) % MOD;
        h2[i+1] = (h2[i] + (s[i] - 'a' + 1) * p_pow2[i]) % MOD;
    }
    return {h1, h2};
}