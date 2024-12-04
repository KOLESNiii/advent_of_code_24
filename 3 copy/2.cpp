#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Function to check if a given position forms an "X-MAS" pattern
bool isValid(vector<vector<char>> grid, int x, int y) {
    if (x - 1 >= 0 && x + 1 < grid.size() && y - 1 >= 0 && y + 1 < grid[0].size()) {
        if (grid[x][y] == 'A') {
            return (((grid[x - 1][y - 1] == 'M' && grid[x + 1][y + 1] == 'S') || (grid[x - 1][y - 1] == 'S' && grid[x + 1][y + 1] == 'M')) &&
            ((grid[x - 1][y + 1] == 'M' && grid[x + 1][y - 1] == 'S') || (grid[x - 1][y + 1] == 'S' && grid[x + 1][y - 1] == 'M')));
        }
    } 
    return false;
}

int main() {
    ifstream inputFile("input.txt");
    string line;
    vector<vector<char>> grid;
    while (getline(inputFile, line)) {
        vector<char> temp(line.begin(), line.end());
        grid.push_back(temp);
    }
    ll s = 0;
    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[0].size(); ++j) {
            if (isValid(grid, i, j)) {
                ++s;
            }
        }
    }
    cout << s;
    return 0;
}