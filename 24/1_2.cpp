#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

unordered_map<string, bool> inputs;

ll convertToBin(vector<bool>& a) {
    ll s = 0;
    ll power = 1;
    for (bool v : a) {
        s += (v ? 1 : 0) * power;
        power <<= 1;
    }
    return s;
}

set<string> wrong(const vector<array<string, 4>>& gates) {
    string highest_z = "z45";
    set<string> wrong;
    for (const auto& [arg1, op, arg2, res] : gates) {
        if (res[0] == 'z' && op != "XOR" && res != highest_z) {
            wrong.insert(res);
        }
        if (op == "XOR" &&
            res[0] != 'x' && res[0] != 'y' && res[0] != 'z' &&
            arg1[0] != 'x' && arg1[0] != 'y' && arg1[0] != 'z' &&
            arg2[0] != 'x' && arg2[0] != 'y' && arg2[0] != 'z') {
            wrong.insert(res);
        }
        if (op == "AND" && arg1 != "x00" && arg2 != "x00") {
            for (const auto& [sarg1, sop, sarg2, sres] : gates) {
                if ((res == sarg1 || res == sarg2) && sop != "OR") {
                    wrong.insert(res);
                }
            }
        }
        if (op == "XOR") {
            for (const auto& [sarg1, sop, sarg2, sres] : gates) {
                if ((res == sarg1 || res == sarg2) && sop == "OR") {
                    wrong.insert(res);
                }
            }
        }
    }
    return wrong;
}

unordered_map<string, bool> simulate(unordered_map<string, bool> init, vector<array<string, 4>>& gates) {
    queue<array<string, 4>> q;
    for (const auto& gate : gates) {
        q.push(gate);
    }
    while (!q.empty()) {
        auto [arg1, op, arg2, res] = q.front();
        q.pop();
        if (init.count(arg1) && init.count(arg2)) {
            bool val1 = init[arg1];
            bool val2 = init[arg2];
            bool result;
            if (op == "AND") result = val1 && val2;
            if (op == "OR") result = val1 || val2;
            if (op == "XOR") result = val1 ^ val2;
            init[res] = result;
        } else {
            q.push({arg1, op, arg2, res});
        }
    }
    return init;
}

int main() {
    ifstream inputFile("input.txt");
    smatch match;
    string line;
    getline(inputFile, line);
    vector<bool> xs, ys;
    while (line != "") {
        stringstream ss(line);
        string strPart;
        int intPart;
        getline(ss, strPart, ':');
        ss >> intPart;
        inputs[strPart] = intPart;
        if (strPart[0] == 'x') {
            xs.push_back(intPart);
        } else if (strPart[0] == 'y') {
            ys.push_back(intPart);
        }
        getline(inputFile, line);
    }
    vector<array<string, 4>> notDoneOps;
    int zCount = 0;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        string arg1, op, arg2, arrow, res;
        ss >> arg1 >> op >> arg2 >> arrow >> res;
        notDoneOps.push_back({arg1, op, arg2, res});
        if (res[0] == 'z') {
            zCount ++;
        }
    }
    vector<bool> results(zCount, 0);
    cout << endl;
    unordered_map<string, bool> pt1 = simulate(inputs, notDoneOps);
    for (auto& [name, val] : pt1) {
        if (name[0] == 'z') {
            int index = stoi(name.substr(1));
            results[index] = val;
        }
    }
    ll s = convertToBin(results);
    set<string> f = wrong(notDoneOps);
    cout << "Part 1: " << s << "\nPart 2: ";
    for (const string a : f) {
        cout << a << ",";
    }
    cout << endl;
    return 0;
}
