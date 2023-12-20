#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

using namespace std;

bool isValidDraw(const map<string, int>& draw, const map<string, int>& initialCubes) {
    for (const auto& pair : draw) {
        if (pair.second > initialCubes.at(pair.first)) {
            return false;
        }
    }
    return true;
}

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
    int validGamesSum = 0;
    
    map<string, int> initialCubes = {{"red", 12}, {"green", 13}, {"blue", 14}};

    while (getline(file, line)) {
        stringstream lineStream(line);
        string part;
        int gameId;
        lineStream >> part; // Read "Game"
        lineStream >> gameId; // Read game ID

        bool isValidGame = true;
        getline(lineStream, part, ':'); // Skip to the draw details
        while (getline(lineStream, part, ';')) {
            map<string, int> draw = processDraw(part);
            if (!isValidDraw(draw, initialCubes)) {
                isValidGame = false;
                break;
            }
        }

        if (isValidGame) {
            std::cout<<gameId<<std::endl;
            validGamesSum += gameId;
        }
    }

    cout << "Sum of valid game IDs: " << validGamesSum << endl;
    return 0;
}

