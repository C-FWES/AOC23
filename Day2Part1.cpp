//
// Created by Wesley Ou on 2023-12-02.
//
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <set>
using namespace std;

class GameSet {
   public:
       int gameId;
       int numRed;
       int numGreen;
       int numBlue;
};

int main() {
   // read input
   vector<string> gamesList;
   string line;
   while (getline(cin, line)) {
       if (line == "stop") {
           break;
       }
       gamesList.push_back(line);
   }

   // process input and assign values to class GameSet
   vector<vector<GameSet>> games;
   for (const auto& currGame : gamesList) {
       vector<GameSet> gameSets;

       // get id
       int gameId = stoi(currGame.substr(5, currGame.find(":") - 5));

       size_t pos = currGame.find(":") + 2;
       string sets = currGame.substr(pos);

       stringstream ss(sets);
       string set;
       while (getline(ss, set, ';')) {
           GameSet gameSet{};
           gameSet.gameId = gameId;
           stringstream setStream(set);

           // extract number and color
           while (setStream >> ws) {
               int num;
               string color;

               if (setStream >> num >> color) {
                   if (color == "red" || color == "red,") { gameSet.numRed = num; }
                   else if (color == "green" || color == "green,") { gameSet.numGreen = num; }
                   else if (color == "blue" || color == "blue,") { gameSet.numBlue = num; }
               }
           }
           gameSets.push_back(gameSet);
       }
       games.push_back(gameSets);
   }

   int redLim = 12;
   int greenLim = 13;
   int blueLim = 14;

   int sum = 0;

   set<int> usedIds;

   for (const auto& currSets : games) {
       int count = 0;
       int currId = -1;
       for (auto set: currSets) {
           currId = set.gameId;
           if (set.numRed <= redLim && set.numGreen <= greenLim && set.numBlue <= blueLim) {
               ++count;
           }
       }
       if (count == currSets.size()) { sum += currId; }
       count = 0;
       currId = -1;
   }

   cout << sum;

   return 0;
}
