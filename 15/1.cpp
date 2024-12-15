#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll HEIGHT = 103;
ll WIDTH = 101;

pair<ll, ll> calcPos(ll x, ll y, ll vx, ll vy) {
    x += 100 * vx;
    y += 100 * vy;
    x = x % WIDTH;
    y = y % HEIGHT;
    x = (x < 0) ? x + WIDTH : x;
    y = (y < 0) ? y + HEIGHT : y;
    return {x, y}; 
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
            for (int x = 0; x < line.size(); ++x) {
                if (line[x] == '@') {
                    cx = x;
                    cy = y;
                }

            }
            map.push_back(line);
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
        if (map[cy+dy][cx+dx] == '.') {
            map[cy][cx] = '.';
            cy += dy;
            cx += dx;
            map[cy][cx] = '@';
            //cout << "moved @ to " << cx << ", " << cy << endl;
        } else if (map[cy+dy][cx+dx] == 'O'){
            queue<array<ll, 2>> q;
            ll nx = cx+dx;
            ll ny = cy+dy;
            while (map[ny][nx] == 'O') {
                q.push({nx, ny});
                nx += dx;
                ny += dy;
            }
            q.push({nx, ny});
            if (map[ny][nx] == '.') {
                map[cy][cx] = '.';
                cy += dy;
                cx += dx;
                auto [nx, ny] = q.front();
                map[ny][nx] = '@';
                //cout << "moved @ to " << nx << ", " << ny << endl;
                q.pop();
                while (!q.empty()) {
                    auto [nx, ny] = q.front();
                    //cout << "moved O to " << nx << ", " << ny << endl;
                    map[ny][nx] = 'O';
                    q.pop();
                }
            }
        }
    }
    ll s = 0;
    for (ll y = 0; y < map.size(); ++y) {
        for (ll x = 0; x < map[0].size(); ++x) {
            //cout << map[y][x]; 
            if (map[y][x] == 'O') {
                s +=  100 * y + x;
            }
        }
        //cout << endl;
    }
    cout << s << endl;
    return 0;
}