#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;



long long int extractNumber(const vector<string>& grid, int i, int& j) {
    
    while (j >= 0 && isdigit(grid[i][j])) {
        j--;
    }
    j++;
    
    string numStr = "";
    // Izračunaj vrijednost broja
    while (j < grid[i].size() && isdigit(grid[i][j])) {
        numStr += grid[i][j];
        j++;
    }
    cout<<"broj "<<numStr<<" ";
    return numStr.empty() ? 0 : stoi(numStr);
}
int findProductOfTwoNumbers(const vector<string>& grid, int i, int j) {
    vector<string> localGrid(3, string(3, '.'));
    for (int di = -1; di <= 1; ++di) {
        for (int dj = -1; dj <= 1; ++dj) {
            int ni = i + di, nj = j + dj;
            if (ni >= 0 && ni < grid.size() && nj >= 0 && nj < grid[ni].size()) {
                localGrid[di + 1][dj + 1] = grid[ni][nj];
            }
        }
    }

    vector<int> numbers;

    for (int di = -1; di <= 1; ++di) {
        for (int dj = -1; dj <= 1; ++dj) {
            if (di == 0 && dj == 0) continue; // Preskačemo sam simbol *
            int ni = i + di, nj = j + dj;
            if (ni >= 0 && ni < grid.size() && nj >= 0 && nj < grid[ni].size() && isdigit(grid[ni][nj]) && localGrid[di + 1][dj + 1] != '.') {
                int num = extractNumber(grid, ni, nj);

                // Prekrivanje broja u lokalnoj kopiji
                int localI = di + 1, localJ = dj + 1;
                while (localJ >= 0 && localJ < 3 && isdigit(localGrid[localI][localJ])) {
                    localGrid[localI][localJ] = '.';
                    localJ++;
                }

                numbers.push_back(num);
                if (numbers.size() == 2) {
                    break;
                }
            }
        }
        if (numbers.size() == 2) {
            break;
        }
    }

    if (numbers.size() == 2) {
        return numbers[0] * numbers[1];
    }

    return 0;
}


int main() {
    ifstream file("input.txt");
    vector<string> grid;
    string line;

    while (getline(file, line)) {
        grid.push_back(line);
    }

    long long int sum = 0;

    for (int i = 0; i < grid.size(); ++i) {
        for (int j = 0; j < grid[i].size(); ++j) {
            if (grid[i][j] == '*') {
                cout<<endl<<i<<" "<<j;
                sum += findProductOfTwoNumbers(grid, i, j);
            }
        }
    }

    cout << "Suma proizvoda dva broja za svaki * simbol: " << sum << endl;
    return 0;
}
