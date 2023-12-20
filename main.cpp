#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

bool isSymbol(char ch) {
    return ch != '.' && !isdigit(ch);
}

int extractNumber(const vector<string>& grid, vector<vector<bool>>& visited,int i, int j) {
    string numStr = "";
    while (j >= 0 && isdigit(grid[i][j])) {
        j--;
    }
    j++;
    while(isdigit(grid[i][j])){
        visited[i][j]=true;
        numStr+=grid[i][j++];
    }
    cout<<numStr<<" ";
    return numStr.empty() ? 0 : stoi(numStr);
}

int main() {
    ifstream file("input.txt");
    vector<string> grid;
    string line;

    while (getline(file, line)) {
        grid.push_back(line);
    }

    int sum = 0;
    vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (isSymbol(grid[i][j])) {
                for (int di = -1; di <= 1; ++di) {
                    for (int dj = -1; dj <= 1; ++dj) {
                        int ni = i + di, nj = j + dj;
                        if (ni >= 0 && ni < grid.size() && nj >= 0 && nj < grid[ni].size() && isdigit(grid[ni][nj]) && !visited[ni][nj]) {
                            sum += extractNumber(grid,visited, ni, nj);
                            
                        }
                    }
                }
            }
        }
    }

    cout << "Suma: " << sum << endl;
    return 0;
}
