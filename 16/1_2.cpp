#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct ArrayHash {
    size_t operator()(const array<ll, 3>& arr) const {
        size_t seed = 0;
        for (ll val : arr) {
            seed ^= hash<ll>{}(val) + 0x9e3778b9 + (seed << 6) + (seed >> 2); 
        }
        return seed;
    }
};

vector<array<ll, 2>> DIRS = {{1,0}, {0, 1}, {-1, 0}, {0, -1}};

ll getMinScore(ll sx, ll sy, int dir, const vector<string>& grid) {
    unordered_map<array<ll, 3>, ll, ArrayHash> visited;
    queue<array<ll, 4>> q;
    q.push({sx, sy, dir, 0});
    visited[{sx, sy, dir}] = 0;
    ll minVal = INT64_MAX;
    while (!q.empty()) {
        auto [x, y, d, s] = q.front();
        q.pop();
        int dc = (d + 1) > 3 ? 0 : (d + 1);
        int da = (d - 1) < 0 ? 3 : (d - 1);
        for (int direct : {dc, da}) {
            if (visited.count({x, y, direct}) != 0) {
                if (visited[{x, y, direct}] > s + 1000) {
                    visited[{x, y, direct}] = s + 1000;
                    q.push({x, y, direct, s + 1000});
                }
            } else {
                visited[{x, y, direct}] = s + 1000;
                q.push({x, y, direct, s + 1000});
            }
        }
        x += DIRS[d][0];
        y += DIRS[d][1];
        if (grid[y][x] == 'E') {
            minVal = min(minVal, s+1);
        } else if (grid[y][x] != '#') {
            if (visited.count({x, y, d}) != 0) {
                if (visited[{x, y, d}] > s + 1) {
                    visited[{x, y, d}] = s + 1;
                    q.push({x, y, d, s + 1});
                }
            } else {
                visited[{x, y, d}] = s + 1;
                q.push({x, y, d, s + 1});
            }
        }
    }
    return minVal;
}

unordered_map<array<ll, 3>, ll, ArrayHash> getVisited(ll sx, ll sy, int dir, const vector<string>& grid) {
    unordered_map<array<ll, 3>, ll, ArrayHash> visited;
    queue<array<ll, 4>> q;
    q.push({sx, sy, dir, 0});
    visited[{sx, sy, dir}] = 0;
    ll minVal = INT64_MAX;
    while (!q.empty()) {
        auto [x, y, d, s] = q.front();
        q.pop();
        int dc = (d + 1) > 3 ? 0 : (d + 1);
        int da = (d - 1) < 0 ? 3 : (d - 1);
        for (int direct : {dc, da}) {
            if (visited.count({x, y, direct}) != 0) {
                if (visited[{x, y, direct}] > s + 1000) {
                    visited[{x, y, direct}] = s + 1000;
                    q.push({x, y, direct, s + 1000});
                }
            } else {
                visited[{x, y, direct}] = s + 1000;
                q.push({x, y, direct, s + 1000});
            }
        }
        x += DIRS[d][0];
        y += DIRS[d][1];
        if (grid[y][x] == 'E') {
            minVal = min(minVal, s+1);
        } else if (grid[y][x] != '#') {
            if (visited.count({x, y, d}) != 0) {
                if (visited[{x, y, d}] > s + 1) {
                    visited[{x, y, d}] = s + 1;
                    q.push({x, y, d, s + 1});
                }
            } else {
                visited[{x, y, d}] = s + 1;
                q.push({x, y, d, s + 1});
            }
        }
        
    }
    return visited;
}

set<array<ll, 2>> getBestSeats(ll ex, ll ey, unordered_map<array<ll, 3>, ll, ArrayHash>& visited, const vector<string>& grid, ll maxVal) {
    queue<array<ll, 4>> q;
    for (int i = 0; i < 4; ++i) {
        q.push({ex, ey, i, maxVal});
    }
    set<array<ll, 2>> bestSeats;
    while (!q.empty()) {
        auto [x, y, d, s] = q.front();
        q.pop();
        bestSeats.insert({x, y});
        int da = (d + 1) > 3 ? 0 : (d + 1);
        int dc = (d - 1) < 0 ? 3 : (d - 1);
        for (int direct : {dc, da}) {
            if (visited.count({x, y, direct}) && visited[{x, y, direct}] == s - 1000) {
                q.push({x, y, direct, s - 1000});
            }
        }
        x -= DIRS[d][0];
        y -= DIRS[d][1];
        if (grid[y][x] != '#') {
            if (visited.count({x, y, d}) && visited[{x, y, d}] == s - 1) {
                q.push({x, y, d, s - 1});
            }
        }
    } 
    return bestSeats;
}

int main() {
    ifstream inputFile("input.txt");
    string line;
    vector<string> grid;
    smatch match;
    ll sx, sy, ex, ey;
    int y = 0;
    while (getline(inputFile, line)) {
        for (int x = 0; x < line.size(); ++x) {
            if (line[x] == 'S') {
                sx = x;
                sy = y;
            } else if (line[x] == 'E') {
                ex = x;
                ey = y;
            }

        }
        grid.push_back(line);
        ++y;
    }
    ll s = getMinScore(sx, sy, 0, grid);
    unordered_map<array<ll, 3>, ll, ArrayHash> visited = getVisited(sx, sy, 0, grid);
    set<array<ll, 2>> bestSeats = getBestSeats(ex, ey, visited, grid, s);
    cout << "Part 1: " << s << "\nPart 2: " << bestSeats.size() << endl;
    return 0;
}