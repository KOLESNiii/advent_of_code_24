#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

unordered_map<string, set<string>> m;

void findLargestClique(vector<string>& current, vector<string>& best, vector<string>& candidates, int depth = 0) {
    if (candidates.empty()) {
        if (current.size() > best.size()) {
            best = current;
        }
        return;
    }

    for (int i = 0; i < candidates.size(); ++i) {
        string node = candidates[i];
        current.push_back(node);
        vector<string> nextCandidates;
        for (int j = i + 1; j < candidates.size(); ++j) {
            if (m[node].count(candidates[j])) {
                nextCandidates.push_back(candidates[j]);
            }
        }
        findLargestClique(current, best, nextCandidates, depth + 1);
        current.pop_back();
    }
}

int main() {
    ifstream inputFile("input.txt");
    regex pattern(R"(([a-z]{2})-([a-z]{2}))");
    smatch match;
    string line;
    unordered_set<string> unique;
    while (getline(inputFile, line)) {
        if (regex_match(line, match, pattern)) {
            string a = match[1];
            string b = match[2];
            unique.insert(a);
            unique.insert(b);
            if (!m.count(a)) {
                m[a] = {b};
            } else {
                m[a].insert(b);
            }
            if (!m.count(b)) {
                m[b] = {a};
            } else {
                m[b].insert(a);
            }
        }
    }
    vector<array<string, 3>> s;
    ll sum = 0;
    for (auto& [k, vals1] : m) {
        for (string val1 : vals1) {
            set<string> vals2 = m[val1];
            for (string val2 : vals2) {
                set<string> vals3 = m[val2];
                for (string val3 : vals3) {
                    if (val3 == k) {
                        s.push_back({val1, val2, val3});
                        if (val1[0] == 't' || val2[0] == 't' || val3[0] == 't') {
                            sum ++;
                        }
                    }
                }
            }
        }
    }
    vector<string> currentClique, maxClique;
    vector<string> nodes(unique.begin(), unique.end());
    findLargestClique(currentClique, maxClique, nodes);
    sort(maxClique.begin(), maxClique.end());
    sum /= 6;
    cout << "Part 1: " << sum << "\nPart 2: ";
    for (string& s : maxClique) {
        cout << s << ",";
    }
    cout << endl;
    return 0;
}
