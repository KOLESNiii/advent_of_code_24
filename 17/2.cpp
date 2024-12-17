#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll output(ll A) {
    return (((A % 8) ^ 1) ^ 5 ^ (A >> ((A % 8) ^ 1))) % 8;
}

ll findA(vector<int>& program) {
    vector<ll> possible = {0};
    for (auto it = program.rbegin(); it != program.rend(); ++it) {
        vector<ll> newPossible;
        for (ll p : possible) {
            for (int i = 0; i < 8; ++i) {
                ll np = (p << 3) + i;
                if (output(np) == *it) {
                    newPossible.push_back(np);
                }
            }
        }
        possible = move(newPossible);
    }
    return *min_element(possible.begin(), possible.end());
}

int main() {
    ifstream inputFile("input.txt");
    string line, n;
    for (int i = 0; i < 5; ++i) {
        getline(inputFile, line);
    }
    istringstream iss(line.substr(line.find(':') + 1));
    vector<int> instructions;
    while (getline(iss, n, ',')) {
        instructions.push_back(stoi(n));
    }
    ll smallestPossible = findA(instructions);
    cout << smallestPossible;
    return 0;
}
