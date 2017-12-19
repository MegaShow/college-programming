#include <iostream>
#include <string>
#include "vehicle.h"
#include "tourist.h"
 int main() {
     std::string cname;     // name of the city
    double x, y;           // position of the city
    double bsp, tsp, asp;  // speed of bicycle, train and airplane.
     std::cin >> cname >> x >> y;
    City src = {x, y, cname};
    std::cin >> cname >> x >> y;
    City dest = {x, y, cname};
     std::cin >> bsp >> tsp >> asp;
    BicycleStrategy bicycle(bsp);
    TrainStrategy train(tsp);
    AirplaneStrategy air(asp);
     Tourist lsc(&bicycle);
    lsc.travel(src, dest);
     lsc.setStrategy(&train);
    lsc.travel(src, dest);
     lsc.setStrategy(&air);
    lsc.travel(src, dest);
     return 0;
}
  