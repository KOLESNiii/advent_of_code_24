#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

int main() {
    std::ifstream inputFile("input.txt");
    string line;
    ll s = 0;
    while(getline(inputFile, line)) {
        istringstream report(line);
        ll a, b;
        report >> a;
        int increasing = 0;
        bool invalid = false;
        while (report >> b) {
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
        if (! invalid) {
            s ++;
        }
    }
    inputFile.close();
    cout << s;
    return 0;
}