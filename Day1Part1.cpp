//
// Created by Wesley Ou on 2023-12-01.
//
#include <iostream>
#include <vector>
#include <numeric>
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
    vector<int> calibrationValues;
    for (auto & code : codes) {
        vector<int> foundDigits;
        for (char j : code) {
            if (isdigit(j)) {
                // only use first and last digits
                if (foundDigits.size() == 2) {
                    foundDigits.pop_back();
                }
                int digit = j - '0';
                foundDigits.push_back(digit);
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
