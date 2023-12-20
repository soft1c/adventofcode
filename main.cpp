#include <iostream>
#include <fstream>
#include <set>
#include <cmath>
#include <string>

using namespace std;

int main() {
    ifstream file("input.txt");
    string line;
    int totalScore = 0;

    while (getline(file, line)) {
        // Preskakanje riječi "Card" i broja karte
        size_t pos = line.find(':');
        if (pos == string::npos) continue; // Ako nema ':' u liniji, preskoči liniju

        // Razdvajanje dijelova linije
        string winningPart = line.substr(pos + 1, line.find('|') - pos - 1);
        string cardPart = line.substr(line.find('|') + 1);

        set<int> winningNumbers;
        int number;
        size_t last = 0, next = 0;

        // Čitamo winning brojeve
        while ((next = winningPart.find(' ', last)) != string::npos) {
            string numStr = winningPart.substr(last, next - last);
            if (!numStr.empty()) {
                number = stoi(numStr);
                winningNumbers.insert(number);
            }
            last = next + 1;
        }
        if (!winningPart.substr(last).empty()) {
            number = stoi(winningPart.substr(last));
            winningNumbers.insert(number);
        }

        // Brojimo winning brojeve na kartici
        int matchingNumbers = 0;
        last = 0, next = 0;
        while ((next = cardPart.find(' ', last)) != string::npos) {
            string numStr = cardPart.substr(last, next - last);
            if (!numStr.empty() && winningNumbers.count(stoi(numStr)) > 0) {
                cout<<"nasao: "<<numStr<<" ";
                matchingNumbers++;
            }
            last = next + 1;
        }
        if (!cardPart.substr(last).empty() && winningNumbers.count(stoi(cardPart.substr(last))) > 0) {
            matchingNumbers++;
        }

        // Izračunavamo bodove za karticu
        if (matchingNumbers > 0) {
            cout<<matchingNumbers<<endl;
            totalScore += pow(2, matchingNumbers - 1);
        }
    }

    cout << "Ukupan broj bodova: " << totalScore << endl;

    return 0;
}
