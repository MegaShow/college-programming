#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#ifndef SYMBOLS
#define HEAD '@'
#define BODY 'X'
#define EMPTY '+'
#define FOOD '$'
#endif  // !SYMBOLS

enum direction { up = 0, down = 1, left = 2, right = 4, freeze = 5 };

struct point {
  int x;
  int y;
  point(int x = 0, int y = 0) : x(x), y(y) {}
  point(const point& another) : x(another.x), y(another.y) {}
  point& operator=(const point& other) {
    x = other.x;
    y = other.y;
    return *this;
  }
  friend bool operator==(const point& point1, const point& point2) {
    return point1.x == point2.x && point1.y == point2.y;
  }
  point& move(direction d) {
    switch (d) {
      case up:
        x--;
        break;
      case down:
        x++;
        break;
      case left:
        y--;
        break;
      case right:
        y++;
        break;
      case freeze:
      default:
        break;
    }
    return *this;
  }
};

#endif  // !_GLOBAL_H_
