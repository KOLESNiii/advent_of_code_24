#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<char> inOrder = {'X', 'M', 'A', 'S'};

bool isValidCoordinate(ll x, ll y, ll rows, ll cols) {
    return x >= 0 && y >= 0 && x < rows && y < cols;
}

vector<pair<ll, ll>> directions = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
};

bool isValidStart(vector<vector<char>> grid, ll x, ll y) {
    ll rows = grid.size();
    ll cols = grid[0].size();
    for (pair d : directions) {
        int dx = d.first;
        int dy = d.second;
        ll cx = x;
        ll cy = y;
        bool valid = true;
        for (char c : inOrder) {
            if (!isValidCoordinate(cx, cy, rows, cols) || grid[cx][cy] != c) {
                valid = false;
                break;
            }
            cx += dx;
            cy += dy;
        }
        if (valid) return true;
    }
    return false;
}

int main() {
    ifstream inputFile("input.txt");
    string line;
    vector<vector<char>> grid;
    while (getline(inputFile, line)) {
        vector<char> temp(line.begin(), line.end());
        grid.push_back(temp);
    }
    ll s = 0;
    for (ll i = 0; i < grid.size(); ++i) {
        for (ll j = 0; j < grid[0].size(); ++j) {
            if (grid[i][j] == 'X' && isValidStart(grid, i, j)) {
                s++;
            }
        }
    }
    cout << s;
    return 0;
}