#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

vector<array<ll, 2>> DIRS = {{1,0}, {0, 1}, {-1, 0}, {0, -1}};
// 0 = right, 1 = dowm, 2 = left, 3 = up
map<int, char> getCharFromDir= {
    {0, '>'},
    {1, 'v'},
    {2, '<'},
    {3, '^'}
};

vector<string> gridNums = {
    "#####",
    "#789#",
    "#456#",
    "#123#",
    "##0A#",
    "#####"
};

vector<string> gridDirs = {
    "#####",
    "##^A#",
    "#<v>#",
    "#####"
};

map<char, array<ll, 2>> numPos = {
    {'7' , {1, 1}},
    {'8' , {2, 1}},
    {'9' , {3, 1}},
    {'4' , {1, 2}},
    {'5' , {2, 2}},
    {'6' , {3, 2}},
    {'1' , {1, 3}},
    {'2' , {2, 3}},
    {'3' , {3, 3}},
    {'0' , {2, 4}},
    {'A' , {3, 4}}
};

map<char, array<ll, 2>> movePos = {
    {'^' , {2, 1}},
    {'A' , {3, 1}},
    {'<' , {1, 2}},
    {'v' , {2, 2}},
    {'>' , {3, 2}}
};

vector<string> getAllPaths(char s, char e, bool isNumpad) {
    vector<string> allPaths;
    set<char> visited;
    queue<pair<string, string>> q;
    q.push({string(1, s), {}});
    size_t minSize = INT64_MAX;
    while (!q.empty()) {
        auto [p, d] = q.front();
        q.pop();
        char c = p.back();
        if (c == e) {
            d.push_back('A');
            if (d.size() <= minSize) {
                allPaths.push_back(d);
                minSize = min(minSize, d.size());
            }
            continue;
        }
        for (int i = 0; i < 4; ++i) {
            auto [dx, dy] = DIRS[i];
            char nc;
            if (isNumpad) {
                nc = gridNums[numPos[c][1]+dy][numPos[c][0]+dx];
            } else {
                nc = gridDirs[movePos[c][1]+dy][movePos[c][0]+dx];
            }
            if (nc == '#' || find(p.begin(), p.end(), nc) != p.end()) {
                continue;
            }
            //cout << c << " from using: " << getCharFromDir[i] << " to " << nc << endl;
            //p.push_back(nc);
            //d.push_back(getCharFromDir[i]);
            string np = p + nc;
            string nd = d + getCharFromDir[i];
            q.push({np, nd});
        }
    }
    return allPaths;
}

unordered_map<string, ll> memo;

ll getMin(vector<string> path) {
    size_t minSize = INT64_MAX;
    for (string s : path) {
        minSize = min(minSize, s.size());
    }
    return minSize;
}

ll min_steps(int layer, const string& segment, bool first){
    auto key = to_string(layer) + ":" + segment;
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }

    ll s = 0;
    char c = 'A';
    for (const char& nc : segment) {
        vector<string> paths = getAllPaths(c, nc, first);
        if (layer == 0) {
            s += getMin(paths);
        } else {
            ll minSize = INT64_MAX;
            for (string p : paths) {
                minSize = min(minSize, min_steps(layer-1, p, false));
            }
            s += minSize;
        }
        c = nc;
    }

    memo[key] = s;
    return s;
}

int main() {
    ifstream inputFile("input.txt");
    string line;
    vector<int> nums;
    vector<string> codes;
    smatch match;
    regex pattern(R"((\d+)A)"); 
    while (getline(inputFile, line)) {
        codes.push_back(line);
        if (regex_search(line, match, pattern)) {
            ll num = stoll(match[1]);
            nums.push_back(num);
        }
    }
    ll s = 0;
    for (int i = 0; i < nums.size(); ++i) {
        s += nums[i] * min_steps(25, codes[i], true);
    }
    cout << s << endl;
    return 0;
}
