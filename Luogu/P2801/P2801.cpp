#include <bits/stdc++.h>
using namespace std;
int len;
vector<int> st, ed, block_size, id, A, mark;
vector<vector<int> > sorted_blocks;

void init_sqrt(int N) {
    len = sqrt(N);
    st = vector<int>(len+1);
    ed = vector<int>(len+1);
    block_size = vector<int>(len+1);
    id = vector<int>(N+1);
    mark = vector<int>(len+1, 0);
    sorted_blocks = vector<vector<int> >(len+1);

    for (int i = 1; i <= len; ++i) {
        st[i] = N / len * (i - 1) + 1;
        ed[i] = N / len * i;
    }
    ed[len] = N;

    for (int i = 1; i <= len; ++i) {
        for (int j = st[i]; j <= ed[i]; ++j) {
            id[j] = i;
        }
    }

    for (int i = 1; i <= len; ++i) {
        block_size[i] = ed[i] - st[i] + 1;
    }
}

void update_block(int idx) {
    for (int i = 0; i < block_size[idx]; ++i) {
        sorted_blocks[idx][i] = A[st[idx] + i];
    }
    sort(sorted_blocks[idx].begin(), sorted_blocks[idx].end());
}

int main() {
    ios::sync_with_stdio(0);
    int N, Q;
    cin >> N >> Q;

    A = vector<int>(N+1, 0);
    init_sqrt(N);


    for (int i = 1; i <= N; ++i) {
        cin >> A[i];
    }

    for (int i = 1; i <= len; ++i) {
        for (int j = st[i]; j <= ed[i]; ++j) {
            sorted_blocks[i].push_back(A[j]);
        }
        sort(sorted_blocks[i].begin(), sorted_blocks[i].end());
    }

    while (Q--) {
        char op;
        cin >> op;

        if (op == 'M') {
            int l, r, w;
            cin >> l >> r >> w;

            if (id[l] == id[r]) {
                for (int i = l; i <= r; ++i) {
                    A[i] += w;
                }
                update_block(id[l]);
            }
            else {
                for (int i = l; i <= ed[id[l]]; ++i) {
                    A[i] += w;
                }
                update_block(id[l]);
                for (int i = st[id[r]]; i <= r; ++i) {
                    A[i] += w;
                }
                update_block(id[r]);
                for (int i = id[l] + 1; i < id[r]; ++i) {
                    mark[i] += w;
                }
            }
        }
        else {
            int l, r, c;
            int cnt = 0;
            cin >> l >> r >> c;

            if (id[l] == id[r]) {
                for (int i = l; i <= r; ++i) {
                    if (A[i] + mark[id[l]] >= c) {
                        cnt++;
                    }
                }
            }
            else {
                for (int i = l; i <= ed[id[l]]; ++i) {
                    if (A[i] + mark[id[l]] >= c) {
                        cnt++;
                    }
                }
                for (int i = st[id[r]]; i <= r; ++i) {
                    if (A[i] + mark[id[r]] >= c) {
                        cnt++;
                    }
                }

                for (int i = id[l] + 1; i < id[r]; ++i) {
                    cnt += sorted_blocks[i].end() - lower_bound(sorted_blocks[i].begin(), sorted_blocks[i].end(), c - mark[i]);
                }
            }
        
            cout << cnt << "\n";
        }

    }

    return 0;
}