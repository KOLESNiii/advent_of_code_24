#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ifstream inputFile("input.txt");
    ifstream ruleFile("rules.txt");
    string line;
    vector<vector<ll>> grid;
    while (getline(inputFile, line)) {
        vector<ll> temp;
        istringstream iss(line);
        string tk;
        while (getline(iss, tk, ',')) {
            ll a = stoll(tk);
            temp.push_back(a);
        }
        grid.push_back(temp);
    }
    map<ll, set<ll>> ms;
    while (getline(ruleFile, line)) {
        ll a, b;
        regex pattern(R"((\d+)\|(\d+))");
        smatch matches;
        auto it = sregex_iterator(line.begin(), line.end(), pattern);
        auto end = sregex_iterator();
        for (; it != end; ++it) {
            smatch match = *it;
            a = stoll(match[1]);
            b = stoll(match[2]);
            if (ms.count(a) == 0) {
                ms.insert({a, set<ll> {b}});
            } else {
                ms[a].insert(b);
            }
        }
    }
    auto comparison = [&ms](ll a, ll b) {
        if (ms.count(a) == 0) {
            return false;
        } else {
            if (ms[a].count(b)) {
                return true;
            } else {
                return false;
            }
        }
    };
    ll s = 0;
    ll q = 0;
    for (ll i = 0; i < grid.size(); ++i) {
        vector<ll> gridCopy = grid[i];
        sort(gridCopy.begin(), gridCopy.end(), comparison);
        bool isSame = true;
        for (ll j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j] != gridCopy[j]) {
                isSame = false;
            }
        }
        if (isSame) {
            s += gridCopy[gridCopy.size()/2];
        } else {
            q += gridCopy[gridCopy.size()/2];
        }
    }
    cout << "Part 1: " << s << " Part 2: " << q << endl;
    return 0;
}