#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <tuple>
#include <stdlib.h>
#include <ctime>

#include "json.hpp"

using json = nlohmann::json;
using namespace std;

json j;
string currentRoom;
int roomIndex;

// Items the player currently has (inventory)
vector<string> items;
// Items in the current state of the game. E.g. if an item is picked up, it is removed from roomItems
// roomItems[0] is a vector of the items contained in the first room etc.
vector<vector<string>> roomItems;
// Maps the rooms of enemies to their index in j["enemies"]
// E.g. for map1.json, enemies["room2"] = 0 as the enemy in room2 is the first enemey in j["enemy"]
map<string, int> enemies;
// Stores the state of a game so that it can be loaded again
// I.e. savedGames = ["nameOfSave" : (items, roomItems, enemies, currentRoom)]
map<string, tuple<vector<string>, vector<vector<string>>, map<string, int>, string>> savedGames;

// Finds index of room in .json file for easier referencing.
// E.g. in map1.json, findRoomIndex("room1") would return 0 as it is the first room in j["rooms"].
int findRoomIndex(string roomNum) {
  for (int i = 0; i < j["rooms"].size(); i++)
    if (j["rooms"][i]["id"] == roomNum)
      return i;
  return -1;
}

// Prints the info of the room. E.g. description, items, enemies
void showRoomInfo() {
  roomIndex = findRoomIndex(currentRoom);
  cout << j["rooms"][roomIndex]["desc"] << endl;
  for (string item : roomItems[roomIndex]) {
    cout << "There is a " << item << "." << endl;
  }
  if (enemies.count(currentRoom) == 1) {
    cout << "There is a " << j["enemies"][enemies[currentRoom]]["id"] << " in the room with you." << endl;
  }
}

// Check if the user has the items to kill an enemy
bool checkItems() {
  for (string requiredItem : j["enemies"][enemies[currentRoom]]["killedby"]) {
    if (find(items.begin(), items.end(), requiredItem) == items.end())
      return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  ifstream fin(argv[1]);
  fin >> j;

  currentRoom = j["player"]["initialroom"];

  bool entered = true, enemyRoom = false;

  // Init room items
  for (int i = 0; i < j["rooms"].size(); i++) {
    roomItems.push_back(j["rooms"][i]["obj"]);
  }
  // Init enemies
  for (int i = 0; i < j["enemies"].size(); i++) {
    enemies[j["enemies"][i]["initialroom"]] = i;
  }

  srand(time(0));

  string input;
  while (input != "q") {

    // Checks if player has just entered the room. I.e. a room init
    if (entered) {
      showRoomInfo();
      entered = false;
    }

    if (enemies.count(currentRoom) == 1)
      enemyRoom = true;
    else
      enemyRoom = false;

    getline(cin, input);

    // Player can always look around, check inventory or attempt to kill something whether there are enemies in the room or not.
    // I.e. these commands can happen without the chance of death being calculated
    if (input == "look")
      showRoomInfo();
    else if (input == "list items") {
      cout << "Inventory: " << endl;
      for (string item : items)
        cout << item << endl;
    }
    else if (input.substr(0, input.find(" ")) == "kill") { // Kill ___
      string enemy = input.substr(input.find(" ") + 1);
      if (enemies.count(currentRoom) >= 1 && j["enemies"][enemies[currentRoom]]["initialroom"] == currentRoom && j["enemies"][enemies[currentRoom]]["id"] == enemy) {
        if (checkItems()) {
          cout << "You killed the " << enemy << "." << endl;
          enemies.erase(currentRoom);
          if (enemies.size() == 0) {
            cout << "Congratulations! You killed all of the enemies." << endl;
            return (0);
          }
        }
        else {
          cout << "You dont have the items to do that, so the " << enemy << " killed you." << endl;
          return (0);
        }
      }
      else
        cout << "There is not a " << enemy << " in this room." << endl;
    }
    else if (input.substr(0, input.find(" ")) == "save") { // Save ___
      string saveName = input.substr(input.find(" ") + 1);
      savedGames[saveName] = make_tuple(items, roomItems, enemies, currentRoom);
      cout << "Game saved as " << saveName << endl;
    }
    else if (input.substr(0, input.find(" ")) == "load") { // Load ___
      string loadName = input.substr(input.find(" ") + 1);
      if (savedGames.count(loadName)) {
        cout << "Save file " << loadName << " has been loaded." << endl;
        items = get<0>(savedGames[loadName]);
        roomItems = get<1>(savedGames[loadName]);
        enemies = get<2>(savedGames[loadName]);
        currentRoom = get<3>(savedGames[loadName]);
        roomIndex = findRoomIndex(currentRoom);
      }
      else
        cout << "No save file named " << loadName << " found." << endl;
    }
    else {
      // Calculate chance to see if user died
      // If they survived, continue with the other if statements
      if (enemyRoom) {
        bool chance = (rand() % 2) == 0;
        if (chance) {
          cout << "You were killed while trying to " << input << "." << endl;
          return (0);
        }
      }

      // Movement statements
      if (input == "go east") { // go east
        if (j["rooms"][roomIndex]["e"] == "")
          cout << "Can't go that way." << endl;
        else {
          currentRoom = j["rooms"][roomIndex]["e"];
          entered = true;
        }
      }
      else if (input == "go west") { // go west
        if (j["rooms"][roomIndex]["w"] == "")
          cout << "Can't go that way." << endl;
        else {
          currentRoom = j["rooms"][roomIndex]["w"];
          entered = true;
        }
      }
      else if (input == "go north") { // go north
        if (j["rooms"][roomIndex]["n"] == "")
          cout << "Can't go that way." << endl;
        else {
          currentRoom = j["rooms"][roomIndex]["n"];
          entered = true;
        }
      }
      else if (input == "go south") { // go south
        if (j["rooms"][roomIndex]["s"] == "")
          cout << "Can't go that way." << endl;
        else {
          currentRoom = j["rooms"][roomIndex]["s"];
          entered = true;
        }
      }
      else if (input.substr(0, input.find(" ")) == "take") { // Take ___
        string item = input.substr(input.find(" ") + 1);
        // If item exists (is available/not a spelling error), add it to inventory
        if (find(roomItems[roomIndex].begin(), roomItems[roomIndex].end(), item) != roomItems[roomIndex].end()) {
          roomItems[roomIndex].erase(find(roomItems[roomIndex].begin(), roomItems[roomIndex].end(), item));
          items.push_back(item);
          cout << "You took the " << item << "." << endl;
        }
        else
          cout << "There isn't a " << item << " in the room." << endl;
      }
      else
        cout << "Command unknown." << endl;
    }
  }
}