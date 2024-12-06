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
    vector<ll> curDir = {0, -1};
    set<vector<ll>> visited;
    while (curPos[0] < maxX && curPos[1] < maxY && curPos[0] >= 0 && curPos[1] >= 0) {
        ll curX = curPos[0];
        ll curY = curPos[1];
        ll dX = curDir[0];
        ll dY = curDir[1];
        if (obstacles.count({curX + dX, curY + dY}) == 0) {
            curPos = {curX + dX, curY + dY};
            if (curPos[0] < maxX && curPos[1] < maxY && curPos[0] >= 0 && curPos[1] >= 0) {
                visited.insert(curPos);
            }
        } else {
            curDir = rotateRight(curDir);
        }
    }
    cout << visited.size() << endl;
    return 0;
}