#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll XMAX = 70;
ll YMAX = 70;
ll NUMBYTES = 1024;

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
};

vector<array<ll, 2>> DIRS = {{1,0}, {0, 1}, {-1, 0}, {0, -1}};

pair<ll, unordered_map<array<ll, 2>, ll, ArrayHash>> getMinScore(const unordered_set<array<ll, 2>, ArrayHash>& blocked) {
    unordered_map<array<ll, 2>, ll, ArrayHash> visited;
    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<>> q;
    q.push({0, 0, 0});
    visited[{0, 0}] = 0;
    ll minVal = INT64_MAX;
    while (!q.empty()) {
        auto [x, y, s] = q.top();
        q.pop();
        for (auto [dx, dy] : DIRS) {
            ll nx = x + dx;
            ll ny = y + dy;
            if (nx > XMAX || ny > YMAX || nx < 0 || ny < 0) {
                continue;
            }
            if (nx == XMAX && ny == YMAX) {
                return {s+1, visited};
            }
            if (!blocked.count({nx, ny})) {
                if (!visited.count({nx, ny}) || visited[{nx, ny}] > s+1) {
                    visited[{nx, ny}] = s+1;
                    minVal = min(s+1, minVal);
                    q.push({nx, ny, s+1});
                }
            }
        }
    }
    return {-1, visited};
}

unordered_set<array<ll, 2>, ArrayHash> getRoute(unordered_map<array<ll, 3>, ll, ArrayHash>& visited, ll maxVal) {
    queue<array<ll, 3>> q;
    q.push({XMAX, YMAX, maxVal});
    unordered_set<array<ll, 2>, ArrayHash> route;
    while (!q.empty()) {
        auto [x, y, s] = q.front();
        q.pop();
        route.insert({x, y});
        for (auto [dx, dy] : DIRS) {
            ll nx = x + dx;
            ll ny = y + dy;
            if (visited.count({nx, ny}) && visited[{nx, ny}] == s - 1) {
                q.push({nx, ny, s - 1});
            }
        }
    } 
    return route;
}

int main() {
    ifstream inputFile("input.txt");
    unordered_set<array<ll, 2>, ArrayHash> blocked;
    queue<array<ll, 2>> q;
    regex pattern(R"((\d+),(\d+))");
    smatch match;
    string line;
    ll countBytes = 0;
    while (getline(inputFile, line)) {
        if (regex_search(line, match, pattern)) {
            ll x = stoll(match[1]);
            ll y = stoll(match[2]);
            if (countBytes < NUMBYTES) {
                blocked.insert({x, y});
                countBytes ++;
            } else {
                q.push({x, y});
            }
        }
    }
    auto [s, visited] = getMinScore(blocked);
    cout << "Part 1: " << s << endl;
    while (!q.empty()) {
        array<ll, 2> nb = q.front();
        q.pop();
        blocked.insert(nb);
        if (visited.count(nb)) {
            auto [s, visited] = getMinScore(blocked);
            if (s == -1) {
                cout << "Part 2: " << nb[0] << "," << nb[1] << endl;
                break;
            }
        }
    }
    return 0;
}