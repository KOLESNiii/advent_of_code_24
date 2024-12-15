#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll HEIGHT = 103;
ll WIDTH = 101;

struct Robot {
    ll x, y, vx, vy;
};

void simulate(vector<Robot>& robots, ll t) {
    for (auto& robot : robots) {
        robot.x += t * robot.vx;
        robot.x = robot.x % WIDTH;
        robot.y += t * robot.vy;
        robot.y = robot.y % HEIGHT;
        robot.x = (robot.x < 0) ? robot.x + WIDTH : robot.x;
        robot.y = (robot.y < 0) ? robot.y + HEIGHT : robot.y;
    }
}

pair<ll, ll> boundingBox(const vector<Robot>& robots) {
    ll minX = LLONG_MAX, maxX = LLONG_MIN;
    ll minY = LLONG_MAX, maxY = LLONG_MIN;

    for (const auto& robot : robots) {
        minX = min(minX, robot.x);
        maxX = max(maxX, robot.x);
        minY = min(minY, robot.y);
        maxY = max(maxY, robot.y);
    }

    ll width = maxX - minX + 1;
    ll height = maxY - minY + 1;
    return {width, height};
}

void saveGridToFile(const vector<Robot>& robots, ll time) {
    ll minX = LLONG_MAX, maxX = LLONG_MIN;
    ll minY = LLONG_MAX, maxY = LLONG_MIN;

    for (const auto& robot : robots) {
        minX = min(minX, robot.x);
        maxX = max(maxX, robot.x);
        minY = min(minY, robot.y);
        maxY = max(maxY, robot.y);
    }

    vector<string> grid(maxY - minY + 1, string(maxX - minX + 1, '.'));

    for (const auto& robot : robots) {
        grid[robot.y - minY][robot.x - minX] = '#';
    }

    string fileName = "output_grid" + to_string(time) + ".txt";
    ofstream outputFile(fileName);
    for (const auto& row : grid) {
        outputFile << row << "\n";
    }
    outputFile.close();

    cout << "Saved grid to " << fileName << endl;
}

int main() {
    ifstream inputFile("input.txt");
    string line;
    regex pattern(R"(p=(-?\d+),(-?\d+) v=(-?\d+),(-?\d+))");
    smatch match;

    vector<Robot> robots;

    while (getline(inputFile, line)) {
        if (regex_search(line, match, pattern)) {
            ll x = stoll(match[1]);
            ll y = stoll(match[2]);
            ll vx = stoll(match[3]);
            ll vy = stoll(match[4]);
            robots.push_back({x, y, vx, vy});
        }
    }
    unordered_set<ll> hs; 
    ll t = 0;
    bool found = false;
    while (!found) {
        for (Robot robot : robots) {
            hs.insert(robot.x+robot.y*WIDTH);
        }
        if (robots.size() - hs.size() == 0) {
            cout << t << endl;
            saveGridToFile(robots, t);
            found = true;
        } else {
            if (t % 100 == 0) {
                cout << t << endl;
            }
        }
        /*for (Robot robot : robots) {
            if (hs.count(robot.x+(robot.y+1)*WIDTH) != 0 && hs.count(robot.x+1+(robot.y+1)*WIDTH) != 0 && hs.count(robot.x-1+(robot.y+1)*WIDTH) != 0 && hs.count(robot.x+(robot.y+2)*WIDTH) != 0) {
                cout << t << endl;
                saveGridToFile(robots, t);
                found = true;
                break;
            }
        }*/
        hs.clear();
        simulate(robots, 1);
        t ++;
    }
    /*simulate(robots, 100);
    for (int i = 101; i <= 200; ++i) {
        simulate(robots, 1);
        saveGridToFile(robots, i);
    }*/

    return 0;
}
