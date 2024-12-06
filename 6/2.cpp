#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct VectorHash {
    size_t operator()(const array<ll, 2>& vec) const {
        std::size_t seed = 0;
        for (ll num : vec) {
            seed ^= hash<ll>()(num) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
    size_t operator()(const array<ll, 4>& vec) const {
        std::size_t seed = 0;
        for (ll num : vec) {
            seed ^= hash<ll>()(num) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        }
        return seed;
    }
};

array<ll, 2> rotateRight(array<ll, 2> dir) {
    return {-dir[1], dir[0]};
}

int main() {
    ifstream inputFile("input.txt");
    string line;
    unordered_set<array<ll, 2>, VectorHash> obstacles;
    array<ll, 2> curPos;
    ll y = 0;
    ll maxX, maxY;
    while (getline(inputFile, line)) {
        ll x = 0;
        istringstream iss(line);
        char tk;
        while (iss >> tk) {
            if (tk == '^') {
                curPos = {x, y};
            } else if (tk == '#') {
                obstacles.insert({x, y});
            }
            ++x;
        }
        maxX = x;
        ++y;
    }
    maxY = y;
    ll s = 0;
    array<ll, 2> curDir = {0, -1};
    array<ll, 2> startDir = curDir;
    array<ll, 2> startPos = curPos;
    unordered_set<array<ll, 2>, VectorHash> visitedFirst;
    visitedFirst.insert(startPos);
    while (curPos[0] < maxX && curPos[1] < maxY && curPos[0] >= 0 && curPos[1] >= 0) {
        ll curX = curPos[0];
        ll curY = curPos[1];
        ll dX = curDir[0];
        ll dY = curDir[1];
        if (obstacles.count({curX + dX, curY + dY}) == 0) {
            curPos = {curX + dX, curY + dY};
            if (curPos[0] <= maxX && curPos[1] <= maxY && curPos[0] >= 0 && curPos[1] >= 0) {
                visitedFirst.insert({curX, curY});
            }
        } else {
            curDir = rotateRight(curDir);
        }
    }
    unordered_set<array<ll, 4>, VectorHash> visited;
    for (auto it = visitedFirst.begin(); it != visitedFirst.end(); ++it) {
        ll obstacleX = (*it)[0];
        ll obstacleY = (*it)[1];
        curPos = startPos;
        curDir = startDir;
        while (curPos[0] < maxX && curPos[1] < maxY && curPos[0] >= 0 && curPos[1] >= 0) {
            ll curX = curPos[0];
            ll curY = curPos[1];
            ll dX = curDir[0];
            ll dY = curDir[1];
            if (visited.count({curX, curY, dX, dY}) != 0) {
                ++s;
                break;
            }
            if (obstacles.count({curX + dX, curY + dY}) == 0 && !(curX + dX == obstacleX && curY + dY == obstacleY)) {
                curPos = {curX + dX, curY + dY};
                if (curPos[0] < maxX && curPos[1] < maxY && curPos[0] >= 0 && curPos[1] >= 0) {
                    visited.insert({curX, curY, dX, dY});
                }
            } else {
                visited.insert({curX, curY, dX, dY});
                curDir = rotateRight(curDir);
            }
        }
        visited.clear();
    }
    cout << s << endl;
    return 0;
}