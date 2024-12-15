#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, -1, 1};

bool isValid(ll x, ll y, ll xMax, ll yMax) {
    return x >= 0 && x < xMax && y >= 0 && y < yMax;
}

ll dfs(int x, int y, char c, vector<vector<char>> &grid, vector<vector<bool>> &visited,
       ll xMax, ll yMax, ll &cornerCount) {
    visited[y][x] = true;
    ll area = 1;

    // For each direction, explore the grid
    for (int i = 0; i < 4; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (!isValid(nx, ny, xMax, yMax) || grid[ny][nx] != c) {
            // Add edge to boundary set
            int p;
        } else if (!visited[ny][nx]) {
            area += dfs(nx, ny, c, grid, visited, xMax, yMax, cornerCount);
        }
    }

    auto checkSpace = [&](ll x_,ll y_) -> bool {
        return isValid(x_, y_, xMax, yMax) && grid[y_][x_] == c;
    };

    // Detect corners for the current cell
    bool top = checkSpace(x, y-1);
    bool bottom = checkSpace(x, y+1);
    bool left = checkSpace(x-1, y);
    bool right = checkSpace(x+1, y);
    bool topLeft = checkSpace(x-1, y-1);
    bool topRight = checkSpace(x+1, y-1);
    bool bottomLeft = checkSpace(x-1, y+1);
    bool bottomRight = checkSpace(x+1, y+1);
    if (!top && !left) {
        cornerCount++;
    }
    if (!top && !right) {
        cornerCount++;
    }
    if (!bottom && !left) {
        cornerCount++;
    }
    if (!bottom && !right) {
        cornerCount++;
    }
    if (right && bottom && !bottomRight) {
        cornerCount++;
    }
    if (left && bottom && !bottomLeft) {
        cornerCount++;
    }
    if (right && top && !topRight) {
        cornerCount++;
    }
    if (left && top && !topLeft) {
        cornerCount++;
    }

    return area;
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

    ll s = 0;

    for (int i = 0; i < maxY; ++i) {
        for (int j = 0; j < maxX; ++j) {
            if (!visited[i][j]) {
                char target = grid[i][j];
                ll sides = 0;
                ll area = dfs(j, i, target, grid, visited, maxX, maxY, sides);
                cout << area << ", " << sides << endl;
                s += area * sides;
            }
        }
    }

    cout << s << endl;
    return 0;
}