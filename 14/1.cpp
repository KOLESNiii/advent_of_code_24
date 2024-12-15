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
    vector<array<ll, 2>> as, bs, targets;
    regex pattern(R"(p=(-?\d+),(-?\d+) v=(-?\d+),(-?\d+))");
    smatch match;
    vector<pair<ll, ll>> finalPos;
    while (getline(inputFile, line)) {
        if (regex_search(line, match, pattern)) {
            ll x = stoll(match[1]);
            ll y = stoll(match[2]);
            ll vx = stoll(match[3]);
            ll vy = stoll(match[4]);
            finalPos.push_back(calcPos(x, y, vx, vy));
        }
    }
    ll q1 = 0;
    ll q2 = 0;
    ll q3 = 0;
    ll q4 = 0;
    for (auto [x, y] : finalPos) {
        //cout << x << ", " << y << endl;
        if (x < (WIDTH-1)/2) {
            if (y < (HEIGHT-1)/2) {
                q1 ++;
            } else if (y > (HEIGHT-1)/2) {
                q2 ++;
            }
        } else if (x > (WIDTH-1)/2) {
            if (y < (HEIGHT-1)/2) {
                q3 ++;
            } else if (y > (HEIGHT-1)/2) {
                q4 ++;
            }
        }
    }
    cout << q1 * q2 * q3 * q4 << endl;
    return 0;
}