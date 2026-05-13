#include <bits/stdc++.h>

using namespace std;

int n;

bool col[20];
bool diag1[40];
bool diag2[40];

vector<string> board;
vector<vector<string>> ans;
void backtrack(int row) {
    if (row == n) {
        ans.push_back(board);
        return;
    }

    for (int c = 0; c < n; c++) {
        if (col[c]) continue;
        if (diag1[row-c+n]) continue;
        if (diag2[row+c]) continue;

        board[row][c] = 'Q';
        col[c] = true;
        diag1[row-c+n] = true;
        diag2[row+c] = true;

        backtrack(row + 1);

        board[row][c] = '.';
        col[c] = false;
        diag1[row-c+n] = false;
        diag2[row+c] = false;
    }
}
int main() {
    cin >> n;
    board.assign(n, string(n, '.'));
    
    backtrack(0);

    cout << ans.size() << '\n';

    for (int i = 0; i < ans.size(); i++) {
        for (string s: ans[i]) {
            cout << s << '\n';
        }
        cout << '\n';
    }

    return 0;
}