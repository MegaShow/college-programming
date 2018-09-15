#include <stdio.h>

int main(void) {
    int val;
    double price = 0;
    scanf("%d", &val);
    if (val > 400) {
        price += 0.5663 * (val - 400);
        val = 400;
    }
    if (val > 150) {
        price += 0.4663 * (val - 150);
        val = 150;
    }
    price += 0.4463 * val;
    printf("%.1f\n", price);
}
