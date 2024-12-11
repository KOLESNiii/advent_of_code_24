#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

pair<ll, ll> splitNumber(ll number) {
    string numStr = to_string(number);
    int mid = numStr.size() / 2;
    ll left = stoll(numStr.substr(0, mid));
    ll right = stoll(numStr.substr(mid));
    return {left, right};
}

ll countStones(vector<ll> stones, int numIts) {
    unordered_map<ll, ll> currentStones;
    for (ll stone : stones) {
        currentStones[stone] = 1;
    }
    for (int i = 0; i < numIts; ++i) {
        unordered_map<ll, ll> nextStones;
        for (auto [stone, n] : currentStones) {
            if (stone == 0) {
                nextStones[1] += n;
            } else {
                if (to_string(stone).size() % 2 == 0) {
                    auto [left, right] = splitNumber(stone);
                    nextStones[left] += n;
                    nextStones[right] += n;
                } else {
                    nextStones[stone * 2024] += n;
                }
            }
        }
        currentStones = move(nextStones);
    }
    ll s = 0;
    for (auto [stone, count] : currentStones) {
        s += count;
    }
    return s;
}

int main() {
    ifstream inputFile("input.txt");
    ll a;
    vector<ll> initialStones;
    while (inputFile >> a) {
        initialStones.push_back(a);
    }
    ll result1 = countStones(initialStones, 25);
    ll result2 = countStones(initialStones, 75);

    cout << "Part 1: " << result1 << "\nPart 2: " << result2 << endl;
    return 0;
}