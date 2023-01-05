#include <bits/stdc++.h>
using namespace std;

struct Par {
    int left, right;
    bool operator< (Par a, Par b) {
        return (a.right < b.right) || (a.right == b.right && a.left > b.left);
    }
};

int main() {
    ios::sync_with_stdio(0);
    
    int n;
    cin >> n;

    vector<pair<Par, int>> diffs;
    for (int i = 0; i < n; ++i) {
        string s;
        cin >> s;

        int diff = 0;
        for (char c : s) {
            if (c == '(') {
                if (diff < 0) {
                    right += abs(diff);
                    diff = 0;
                }
                diff++;
            } else if (c == ')') {
                diff--;
            }
        }
        if (diff < 0) {
            right += abs(diff);
        }
        else {
            left += diff;
        }
        diffs.push_back({{left, right}, i+1});
    }

    sort(diffs.begin(), diffs.end());

    bool flag = true; 
    int diff = 0;
    for (auto p : diffs) {
        diff -= p.first.right;
        if (diff < 0) flag = false;
        diff += p.first.left;
    }

    if (flag) {
        for (auto p : diffs) {
            cout << p.second << "\n";
        }
    }
    else {
        cout << "impossible\n";
    }
    return 0;
}
