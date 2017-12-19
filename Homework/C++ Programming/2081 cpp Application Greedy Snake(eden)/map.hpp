// MegaShow
#ifndef MAP_HPP_
#define MAP_HPP_

#include <iostream>
#include <list>
#include "global.hpp"
#include "snake.hpp"

class map {
  private:
    bool exit;
    char** cmap;
    snake* li;
    point size;
    std::list<point> food;

  public:
    map(point size, point head, std::list<point> food) {
        this->exit = false;
        this->li = new snake(head);
        this->size = size;
        this->food = food;
        cmap = new char*[size.x];
        for(int i = 0; i < size.x; i++)
            cmap[i] = new char[size.y];
        for(int i = 0; i < size.x; i++){
            for(int j = 0; j < size.y; j++)
                cmap[i][j] = EMPTY;
        }
        for(std::list<point>::iterator it = food.begin(); it != food.end(); it++)
            cmap[it->x][it->y] = FOOD;
        cmap[head.x][head.y] = HEAD;
    }

    bool move(direction di) {
        if(li->move(di, cmap, size, food))
            return true;
        exit = true;
        return false;
    }

    void print() {
        for(int i = 0; i < size.x; i++){
            for(int j = 0; j < size.y; j++)
                std::cout << cmap[i][j];
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    bool isGameOver() {
        return exit;
    }

    ~map(){
        delete li;
        for(int i = 0; i < size.x; i++)
            delete [] cmap[i];
        delete [] cmap;
    }
};

#endif