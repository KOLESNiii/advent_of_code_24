#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

constexpr ll XMAX = 70;
constexpr ll YMAX = 70;
constexpr ll NUMBYTES = 1024;

vector<array<ll, 2>> DIRS = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

ll getMinScore(vector<vector<bool>>& blocked) {
    vector<vector<ll>> dist(XMAX + 1, vector<ll>(YMAX + 1, INT64_MAX));
    priority_queue<array<ll, 3>, vector<array<ll, 3>>, greater<>> pq;
    pq.push({0, 0, 0});
    dist[0][0] = 0;

    while (!pq.empty()) {
        auto [steps, x, y] = pq.top();
        pq.pop();

        if (x == XMAX && y == YMAX) {
            return steps;
        }

        for (auto [dx, dy] : DIRS) {
            ll nx = x + dx, ny = y + dy;
            if (nx >= 0 && nx <= XMAX && ny >= 0 && ny <= YMAX && !blocked[nx][ny]) {
                if (dist[nx][ny] > steps + 1) {
                    dist[nx][ny] = steps + 1;
                    pq.push({steps + 1, nx, ny});
                }
            }
        }
    }
    return -1;
}

int main() {
    ifstream inputFile("input.txt");
    vector<vector<bool>> blocked(XMAX + 1, vector<bool>(YMAX + 1, false));

    queue<array<ll, 2>> additionalBlocks;
    string line;
    ll countBytes = 0;
    while (getline(inputFile, line)) {
        ll x, y;
        sscanf(line.c_str(), "%lld,%lld", &x, &y);
        if (countBytes < NUMBYTES) {
            blocked[x][y] = true;
            countBytes++;
        } else {
            additionalBlocks.push({x, y});
        }
    }

    ll minSteps = getMinScore(blocked);
    cout << "Part 1: " << minSteps << endl;
    while (!additionalBlocks.empty()) {
        auto [x, y] = additionalBlocks.front();
        additionalBlocks.pop();

        blocked[x][y] = true;
        if (getMinScore(blocked) == -1) {
            cout << "Part 2: " << x << "," << y << endl;
            break;
        }
    }
    return 0;
}
