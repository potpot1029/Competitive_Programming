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

    int N, K, G;
    string CD;
    map<pair<long long, long long>, int> hash_pop;
    cin >> N >> K;
    cin >> CD;
    CD = CD + CD;
    Hash hash_CD(CD);

    cin >> G;
    for (int i = 1; i <= G; ++i) {
        string popular_game;
        cin >> popular_game;

        Hash temp_hash(popular_game);
        hash_pop[temp_hash.get_hash(0, temp_hash.n-1)] = i;
    }


    for (int i = 0; i < K; ++i) {
        vector<int> popular_games_in_CD;
        map<int, bool> vis;
        bool flag = false;
        for (int j = i, cnt = 1; cnt <= N; j += K, cnt++) {
            pair<long long, long long> cur_hash = hash_CD.get_hash(j, j + K - 1);
            // cout << CD.substr(j, K) << " " << cur_hash.first << " " << i << " " << j << "\n";
            if (hash_pop.count(cur_hash) && !vis[hash_pop[cur_hash]]) {
                popular_games_in_CD.push_back(hash_pop[cur_hash]);
                vis[hash_pop[cur_hash]] = true;
            }
            else {
                flag = true;
                break;
            }
        }
        if (flag) {
            continue;
        }
        cout << "YES\n";
        for (auto games_idx : popular_games_in_CD) {
            cout << games_idx << " ";
        }
        cout << "\n";
        return 0;
    }
    
    cout << "NO\n";
    return 0;
}