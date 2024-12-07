#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool isTrue(vector<ll> nums, ll val, ll rollingVal=0, bool doConcat=false) {
    if (rollingVal == val && nums.size() == 0) {
        return true;
    } else if (rollingVal > val || nums.size() == 0) {
        return false;
    }
    ll multRollingVal = (rollingVal == 0) ? 1 : rollingVal;
    ll nextVal = nums.back();
    ll concat = stoll(to_string(rollingVal) + to_string(nextVal));
    nums.pop_back();
    return isTrue(nums, val, rollingVal + nextVal, doConcat) || isTrue(nums, val, multRollingVal * nextVal, doConcat) || (doConcat && isTrue(nums, val, concat, doConcat));
}

int main() {
    ifstream inputFile("input.txt");
    string line;
    vector<vector<ll>> grid;
    vector<ll> nums;
    while (getline(inputFile, line)) {
        vector<ll> temp;
        istringstream iss(line);
        string tk;
        getline(iss, tk, ':');
        nums.push_back(stoll(tk));
        getline(iss, tk, ':');
        istringstream iss2(tk);
        ll a;
        while (iss2 >> a) {
            temp.push_back(a);
        }
        reverse(temp.begin(), temp.end());
        grid.push_back(temp);
    }
    ll s = 0;
    ll q = 0;
    for (int i = 0; i < grid.size(); ++i) {
        if (isTrue(grid[i], nums[i])) {
            s += nums[i];
        }
        if (isTrue(grid[i], nums[i], 0, true)) {
            q += nums[i];
        }
    }

    cout << "Part 1: " << s << " Part 2: " << q << endl;
    return 0;
}