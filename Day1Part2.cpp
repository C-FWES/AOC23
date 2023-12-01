//
// Created by Wesley Ou on 2023-12-01.
//
#include <iostream>
#include <vector>
#include <numeric>
#include <map>
using namespace std;

int main() {
    vector<string> codes;
    string line;
    // read input
    while(getline(cin, line)) {
        if (line == "stop") {
            break;
        }
        codes.push_back(line);
    }

    // define text number to digit number connection

    map<string, int> numberMap;
    numberMap.insert(pair<string, int>("one", 1));
    numberMap.insert(pair<string, int>("two", 2));
    numberMap.insert(pair<string, int>("three", 3));
    numberMap.insert(pair<string, int>("four", 4));
    numberMap.insert(pair<string, int>("five", 5));
    numberMap.insert(pair<string, int>("six", 6));
    numberMap.insert(pair<string, int>("seven", 7));
    numberMap.insert(pair<string, int>("eight", 8));
    numberMap.insert(pair<string, int>("nine", 9));

    vector<int> calibrationValues;
    for (auto & code : codes) {
        vector<int> foundDigits;
        for (int j = 0; j < code.size(); ++j) {
            if (isdigit(code[j])) {
                // only use first and last digits
                if (foundDigits.size() == 2) {
                    foundDigits.pop_back();
                }
                int digit = code[j] - '0';
                foundDigits.push_back(digit);
            }
            // is alpha
            else if (isalpha(code[j])) {
                string word(1, tolower(code[j]));
                int count = j;
                while (isalpha(code[count] )) {
                    if (numberMap[word]) {
                        if (foundDigits.size() == 2) {
                            foundDigits.pop_back();
                        }
                        foundDigits.push_back(numberMap[word]);
                        break;
                    }
                    ++count;
                    word += tolower(code[count]);
                }
            }
        }
        // concatenate numbers
        if (foundDigits.size() == 1) { calibrationValues.push_back(foundDigits[0] * 10 + foundDigits[0]); }
        else { calibrationValues.push_back(foundDigits[0] * 10 + foundDigits[1]); }
    }

    // output sums
    cout << accumulate(calibrationValues.begin(), calibrationValues.end(), 0);
    return 0;
}
