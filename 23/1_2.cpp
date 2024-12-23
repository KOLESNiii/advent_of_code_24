#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

unordered_map<string, set<string>> m;

void largestFullyConnected(vector<string> &current, unordered_set<string> &potentialNodes, unordered_set<string> &excludedNodes, vector<string> &biggest) {
    if (potentialNodes.empty() && excludedNodes.empty()) {
        if (current.size() > biggest.size()) {
            biggest = current;
        }
        return;
    }

    string pivot;
    if (!potentialNodes.empty()) {
        pivot = *potentialNodes.begin();
    } else {
        pivot = *excludedNodes.begin();
    }

    vector<string> nonNeighbors;
    for (const string &node : potentialNodes) {
        if (!m[pivot].count(node)) {
            nonNeighbors.push_back(node);
        }
    }

    for (const string &node : nonNeighbors) {
        current.push_back(node);
        unordered_set<string> newPotential;
        unordered_set<string> newExcluded;
        for (const string &nn : m[node]) {
            if (potentialNodes.count(nn)) newPotential.insert(nn);
            if (excludedNodes.count(nn)) newExcluded.insert(nn);
        }

        largestFullyConnected(current, newPotential, newExcluded, biggest);
        current.pop_back();
        potentialNodes.erase(node);
        excludedNodes.insert(node);
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
            //cout << a << " to " << b << endl;
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
    unordered_set<string> excluded;
    cout << nodes.size() << endl;
    largestFullyConnected(currentClique, unique, excluded, maxClique);
    sort(maxClique.begin(), maxClique.end());
    sum /= 6;
    cout << "Part 1: " << sum << "\nPart 2: ";
    for (string& s : maxClique) {
        cout << s << ",";
    }
    cout << endl;
    return 0;
}
