#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

bool isSafe(vector<ll> nums) {
    ll a;
    a = nums[0];
    int increasing = 0;
    bool invalid = false;
    for (ll b : vector<ll>(nums.begin()+1, nums.end())) {
        if (abs(a-b) < 1 || abs(a-b) > 3) {
            invalid = true;
            break;
        } else {
            if (increasing == 0) {
                if (a-b > 0) {
                    increasing = -1;
                } else {
                    increasing = 1;
                }
            } else if (increasing == 1) {
                if (a-b > 0) {
                    invalid = true;
                    break;
                }
            } else if (increasing == -1) {
                if (b-a > 0) {
                    invalid = true;
                    break;
                }
            }
        }
        a = b;
    }
    return !invalid;
}

int main() {
    std::ifstream inputFile("input.txt");
    string line;
    ll s = 0;
    while(getline(inputFile, line)) {
        istringstream report(line);
        vector<ll> nums;
        ll a;
        bool invalid = true;
        while (report >> a) {
            nums.push_back(a);
        }
        vector<vector<ll>> nnums;
        for (int i = 0; i < nums.size(); i++) {
            vector<ll> temp;
            for (int j = 0; j < nums.size(); j++) {
                if (j != i) {
                    temp.push_back(nums[j]);
                }
            }
            nnums.push_back(temp);
        }
        for (vector<ll> numss : nnums) {
            if (isSafe(numss)) {
                invalid = false;
                break;
            }
        }
        if (!invalid) {
            s ++;
        }
    }
    inputFile.close();
    cout << s;
    return 0;
}