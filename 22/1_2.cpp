#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct ArrayHash {
    size_t operator()(const array<ll, 4>& arr) const {
        size_t seed = 0;
        for (ll val : arr) {
            seed ^= hash<ll>{}(val) + 0x9e3778b9 + (seed << 6) + (seed >> 2); 
        }
        return seed;
    }
};

unordered_map<array<ll, 4>, vector<ll>, ArrayHash> mi;

int main() {
    ifstream inputFile("input.txt");
    vector<ll> nums;
    ll a;
    while (inputFile >> a) {
        nums.push_back(a);
    }
    ll s = 0;
    for (int j = 0; j < nums.size(); ++j) {
        ll sn = nums[j];
        ll prev = sn;
        deque<ll> q; 
        set<array<ll, 4>> found;
        for (int i = 0; i < 2000; ++i) {
            ll temp;
            sn ^= sn << 6;
            sn %= 16777216;
            sn ^= sn >> 5;
            sn %= 16777216;
            sn ^= sn << 11;
            sn %= 16777216;
            if (i != 0) {
                ll d = (sn%10) - (prev%10);
                q.push_back(d);
                if (q.size() == 4) {
                    array<ll, 4> key = {q[0], q[1], q[2], q[3]};
                    //cout << q[0] <<", " << q[1] << ", " << q[2] << ", " << q[3] << endl;
                    //cout << (sn%10) << endl;
                    if (!found.count(key)) {
                        mi[key].push_back((sn%10));
                        found.insert(key);
                    }
                    q.pop_front();
                }
            }
            prev = sn;
        }
        s += sn;
    }
    ll maxCount = 0;
    for (const auto& [key, pairs] : mi) {
        ll sum = 0;
        for (const auto& v : pairs) {
            sum += v;
        }
        //cout << maxCount << ", " << sum << endl;
        maxCount = max(maxCount, sum);
    }
    cout << "Part 1: " << s << "\nPart 2: " << maxCount;
    return 0;
}
