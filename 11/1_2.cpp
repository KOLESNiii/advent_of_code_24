#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Memoization map
unordered_map<ll, vector<ll>> memo;

vector<ll> transform(ll nextStone) {
    // Check if result is already computed
    if (memo.find(nextStone) != memo.end()) {
        return memo[nextStone];
    }

    vector<ll> result;
    if (nextStone == 0) {
        result.push_back(1);
    } else if (to_string(nextStone).size() % 2 == 0) {
        int size = to_string(nextStone).size();
        ll p = pow(10, size / 2);
        ll left = nextStone / p;
        ll right = nextStone % p;
        result.push_back(left);
        result.push_back(right);
    } else {
        result.push_back(nextStone * 2024);
    }

    // Save the result in memoization map
    memo[nextStone] = result;
    return result;
}

int main() {
    ifstream inputFile("input.txt");
    queue<ll> currentLevel;
    ll a;

    // Read input into queue
    while (inputFile >> a) {
        currentLevel.push(a);
    }

    // Process 75 levels
    for (int i = 0; i < 75; ++i) {
        cout << "Level: " << i << endl;
        queue<ll> nextLevel;

        while (!currentLevel.empty()) {
            ll nextStone = currentLevel.front();
            currentLevel.pop();

            // Transform and push results to the next level
            vector<ll> results = transform(nextStone);
            for (ll res : results) {
                nextLevel.push(res);
            }
        }

        // Swap queues for the next iteration
        swap(currentLevel, nextLevel);
    }

    // Output the final size of the queue
    cout << "Final queue size: " << currentLevel.size() << endl;
    return 0;
}
