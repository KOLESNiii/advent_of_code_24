#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    std::ifstream inputFile("input.txt");
    string line;
    ll s = 0;
    regex mulRegex("(mul\\((\\d+),(\\d+)\\))");
    smatch match;
    while(getline(inputFile, line)) {
        auto begin = sregex_iterator(line.begin(), line.end(), mulRegex);
        auto end = sregex_iterator();
        for (auto it = begin; it != end; ++it) {
            ll a = stoll((*it)[1].str());
            ll b = stoll((*it)[2].str());
            s += a * b;
        }
    }
    inputFile.close();
    cout << s;
    return 0;
}