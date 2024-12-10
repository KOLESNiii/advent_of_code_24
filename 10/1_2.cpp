#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int getTrailHeadScore(int x, int y, vector<vector<int>> grid, int xMax, int yMax, set<array<int, 2>>& visited, bool isPt2 = false) {
    if (!isPt2) {
        visited.insert({x, y});
    }
    int thisHeight = grid[y][x];
    int targetHeight = thisHeight+1;
    array<int, 2> up = {x, y-1};
    array<int, 2> down = {x, y+1};
    array<int, 2> right = {x+1, y};
    array<int, 2> left = {x-1, y};
    vector<array<int, 2>> poss = {up, down, right, left};
    int s = 0;
    for (array<int, 2> pos : poss) {
        if (pos[0] < xMax && pos[1] < yMax && pos[0] >= 0 && pos[1] >= 0 && visited.count(pos) == 0) {
            if (grid[pos[1]][pos[0]] == targetHeight) {
                if (targetHeight == 9) {
                    if (!isPt2) {
                        visited.insert(pos);
                    }
                    s ++;
                } else {
                    s += getTrailHeadScore(pos[0], pos[1], grid, xMax, yMax, visited, isPt2);
                }
            }
        }
    }
    return s;
}

int main() {
    ifstream inputFile("input.txt");
    vector<vector<int>> grid;
    vector<array<int, 2>> starts;
    char c;
    string line;
    int y = 0;
    int xMax, yMax;
    while (getline(inputFile, line)) {
        int x = 0;
        istringstream iss(line);
        vector<int> temp;
        while (iss >> c) {
            int val = c - '0';
            temp.push_back(val);
            if (val == 0) {
                starts.push_back({x, y});
            }
            x ++;
        }
        grid.push_back(temp);
        xMax = x;
        y ++;
    }
    yMax = y;
    cout << endl;
    
    ll s = 0;
    ll q = 0;
    for (auto [x, y] : starts) {
        set<array<int, 2>> emptyVisited = {};
        int val = getTrailHeadScore(x, y, grid, xMax, yMax, emptyVisited);
        s += val;
        emptyVisited.clear();
        val = getTrailHeadScore(x, y, grid, xMax, yMax, emptyVisited, true);
        q += val;
    }
    cout << "Part 1: " << s << endl << "Part 2: " << q << endl;
    return 0;
}