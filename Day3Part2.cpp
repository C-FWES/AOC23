//
// Created by Wesley Ou on 2023-12-03.
//
#include <iostream>
#include <string>
#include <numeric>
#include <set>
using namespace std;

int main() {
    // read input to a 2d array
    vector<string> grid;
    string line;
    while (getline(cin, line)) {
        if (line == "stop") { break; }
        grid.push_back(line);
    }

    vector<int> partNums;
    vector<int> gearRatios;
    set<int> usedNums;

    int rows = grid.size();
    int cols = grid[0].size();
    int gearRatioSum;

    vector<vector<bool>> visited(rows, vector<bool>(cols, false));

    int directions[8][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, -1}, {1, 1}};

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // check if cell has a symbol
            if (grid[i][j] == '*') {

                vector<int> adjacentToGear;

                for (const auto& dir: directions) {
                    int nextX;
                    int nextY;

                    nextX = i + dir[0];
                    nextY = j + dir[1];

                    // check if adjacent is a digit
                    if (isdigit(grid[nextX][nextY]) && !visited[nextX][nextY]) {
                        string fullNumber = to_string(grid[nextX][nextY] - '0');
                        visited[nextX][nextY] = true;
                        // check left and right to obtain whole number
                        int countL = 1;
                        while (isdigit(grid[nextX][nextY - countL])) { // left is num
                            if (!visited[nextX][nextY - countL]) {
                                fullNumber = to_string(grid[nextX][nextY - countL] - '0') + "" + fullNumber;
                                visited[nextX][nextY - countL] = true;
                                ++countL;
                            }
                        }
                        int countR = 1;
                        while (isdigit(grid[nextX][nextY + countR])) { // right is num
                            if (!visited[nextX][nextY + countR]) {
                                fullNumber += to_string(grid[nextX][nextY + countR] - '0');
                                visited[nextX][nextY + countR] = true;
                                ++countR;
                            }
                        }

                        adjacentToGear.push_back(stoi(fullNumber));
                        partNums.push_back(stoi(fullNumber));
                    }
                }

                if (adjacentToGear.size() == 2) {
                    int product = adjacentToGear[0] * adjacentToGear[1];
                    gearRatioSum += product;
                }
            }
        }
    }

    cout << gearRatioSum;

    return 0;
}
