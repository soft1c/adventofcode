#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <cctype>

using namespace std;

int stringToDigit(const string& s) {
    static const unordered_map<string, int> stringDigits = {
        {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4},
        {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}
    };
    
    auto it = stringDigits.find(s);
    return it != stringDigits.end() ? it->second : -1;
}

int getFirstDigit(const string& line) {
    vector<int> wordLengths = {3, 4, 5}; // Lengths of digit words

    for (size_t i = 0; i < line.size(); ++i) {
        if (isdigit(line[i])) {
            return line[i] - '0';
        }
        for (int len : wordLengths) {
            if (i + len <= line.size()) {
                string word = line.substr(i, len);
                for (char &ch : word) ch = tolower(ch); // Convert to lowercase
                int digit = stringToDigit(word);
                if (digit != -1) {
                    return digit;
                }
            }
        }
    }
    return -1; // Return -1 if no digit found
}

int getLastDigit(const string& line) {
    vector<int> wordLengths = {3, 4, 5}; // Lengths of digit words

    for (size_t i = line.size(); i-- > 0;) {
        if (isdigit(line[i])) {
            return line[i] - '0';
        }
        for (int len : wordLengths) {
            if (i >= len - 1) {
                string word = line.substr(i - len + 1, len);
                for (char &ch : word) ch = tolower(ch); // Convert to lowercase
                int digit = stringToDigit(word);
                if (digit != -1) {
                    return digit;
                }
            }
        }
    }
    return -1; // Return -1 if no digit found
}

int main() {
    ifstream file("input.txt");
    string line;
    int sum = 0;

    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return 1;
    }

    while (getline(file, line)) {
        int firstDigit = getFirstDigit(line);
        int lastDigit = getLastDigit(line);

        if (firstDigit != -1 && lastDigit != -1) {
            cout << "Found digits: " << firstDigit << " and " << lastDigit << endl;
            sum += firstDigit * 10 + lastDigit;
        }
    }

    file.close();

    cout << "Sum of all two-digit numbers: " << sum << endl;

    return 0;
}
