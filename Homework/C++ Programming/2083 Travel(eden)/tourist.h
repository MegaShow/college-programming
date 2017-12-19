// MegaShow
#ifndef TOURIST_H_
#define TOURIST_H_

#include "vehicle.h"

class Tourist {
 public:


    explicit Tourist(Vehicle* strategy_);

    void setStrategy(Vehicle* strategy_);

    void travel(const City& src, const City& dest);

 private:
    Vehicle* strategy;
};


Tourist::Tourist(Vehicle* strategy_){
	strategy = strategy_;
}

void Tourist::setStrategy(Vehicle* strategy_){
	strategy = strategy_;
}

void Tourist::travel(const City& src, const City& dest){
	strategy->doTravel(src, dest);
}


#endif