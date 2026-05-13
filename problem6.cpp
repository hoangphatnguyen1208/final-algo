#include <bits/stdc++.h>

using namespace std;

int k;
vector <vector<int>> a;

class Node {
    public:
        int val;
        int idx;
        int row;

    bool operator> (const Node &other) const {
        return val > other.val;
    }
};

int main() {
    cin >> k;
    cin.ignore();
    a.assign(k, vector<int>(0));
    for (int i = 0; i < k; i++) {
        string line;
        getline(cin, line);

        stringstream ss(line);
        int x;
        while (ss >> x) {
            a[i].push_back(x);
        }
    }

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    for (int i = 0; i < k; i++) {
        if (!a[i].empty()) {
            pq.push({a[i][0], 0, i});
        }
    }
    while (pq.size() != 0) {
        Node cur = pq.top();
        pq.pop();
        cout << cur.val << ' ';
        int idx = cur.idx;
        int row = cur.row;
        if (idx + 1 < a[row].size()) {
            pq.push({a[row][idx + 1], idx + 1, row});
        }
    }
    return 0;
}