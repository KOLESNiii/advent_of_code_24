#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ifstream inputFile("input.txt");
    char c;
    queue<int> q;
    deque<array<int, 3>> vals;
    vector<array<int, 2>> space;
    vector<int> disk;
    int id = 0;
    int index = 0;
    bool isFS = false;
    while (inputFile >> c) {
        int val = c - '0';
        if (isFS) {
            space.push_back({val, index});
            for (int i = 0; i < val; ++i) {
                disk.push_back(0);
            }
        } else {
            vals.push_front({val, index, id});
            for (int i = 0; i < val; ++i) {
                disk.push_back(id);
            }
            id++;
        }
        index += val;
        isFS = !isFS;
    }
    /*for (int i = 0; i < disk.size(); ++i) {
        cout << disk[i];
    }*/
    //cout << endl;
    for (auto [val, indexV, id] : vals) {
        int j = 0;
        for (auto [size, indexS] : space) {
            if (val <= size && indexS < indexV) {
                for (int i = 0; i < val; ++i) {
                    disk[indexV + i] = 0;
                    disk[indexS + i] = id;
                }
                space[j] = {size-val, indexS+val};
                break;
            }
            ++j;
        }
    }
    ll s = 0;
    for (int i = 0; i < disk.size(); ++i) {
        //cout << disk[i];
        s += i * disk[i];
    }
    cout << endl;
    cout << "Part 2: " << s << endl;
    return 0;
}