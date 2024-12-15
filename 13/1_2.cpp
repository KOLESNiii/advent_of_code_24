#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll calcMatrix(array<ll, 2> a, array<ll, 2> b, array<ll, 2> target) {
    ll det = a[0] * b[1] - a[1] * b[0];
    ll valA = target[0] * b[1] - target[1] * b[0];
    ll valB = target[1] * a[0] - target[0] * a[1];
    if (det == 0 || valA % det != 0 || valB % det != 0) {
        return 0;
    }
    valA /= det;
    valB /= det;
    if (valA < 0 || valB < 0) {
        return 0;
    }
    return 3 * valA + valB;
}

int main() {
    ifstream inputFile("input.txt");
    string line;
    vector<array<ll, 2>> as, bs, targets;
    std::regex buttonA_regex(R"(Button A: X([+-]\d+), Y([+-]\d+))");
    std::regex buttonB_regex(R"(Button B: X([+-]\d+), Y([+-]\d+))");
    std::regex prize_regex(R"(Prize: X=(\d+), Y=(\d+))");
    while (getline(inputFile, line)) {
        smatch match;
        if (regex_search(line, match, buttonA_regex)) {
            as.push_back({stoi(match[1].str()), stoi(match[2].str())});
        }
        else if (std::regex_search(line, match, buttonB_regex)) {
            bs.push_back({stoi(match[1].str()), stoi(match[2].str())});
        }
        else if (std::regex_search(line, match, prize_regex)) {
            targets.push_back({stoi(match[1].str()), stoi(match[2].str())});
        }
    }

    ll s = 0;
    ll r = 0;
    for (int i = 0; i < targets.size(); ++i) {
        s += calcMatrix(as[i], bs[i], targets[i]);
        targets[i][0] += 10000000000000;
        targets[i][1] += 10000000000000;
        r += calcMatrix(as[i], bs[i], targets[i]);
    }
    cout << s << endl << r << endl;
    return 0;
}