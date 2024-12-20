#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll XMAX, YMAX;

struct ArrayHash {
    size_t operator()(const array<ll, 2>& arr) const {
        size_t seed = 0;
        for (ll val : arr) {
            seed ^= hash<ll>{}(val) + 0x9e3778b9 + (seed << 6) + (seed >> 2); 
        }
        return seed;
    }
    size_t operator()(const array<ll, 5>& arr) const {
        size_t seed = 0;
        for (ll val : arr) {
            seed ^= hash<ll>{}(val) + 0x9e3778b9 + (seed << 6) + (seed >> 2); 
        }
        return seed;
    }
    size_t operator()(const array<ll, 3>& arr) const {
        size_t seed = 0;
        for (ll val : arr) {
            seed ^= hash<ll>{}(val) + 0x9e3778b9 + (seed << 6) + (seed >> 2); 
        }
        return seed;
    }
    size_t operator()(const array<ll, 4>& arr) const {
        size_t seed = 0;
        for (ll val : arr) {
            seed ^= hash<ll>{}(val) + 0x9e3778b9 + (seed << 6) + (seed >> 2); 
        }
        return seed;
    }
};

vector<array<ll, 2>> DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

tuple<ll, unordered_set<array<ll, 2>, ArrayHash>, vector<vector<ll>>> getMinScore(vector<vector<bool>>& blocked, array<ll, 2>& start, array<ll, 2>& end) {
    vector<vector<ll>> dist(XMAX + 1, vector<ll>(YMAX + 1, INT64_MAX));
    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<>> pq;
    unordered_set<array<ll, 2>, ArrayHash> visited;
    pq.push({0, start[0], start[1]});
    dist[start[0]][start[1]] = 0;

    while (!pq.empty()) {
        auto [steps, x, y] = pq.top();
        pq.pop();
        visited.insert({x, y});

        if (end[0] == x && end[1] == y) {
            return {steps, visited, dist};
        }

        for (auto [dx, dy] : DIRS) {
            ll nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx <= XMAX && ny >= 0 && ny <= YMAX && !blocked[ny][nx]) {
                if (dist[nx][ny] > steps + 1) {
                    dist[nx][ny] = steps + 1;
                    pq.push({steps + 1, nx, ny});
                }
            }
        }
    }
    return {-1, visited, dist};
}

unordered_set<array<ll, 4>, ArrayHash> getAllCheats(unordered_set<array<ll, 2>, ArrayHash>& possible, vector<vector<ll>>& dist) {
    unordered_set<array<ll, 4>, ArrayHash> s;

    for (auto [x, y] : possible) {
        queue<array<ll, 3>> q;
        unordered_set<array<ll, 3>, ArrayHash> visited;

        for (auto [dx, dy] : DIRS) {
            ll nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx <= XMAX && ny >= 0 && ny <= YMAX) {
                q.push({1, nx, ny});
                visited.insert({1, nx, ny});
            }
        }

        while (!q.empty()) {
            auto [n, tx, ty] = q.front();
            q.pop();

            for (auto [dx, dy] : DIRS) {
                ll nx = tx + dx, ny = ty + dy;

                if (nx < 0 || nx > XMAX || ny < 0 || ny > YMAX) continue;
                if (n < 20 && !visited.count({n+1, nx, ny})) {
                    visited.insert({n+1, nx, ny});
                    q.push({n+1, nx, ny});
                    if (possible.count({nx, ny})) {
                        ll timeSaved = dist[nx][ny] - dist[x][y] - (n+1);
                        if (timeSaved >= 1000) {
                            s.insert({x, y, nx, ny});
                        }
                    }
                }
            }
        }

    }
    return s;
}

int main() {
    ifstream inputFile("input.txt");
    vector<vector<bool>> blocked;
    string line;
    ll y = 0;
    array<ll, 2> start, end;
    while (getline(inputFile, line)) {
        ll x = 0;
        vector<bool> temp;
        for (char c : line) {
            temp.push_back(c == '#');
            if (c == 'S') {
                start = {x, y};
            } else if (c == 'E') {
                end = {x, y};
            }
            x ++;
        }
        blocked.push_back(temp);
        XMAX = x;
        y ++;
    }
    YMAX = y;
    auto [minSteps, visited, dist] = getMinScore(blocked, start, end);
    cout << minSteps << endl;
    unordered_set<array<ll, 4>, ArrayHash> all = getAllCheats(visited, dist);
    ll s = all.size();
    cout << "Part 2: " << s << endl;
    return 0;
}
