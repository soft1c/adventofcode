#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <algorithm>

using namespace std;

map<string, int> processDraw(const string& drawStr) {
    map<string, int> draw;
    stringstream ss(drawStr);
    string token;
    while (getline(ss, token, ',')) {
        stringstream tokenStream(token);
        int count;
        string color;
        tokenStream >> count >> color;
        draw[color] += count;
    }
    return draw;
}

int main() {
    ifstream file("input.txt");
    string line;
    int totalStrength = 0;
    
    while (getline(file, line)) {
        stringstream lineStream(line);
        string part;
        map<string, int> maxCubes = {{"red", 0}, {"green", 0}, {"blue", 0}};
        
        getline(lineStream, part, ':'); // Skip the game ID

        while (getline(lineStream, part, ';')) {
            map<string, int> draw = processDraw(part);
            for (const auto& pair : draw) {
                maxCubes[pair.first] = max(maxCubes[pair.first], pair.second);
            }
        }

        int strength = maxCubes["red"] * maxCubes["green"] * maxCubes["blue"];
        totalStrength += strength;
    }

    cout << "Total strength of all games: " << totalStrength << endl;
    return 0;
}
