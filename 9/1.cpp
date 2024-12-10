#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ifstream inputFile("input.txt");
    vector<int> nums;
    char c;
    queue<int> q;
    deque<int> vals;
    deque<int> space;
    ll id = 0;
    bool isFS = false;
    while (inputFile >> c) {
        int val = c - '0';
        if (isFS) {
            space.push_back(val);
        } else {
            for(int i = 0; i < val; ++i) {
                vals.push_back(id);
            }
            id ++;
        }
        isFS = !isFS;
    }
    id = 0;
    cout << endl;
    while (!vals.empty()) {
        while (vals.front() == id && !vals.empty()) {
            vals.pop_front();
            nums.push_back(id);
        }
        id ++;
        int spaces = space.front();
        space.pop_front();
        for (int i = 0; i < spaces; ++i) {
            if (vals.empty()) {
                break;
            } 
            int lastElem = vals.back();
            //cout << lastElem << endl;
            vals.pop_back();
            nums.push_back(lastElem);
        }
    }
    ll s = 0;
    for (int i = 0; i < nums.size(); ++i) {
        s += i * nums[i];
    }
    cout << "Part 1: " << s << endl;
    return 0;
}