/* EE 08-1003 */

#ifndef _08_1003_H_
#define _08_1003_H_

#include <iostream>
#include <iomanip>
using namespace std;

double footToMeter(double foot){
    return foot * 0.305;
}

double meterToFoot(double meter){
    return meter / 0.305;
}

void display(){
    cout << setw(12) << "Feet" << setw(12) << "Meters" << setw(12) << "Meters" << setw(12) << "Feet" << endl;
    for(int i = 1, j = 20; i <= 10; i++, j+=5){
        cout << setiosflags(ios::fixed) << setprecision(3);
        cout << setw(12) << (double)i << setw(12) << footToMeter(i);
        cout << setw(12) << (double)j << setw(12) << meterToFoot(j);
        cout << endl;
    }
}

#endif

/*
int main(){
    display();
}
*/
