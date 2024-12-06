#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<ll> rotateRight(vector<ll> dir) {
    return {-dir[1], dir[0]};
}

int main() {
    ifstream inputFile("input.txt");
    ifstream ruleFile("rules.txt");
    string line;
    set<vector<ll>> obstacles;
    set<vector<ll>> dots;
    vector<ll> curPos;
    ll y = 0;
    ll maxX, maxY;
    while (getline(inputFile, line)) {
        ll x = 0;
        vector<ll> temp;
        istringstream iss(line);
        char tk;
        while (iss >> tk) {
            if (tk == '^') {
                cout << x << ", " << y << endl;
                curPos = {x, y};
            } else if (tk == '#') {
                obstacles.insert({x, y});
            } else if (tk == '.') {
                dots.insert({x, y});
            }
            ++x;
        }
        maxX = x;
        ++y;
    }
    maxY = y;
    ll s = 0;
    vector<ll> curDir = {0, -1};
    vector<ll> startDir = curDir;
    vector<ll> startPos = curPos;
    set<vector<ll>> visitedFirst;
    visitedFirst.insert(startPos);
    while (curPos[0] < maxX && curPos[1] < maxY && curPos[0] >= 0 && curPos[1] >= 0) {
        ll curX = curPos[0];
        ll curY = curPos[1];
        ll dX = curDir[0];
        ll dY = curDir[1];
        if (obstacles.count({curX + dX, curY + dY}) == 0) {
            curPos = {curX + dX, curY + dY};
            if (curPos[0] <= maxX && curPos[1] <= maxY && curPos[0] >= 0 && curPos[1] >= 0 && dots.count({curX, curY}) != 0) {
                visitedFirst.insert({curX, curY});
            }
        } else {
            curDir = rotateRight(curDir);
        }
    }
    set<vector<ll>> visited;
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