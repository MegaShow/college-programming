// MegaShow
#ifndef SNAKE_HPP_
#define SNAKE_HPP_

#include <list>
#include "global.hpp"

class snake {
  private:
    std::list<point> body;
  public:
    snake(point head){
        body.push_front(head);
    }

    bool move(direction di, char** map, point &size, std::list<point> &food){
        map[body.begin()->x][body.begin()->y] = BODY;
        point head = *body.begin();
        head.move(di);
        if((head.x < 0 || head.x >= size.x || head.y < 0 || head.y >= size.y)
            || (map[head.x][head.y] == BODY && !(body.back() == point(head.x, head.y)))){
            map[body.begin()->x][body.begin()->y] = HEAD;
            return false;
        }
        for(std::list<point>::iterator it = food.begin(); it != food.end(); it++){
            if(*it == head){
                food.erase(it);
                body.push_front(head);
                map[head.x][head.y] = HEAD;
                return true;
            }
        }
        map[body.back().x][body.back().y] = EMPTY;
        map[head.x][head.y] = HEAD;
        body.push_front(head);
        body.pop_back();
        return true;
    }

};

#endif