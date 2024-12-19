#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool canMakeDesign(const string &design, const unordered_set<string> &patterns, unordered_map<string, bool> &memo) {
    if (design.empty()) return true;
    if (memo.count(design)) return memo[design];

    for (const string &pattern : patterns) {
        if (design.find(pattern) == 0) {
            if (canMakeDesign(design.substr(pattern.size()), patterns, memo)) {
                return memo[design] = true;
            }
        }
    }
    return memo[design] = false;
}

ll countDesigns(const string &design, const unordered_set<string> &patterns, unordered_map<string, ll> &memo) {
    if (design.empty()) return 1;
    if (memo.count(design)) return memo[design];

    ll count = 0;
    for (const string &pattern : patterns) {
        if (design.find(pattern) == 0) {
            count += countDesigns(design.substr(pattern.size()), patterns, memo);
        }
    }
    return memo[design] = count;
}

int main() {
    ifstream inputFile("input.txt");
    unordered_set<string> possible;
    vector<string> candidates;
    string line, temp;
    getline(inputFile, line);
    istringstream iss(line);
    while(getline(iss, temp, ',')) {
        temp.erase(remove_if(temp.begin(), temp.end(), ::isspace),temp.end());
        possible.insert(temp);
    }
    getline(inputFile, line);
    while (getline(inputFile, line)) {
        candidates.push_back(line);
    }
    ll one = 0;
    ll two = 0;
    unordered_map<string, bool> memo;
    unordered_map<string, ll> cMemo;
    for (string s : candidates) {
        cMemo.clear();
        if (canMakeDesign(s, possible, memo)) {
            one++;
        }
        two += countDesigns(s, possible, cMemo);
    }
    cout << "Part 1: " << one << "\nPart 2: " << two << endl;
    return 0;
}
