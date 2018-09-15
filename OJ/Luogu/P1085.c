#include <stdio.h>

int main(void) {
    int school, home, maxVal = 8, maxDay = 0;
    for (int i = 1; i <= 7; i++) {
        scanf("%d %d", &school, &home);
        if (school + home > maxVal) {
            maxDay = i;
            maxVal = school + home;
        }
    }
    printf("%d\n", maxDay);
}
