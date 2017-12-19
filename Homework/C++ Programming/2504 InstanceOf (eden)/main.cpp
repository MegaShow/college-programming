#include "instance.h"
 
// Google style don't allow dynamic_cast
// we use marco to trick the system
#define DC dynamic_cast
 
/*
   relationship of each class
            Object
              /\
             /  \
        Animal  Vehicle
          /\      /\
         /  \    /  \
       Dog  Cat Bus  Car
 
*/
 
int main(void) {
    Object *object;
    Animal *animal;
    Dog *dog;
    Cat *cat;
    Vehicle *vehicle;
    Bus *bus;
    Car *car;
 
    // sidecast
    {
        // car >> bus results in NULL
        car = new Car;
        bus = DC<Bus*>(car);
        cout << instanceOf(bus) << endl;
        delete car;
 
        // cat >> dog results in NULL
        cat = new Cat;
        dog = DC<Dog*>(cat);
        cout << instanceOf(dog) << endl;
        delete cat;
    }
 
    // upcast
    {
        // bus >> vehicle
        bus = new Bus;
        vehicle = DC<Vehicle*>(bus);
        cout << instanceOf(vehicle) << endl;
        delete bus;
 
        // car >> object
        car = new Car;
        object = car;
        cout << instanceOf(object) << endl;
        delete car;
 
        // vehicle >> object
        vehicle = new Vehicle;
        object = vehicle;
        cout << instanceOf(object) << endl;
        delete vehicle;
    }
 
    // downcast
    {
        // object >> animal
        object = new Animal;
        animal = DC<Animal*>(object);
        cout << instanceOf(animal) << endl;
        delete object;
 
        // animal >> dog
        animal = new Dog;
        dog = DC<Dog*>(animal);
        cout << instanceOf(dog) << endl;
        delete animal;
 
        // animal >> cat
        animal = new Cat;
        cat = DC<Cat*>(animal);
        cout << instanceOf(cat) << endl;
        delete animal;
    }
 
    return 0;
}
 