/*
 *	Name: [046] 解方程(一元二次)
 *	Author: Mega Show
 *	Date: 2016.12.25
 */

#include <math.h>

int getRoots(double a, double b, double c, \
             double *pRootOne, double *pRootTwo){
    double delta = b * b - 4 * a * c;
    if(delta < 0)
        return 0;
    else{
        double one = (- b - sqrt(delta)) / (2 * a);
        double two = (- b + sqrt(delta)) / (2 * a);
        *pRootOne = (one > two ? one : two);
        *pRootTwo = (one > two ? two : one);
        return 1;
    }
}
