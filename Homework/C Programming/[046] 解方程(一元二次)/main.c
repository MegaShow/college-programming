/* Written by Matrix */

#include <stdio.h>
int main() {
    int t;
    double a, b, c, rootOne, rootTwo;
    int getRoots(double a, double b, double c, \
    double *pRootOne, double *pRootTwo);
    scanf("%d", &t);
    while (t--) {
        scanf("%lf%lf%lf", &a, &b, &c);
        if (0 == getRoots(a, b, c, &rootOne, &rootTwo)) {
            printf("no answers\n");
        } else {
            printf("%.2lf %.2lf\n", rootOne, rootTwo);
        }
    }
    return 0;
}
