#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e6+1;
const int P1 = 1610612741, P2 = 805306457;
const int MOD = 1e9 + 7;
vector<long long> p_pow1(MAXN+10), p_pow2(MAXN+10);

void init_p_pow() {
    p_pow1[0] = p_pow2[0] = 1;
    for (int i = 1; i <= MAXN; i++) {
        p_pow1[i] = (p_pow1[i-1] * P1) % MOD;
        p_pow2[i] = (p_pow2[i-1] * P2) % MOD;
    }
}

pair<long long, long long> calculate_prefix_hash(vector<int> const& s) {
    int n = s.size();

    vector<long long> h1(n + 1, 0), h2(n + 1, 0);
    for (int i = 0; i < n; i++) {
        h1[i+1] = (h1[i] + s[i] * p_pow1[s[i]] % MOD) % MOD;
        h2[i+1] = (h2[i] + s[i] * p_pow2[s[i]] % MOD) % MOD;
    }
    return {h1[n], h2[n]};
}

int main() {
    ios::sync_with_stdio(0);
    /*
        Input
    */ 
    int N, M;
    init_p_pow();
    cin >> N >> M;


    vector<vector<int>> adj(N+1);

    for (int i = 0; i < M; ++i) {
        int v, u;
        cin >> u >> v;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    /*
        Compute answer:
        1. iterate through each vertex v
            a. calculate hash value using adj[v]
            b. push the hash value into a vector
        2. sort the hash values
        3. let the number of elements with hash value x be y
            the contribution to answer is y(y-1)/2
        
        take care of 2 situation:
        1. i and j are not friend
        2. i and j are friend
    */

    // i and j are not friend
    vector<pair<long long, long long>> hash_values;
    for (int i = 1; i <= N; ++i) {
        hash_values.push_back(calculate_prefix_hash(adj[i]));
    }

    sort(hash_values.begin(), hash_values.end());

    // for (auto p : hash_values) {
    //     cout << p.first << " " << p.second << "\n";
    // }

    long long cur_cnt = 1;
    long long ans = 0;
    for (int i = 1; i < (int) hash_values.size(); ++i) {
        if (hash_values[i] != hash_values[i-1]) {
            ans += (cur_cnt * (cur_cnt - 1)) / 2;
            cur_cnt = 1;
        }
        else {
            cur_cnt++;
        }
    }
    ans += (cur_cnt * (cur_cnt - 1)) / 2;

    // i and j are friends
    for (int i = 1; i <= N; ++i) {
        adj[i].push_back(i);
    }
    vector<pair<long long, long long>> hash_values1;
    for (int i = 1; i <= N; ++i) {
        hash_values1.push_back(calculate_prefix_hash(adj[i]));
    }

    sort(hash_values1.begin(), hash_values1.end());

    // for (auto p : hash_values1) {
    //     cout << p.first << " " << p.second << "\n";
    // }

    cur_cnt = 1;
    for (int i = 1; i < (int) hash_values1.size(); ++i) {
        if (hash_values1[i] != hash_values1[i-1]) {
            ans += (cur_cnt * (cur_cnt - 1)) / 2;
            cur_cnt = 1;
        }
        else {
            cur_cnt++;
        }
    }
    ans += (cur_cnt * (cur_cnt - 1)) / 2;
    /*
        Output
    */
    cout << ans << "\n";
    return 0;
}