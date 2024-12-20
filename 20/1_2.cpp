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

tuple<unordered_set<array<ll, 2>, ArrayHash>, vector<vector<ll>>> getDistanceMatrix(vector<vector<bool>>& blocked, array<ll, 2>& start, array<ll, 2>& end) {
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
            return {visited, dist};
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
    return {visited, dist};
}

unordered_set<array<ll, 4>, ArrayHash> getAllCheats(unordered_set<array<ll, 2>, ArrayHash>& possible, vector<vector<bool>>& blocked, vector<vector<ll>>& dist, ll maxTime) {
    unordered_set<array<ll, 4>, ArrayHash> s;

    for (auto [x, y] : possible) {
        queue<array<ll, 3>> q;
        unordered_set<array<ll, 3>, ArrayHash> visited;
        q.push({0, x, y});
        visited.insert({0, x, y});
        while (!q.empty()) {
            auto [n, tx, ty] = q.front();
            q.pop();

            for (auto [dx, dy] : DIRS) {
                ll nx = tx + dx, ny = ty + dy;

                if (nx < 0 || nx > XMAX || ny < 0 || ny > YMAX) continue;
                if (n < maxTime && !visited.count({n+1, nx, ny})) {
                    visited.insert({n+1, nx, ny});
                    q.push({n+1, nx, ny});
                    if (possible.count({nx, ny})) {
                        ll timeSaved = dist[nx][ny] - dist[x][y] - (n+1);
                        if (timeSaved >= 100) {
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
            if (c == 'S') start = {x, y};
            else if (c == 'E') end = {x, y};
            x ++;
        }
        blocked.push_back(temp);
        XMAX = x;
        y ++;
    }
    YMAX = y;
    auto [visited, dist] = getDistanceMatrix(blocked, start, end);
    array<ll, 2> limits = {2, 20};
    for (int i = 0; i < 2; ++i) {
        unordered_set<array<ll, 4>, ArrayHash> all = getAllCheats(visited, blocked, dist, limits[i]);
        cout << "Part " << i+1 << ": " << all.size() << endl;
    }
    return 0;
}
