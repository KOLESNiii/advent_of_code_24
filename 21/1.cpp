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

int getAdjacencyScore(const string &ss) {
    int s = 0;
    for (size_t i = 1; i < ss.size(); ++i) {
        if (ss[i] == ss[i - 1]) {
            ++s;
        }
    }
    return s;
}

int getQualityScore(const string &ss) {
    int s = 0;
    for (char c : ss) {
        if (c == '^' || c == '>' || c == 'A') {
            s++;
        } else if (c == 'v') {
            s += 2;
        } else {
            s += 3;
        }
    }
    return s;
}

bool isSmaller(const string &sa, const string &sb) {
    for (size_t i = 0; i < sa.size(); ++i) {
        switch (sa[i]) {
            case '<':
                if (sb[i] != '<') return true;
                break;
            case 'v':
                if (sb[i] == '<') return false;
                if (sb[i] != 'v') return true;
                break;
            default:
                if (sb[i] == '<' || sb[i] == 'v') return false;
                break;
        }
    }
    return false;
}

bool isBetter(const string &sa, const string &sb) {
    int scoreA = getAdjacencyScore(sa), scoreB = getAdjacencyScore(sb);
    if (scoreA > scoreB) return true;
    if (scoreA == scoreB) {
        int qualityA = getQualityScore(sa), qualityB = getQualityScore(sb);
        if (qualityA < qualityB) return true;
        if (qualityA == qualityB) return isSmaller(sa, sb);
    }
    return false;
}

ll getMinSize(string code) {
    unordered_map<char, string> m;
    for (int i = 0; i < 3; ++i) {
        cout << i << endl;
        bool isNumPad = (i == 0);
        char c = 'A';
        string ss = "";

        for (char nc : code) {
            string bs = "";
            if (isNumPad || !m.count(nc)) {
                vector<string> suffixes = getAllPaths(c, nc, isNumPad);
                for (const string &suffix : suffixes) {
                    if (bs.empty() || suffix.size() < bs.size() || (suffix.size() == bs.size() && isBetter(suffix, bs))) {
                        bs = suffix;
                    }
                }
                m[nc] = bs;
            } else {
                bs = m[nc];
            }
            ss += bs;
            c = nc;
        }
        code = ss;
    }
    return code.size();
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
        s += nums[i] * getMinSize(codes[i]);
    }
    cout << s << endl;
    return 0;
}
