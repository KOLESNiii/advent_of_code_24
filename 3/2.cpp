#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    std::ifstream inputFile("input.txt");
    string line;
    ll s = 0;
    regex mulRegex("((do\\(\\)|don't\\(\\))|mul\\((\\d+),(\\d+)\\))");
    smatch match;
    bool isEnabled = true;
    while(getline(inputFile, line)) {
        auto begin = sregex_iterator(line.begin(), line.end(), mulRegex);
        auto end = sregex_iterator();
        for (auto it = begin; it != end; ++it) {
            if ((*it)[1].matched) {
                if ((*it)[1] == "do()") {
                    isEnabled = true;
                } else if ((*it)[1] == "don't()") {
                    isEnabled = false;
                }
            } else if ((*it)[2].matched && (*it)[3].matched) {
                if (isEnabled) {
                    ll a = stoll((*it)[2].str());
                    ll b = stoll((*it)[3].str());
                    s += a * b;
                }
            }
        }

    }
    inputFile.close();
    cout << s;
    return 0;
}