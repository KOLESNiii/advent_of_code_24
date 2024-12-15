#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool isValid(ll x, ll y, ll xMax, ll yMax) {
    return x >= 0 && x < xMax && y >= 0 && y < yMax;
}

ll dfs(int x, int y, char c, vector<vector<char>> &grid, vector<vector<bool>> &visited, ll xMax, ll yMax, ll &perimeter) {
    visited[y][x] = true;
    ll size = 1;
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (!isValid(nx, ny, xMax, yMax) || grid[ny][nx] != c){
            perimeter++;
        } else if (!visited[ny][nx]) {
            //cout << "Added ";
            //cout << nx << ", " << ny << endl;
            size += dfs(nx, ny, c, grid, visited, xMax, yMax, perimeter);
        }
    }
    return size;
}

int main() {
    ifstream inputFile("input.txt");
    string line;
    vector<vector<char>> grid;
    vector<vector<bool>> visited;
    ll y = 0;
    ll maxX, maxY;
    while (getline(inputFile, line)) {
        ll x = 0;
        vector<char> temp;
        vector<bool> tempB;
        istringstream iss(line);
        char tk;
        while (iss >> tk) {
            temp.push_back(tk);
            tempB.push_back(false);
            ++x;
        }
        grid.push_back(temp);
        visited.push_back(tempB);
        maxX = x;
        ++y;
    }
    //cout << "made grid" << endl;
    maxY = y;

    map<char, vector<ll>> areas;

    for (int i = 0; i < maxY; ++i) {
        for (int j = 0; j < maxX; ++j) {
            if (!visited[i][j]) {
                ll perimeter = 0;
                char target = grid[i][j];
                //cout << target << " at: " << j << ", " << i << endl;
                int size = dfs(j, i, target, grid, visited, maxX, maxY, perimeter);
                //cout << size << ", " << perimeter << endl;
                areas[target].push_back(size * perimeter);
            }
        }
    }

    ll s = 0;
    for (auto [c, ns] : areas) {
        for (ll n : ns) {
            s += n;
        }
    }
    cout << s << endl;
    return 0;
}