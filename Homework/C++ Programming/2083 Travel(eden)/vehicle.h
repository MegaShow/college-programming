// MegaShow
#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <cmath>
#include <iostream>
#include <string>

struct City {
    double x, y;          // position of the city
    std::string name;  // name of city
};

class Vehicle {
 public:
    explicit Vehicle(double _speed) : speed(_speed) {}
    virtual void doTravel(const City& src, const City& dest) = 0;
    double getSpeed() const {
        return speed;
    }
    void setSpeed(double _speed) {
    	speed = _speed;
    }
    virtual ~Vehicle() {}

 private:
    double speed;
};


class BicycleStrategy : public Vehicle {
public:
	BicycleStrategy(double _speed) : Vehicle(_speed) { }
	virtual void doTravel(const City& src, const City& dest){
		double px = fabs(src.x - dest.x);
		double py = fabs(src.y - dest.y);
		double times = (px + py) / getSpeed();
		std::cout << "It takes " << times << " hours to Travel from "
				  << src.name << " to " << dest.name << " by Bicycle." << std::endl;
	}
};

class TrainStrategy : public Vehicle {
public:
	TrainStrategy(double _speed) : Vehicle(_speed) {}
	virtual void doTravel(const City& src, const City& dest){
		double px = fabs(src.x - dest.x);
		double py = fabs(src.y - dest.y);
		double times = sqrt( px * px + py * py ) / getSpeed();
		std::cout << "It takes " << times << " hours to Travel from "
				  << src.name << " to " << dest.name << " by Train." << std::endl;
	}
};

class AirplaneStrategy : public Vehicle {
public:
	AirplaneStrategy(double _speed) : Vehicle(_speed) {}
	virtual void doTravel(const City& src, const City& dest){
		double px = fabs(src.x - dest.x);
		double py = fabs(src.y - dest.y);
		double times = (py > px ? py : px) / getSpeed();
		std::cout << "It takes " << times << " hours to Travel from "
				  << src.name << " to " << dest.name << " by Airplane." << std::endl;
	}
};

#endif