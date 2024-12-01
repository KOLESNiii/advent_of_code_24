#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    std::ifstream inputFile("input.txt");
    if (!inputFile.is_open()) {
        std::cerr << "Error: Could not open file." << std::endl;
        return 1;
    }
    vector<ll> list1;
    vector<ll> list2;
    string line;
    ll a, b;
    while(getline(inputFile, line)) {
        sscanf(line.c_str(), "%lld   %lld", &a, &b);
        list1.push_back(a);
        list2.push_back(b);
    }
    inputFile.close();

    sort(list1.begin(), list1.end());
    sort(list2.begin(), list2.end());

    ll d = 0;
    ll s = 0;
    for (int i = 0; i < list1.size(); ++i) {
        d += abs(list1[i] - list2[i]);
        s += list1[i] * count(list2.begin(), list2.end(), list1[i]);;
    }
    cout << d << endl << s;
    return 0;
}