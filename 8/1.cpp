#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool isValid(array<ll,2> p, set<array<ll,2>> used, ll xMax, ll yMax) {
    return used.count(p) == 0 && p[0] >= 0 && p[1] >= 0 && p[0] < xMax && p[1] < yMax;
}

int main() {
    ifstream inputFile("input.txt");
    string line;
    map<char, vector<array<ll, 2>>> m;
    set<char> chars;
    ll y = 0;
    ll yMax, xMax;
    while (getline(inputFile, line)) {
        ll x = 0;
        istringstream iss(line);
        char tk;
        while (iss >> tk) {
            if (tk == '.') {
                bool eh = false;
            } else if (m.count(tk) != 0) {
                m[tk].push_back({x, y});
            } else {
                m[tk] = {{x, y}};
                chars.insert(tk);
            }
            ++x;
        }
        xMax = x;
        ++y;
    }
    yMax = y;
    ll s = 0;
    set<array<ll, 2>> antinode;
    for (char tk: chars) {
        vector<array<ll, 2>> coords = m[tk];
        set<array<ll, 2>> used;
        used.insert(coords.back());
        coords.pop_back();
        int numIts = coords.size();
        for (int i = 0; i < numIts; ++i) {
            array<ll, 2> nextCoord = coords.back();
            coords.pop_back();
            for (array<ll, 2> c : used) {
                ll dx = c[0] - nextCoord[0];
                ll dy = c[1] - nextCoord[1];
                array<ll, 2> possible = {c[0]+dx, c[1]+dy};
                array<ll, 2> possible2 =  {nextCoord[0]-dx, nextCoord[1]-dy};
                if (isValid(possible, antinode, xMax, yMax)) {
                    antinode.insert(possible);
                    ++s;
                }
                if (isValid(possible2, antinode, xMax, yMax)) {
                    antinode.insert(possible2);
                    ++s;
                }
            }
            used.insert(nextCoord);
        }
    }
    cout << "Part 1: " << s << endl;
    return 0;
}