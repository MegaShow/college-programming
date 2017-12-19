#include "map.hpp"
#include "global.hpp"
#include <iostream>
#include <list>
#include <algorithm>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

class InvalidInputException {
 public:
  InvalidInputException() { cerr << "Invalid input!" << endl; }
};
class DuplicateInputException : public InvalidInputException {
 public:
  DuplicateInputException() { cerr << "Duplicate input!" << endl; }
};

class GameUI {
 private:
  map* world;
  point initial_size;
  point initial_head;
  std::list<point> initial_foods;

 public:
  GameUI() {
    cout << "please input two positive integers indicates the map size!"
         << endl;
    cin >> initial_size.x >> initial_size.y;
    if (initial_size.x <= 5 || initial_size.y <= 5 || initial_size.x > 15 ||
        initial_size.y > 15) {
      cout << "invalid input" << endl;
      throw InvalidInputException();
    }
    cout << "please input two positive integers(range(0, size_x-1), "
            "range(0,size_y-1)) the initialize snake head position!"
         << endl;
    cin >> initial_head.x >> initial_head.y;
    if (initial_head.x >= initial_size.x || initial_head.x < 0 ||
        initial_head.y >= initial_size.y || initial_head.y < 0) {
      cout << "invalid input" << endl;
      throw InvalidInputException();
    }
    int food_num;
    cout << "please input how many food you will put and then input food "
            "position which is different form each other"
         << endl;
    cin >> food_num;

    if (food_num <= 0) {
      throw InvalidInputException();
    }

    while (food_num > 0) {
      food_num--;
      point temp;
      cin >> temp.x >> temp.y;
      if (temp.x >= 0 && temp.x < initial_size.x && temp.y >= 0 &&
          temp.y < initial_size.y &&
          std::find(initial_foods.begin(), initial_foods.end(), temp) ==
              initial_foods.end() &&
          !(temp.x == initial_head.x && temp.y == initial_head.y)) {
        initial_foods.push_back(temp);
      } else {
        throw DuplicateInputException();
      }
    }

    world = new map(initial_size, initial_head, initial_foods);
  }

  ~GameUI() { delete world; }

  void GameLoop() {
    world->print();
    bool exit = false;
    while (true) {
      char operation = getInput();
      switch (operation) {
        case 'w':
        case 'W':
          this->world->move(up);
          break;
        case 's':
        case 'S':
          this->world->move(down);
          break;
        case 'a':
        case 'A':
          this->world->move(left);
          break;
        case 'd':
        case 'D':
          this->world->move(right);
          break;
        case 'q':
        case 'Q':
          exit = true;
          break;
        default:
          this->world->move(freeze);
      }
      world->print();
      if (world->isGameOver()) {
        cout << "Game Over!" << endl;
        break;
      }
      if (exit) {
        cout << "Bye!" << endl;
        break;
      }
    }
  }

  char getInput() {
    char temp;
    cin >> temp;
    return temp;
  }
};

int main() {
  GameUI greedySnake;
  greedySnake.GameLoop();
  return 0;
}

