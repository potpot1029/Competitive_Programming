#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    int N, M;
    cin >> N >> M;

    vector<int> A(N + 1, 0);
    for (int i = 1; i <= N; ++i)
    {
        cin >> A[i];
    }

    // pre-compute for Sqrt decomposition
    int len = sqrt(N);
    vector<int> id(N + 1, 0), st(len + 1, 0), ed(len + 1, 0), size(len + 1, 0);
    vector<long long> sum(len + 1, 0), mark(len + 1, 0);

    for (int i = 1; i <= len; ++i)
    {
        st[i] = N / len * (i - 1) + 1;
        ed[i] = N / len * i;
    }
    ed[len] = N;

    for (int i = 1; i <= len; ++i)
    {
        for (int j = st[i]; j <= ed[i]; ++j)
        {
            id[j] = i;
            sum[i] += A[j];
        }
    }

    for (int i = 1; i <= len; ++i)
    {
        size[i] = ed[i] - st[i] + 1;
    }

    // range sum
    while (M--)
    {
        int op;
        cin >> op;

        if (op == 1)
        { // range update
            int x, y, k;
            cin >> x >> y >> k;

            if (id[x] == id[y])
            {
                for (int i = x; i <= y; ++i)
                {
                    A[i] += k;
                    sum[id[x]] += k; // it's ok to use id[y]
                }
            }
            else
            {
                for (int i = x; i <= ed[id[x]]; ++i)
                {
                    A[i] += k;
                    sum[id[x]] += k;
                }
                for (int i = st[id[y]]; i <= y; ++i)
                {
                    A[i] += k;
                    sum[id[y]] += k;
                }
                for (int i = id[x] + 1; i < id[y]; ++i)
                {
                    mark[i] += k;
                }
            }
        }
        else
        { // range queries
            int x, y;
            cin >> x >> y;
            long long s = 0;

            if (id[x] == id[y])
            {
                for (int i = x; i <= y; ++i)
                {
                    s += A[i] + mark[id[i]];
                }
            }
            else
            {
                for (int i = x; i <= ed[id[x]]; ++i)
                {
                    s += A[i] + mark[id[i]];
                }
                for (int i = st[id[y]]; i <= y; ++i)
                {
                    s += A[i] + mark[id[i]];
                }
                for (int i = id[x] + 1; i < id[y]; ++i)
                {
                    s += sum[i] + mark[i] * size[i];
                }
            }

            cout << s << "\n";
        }
    }
    return 0;
}