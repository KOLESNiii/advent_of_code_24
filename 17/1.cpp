#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ifstream inputFile("input.txt");
    array<ll, 3> registers;
    string line, temp;
    for (int i = 0; i < 3; ++i) {
        getline(inputFile, line);
        istringstream(line) >> temp >> temp >> registers[i];
    }
    getline(inputFile, line);

    getline(inputFile, line);
    istringstream iss(line.substr(line.find(':') + 1));
    string n;
    vector<int> instructions;
    while (getline(iss, n, ',')) {
        instructions.push_back(stoi(n));
    }
    queue<int> output;
    for (int i = 0; i < instructions.size(); i += 2) {
        int opcode = instructions[i];
        ll operand = instructions[i+1];
        if (opcode == 0 || opcode == 2 || opcode == 5 || opcode == 6 || opcode == 7) {
            if (operand >=4 && operand <= 6) {
                operand = registers[operand-4];
            }
        }
        if (opcode == 0) {
            registers[0] >>= operand;
        } else if (opcode == 1) {
            registers[1] ^= operand;
        } else if (opcode == 2) {
            registers[1] = operand % 8;
        } else if (opcode == 3) {
            if (registers[0]) i = operand - 2;
        } else if (opcode == 4) {
            registers[1] ^= registers[2];
        } else if (opcode == 5) {
            output.push(operand % 8);
        } else if (opcode == 6) {
            registers[1] = registers[0] >> operand;
        } else {
            registers[2] = registers[0] >> operand;
        }
    }
    cout << output.front();
    output.pop();
    while (!output.empty()) {
        cout << "," << output.front();
        output.pop();
    }
    return 0;
}