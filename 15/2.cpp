#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool canMoveBlocks(int dx, int dy, ll cx, ll cy, vector<string>& map) {
    if (map[cy][cx] == '#') {
        return false;
    } else if (map[cy][cx] == '.') {
        return true;
    } else {
        if (dy != 0) {
            if (map[cy][cx] == '[') {
                return canMoveBlocks(dx, dy, cx, cy+dy, map) && canMoveBlocks(dx, dy, cx+1, cy+dy, map);
            } else {
                return canMoveBlocks(dx, dy, cx, cy+dy, map) && canMoveBlocks(dx, dy, cx-1, cy+dy, map);
            }
        } else {
            return canMoveBlocks(dx, dy, cx+dx, cy+dy, map);
        }
    }
}

void moveBlocks(int dx, int dy, ll cx, ll cy, vector<string>& map) {
    if (map[cy][cx] == '.') {
        return;
    }
    if (dy != 0) {
        if (map[cy][cx] == '[') {
            moveBlocks(dx, dy, cx+1, cy+dy, map);
            map[cy+dy][cx+1] = map[cy][cx+1];
            map[cy][cx+1] = '.';
        } else {
            moveBlocks(dx, dy, cx-1, cy+dy, map);
            map[cy+dy][cx-1] = map[cy][cx-1];
            map[cy][cx-1] = '.';
        }
    }
    moveBlocks(dx, dy, cx+dx, cy+dy, map);
    map[cy+dy][cx+dx] = map[cy][cx];
    map[cy][cx] = '.';
}


int main() {
    ifstream inputFile("input.txt");
    string line;
    vector<array<ll, 2>> moves;
    vector<string> map;
    smatch match;
    ll cx, cy;
    bool isMap = true;
    int y = 0;
    while (getline(inputFile, line)) {
        if (line.size() == 0) {
            isMap = false;
        } else if (isMap) {
            string temp = "";
            for (int x = 0; x < line.size(); ++x) {
                if (line[x] == '@') {
                    cx = 2*x;
                    cy = y;
                    temp += "@.";
                } else if (line[x] == 'O') {
                    temp += "[]";
                } else if (line[x] == '.') {
                    temp += "..";
                } else {
                    temp += "##";
                }
            }
            map.push_back(temp);
        } else {
            for (char m : line) {
                switch (m) {
                    case '<' :
                        moves.push_back({-1, 0});
                        break;
                    case '^' :
                        moves.push_back({0, -1});
                        break;
                    case '>' :
                        moves.push_back({1, 0});
                        break;
                    case 'v' :
                        moves.push_back({0, 1});
                        break;
                    default:
                        break;            
                }
            }
        }
        ++y;
    }
    for (auto [dx, dy] : moves) {
        //cout << dx << ", " << dy << endl;
        if (canMoveBlocks(dx, dy, cx+dx, cy+dy, map)) {
            moveBlocks(dx, dy, cx+dx, cy+dy, map);
            map[cy][cx] = '.';
            map[cy+dy][cx+dx] = '@';
            cx += dx;
            cy += dy;
        }
    }
    ll s = 0;
    for (ll y = 0; y < map.size(); ++y) {
        for (ll x = 0; x < map[0].size(); ++x) {
            cout << map[y][x]; 
            if (map[y][x] == '[') {
                s +=  100 * y + x;
            }
        }
        cout << endl;
    }
    cout << s << endl;
    return 0;
}