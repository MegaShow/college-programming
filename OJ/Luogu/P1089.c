#include <stdio.h>

int main() {
    int val, sum = 0, bank = 0;
    for (int i = 1; i <= 12; i++) {
        scanf("%d", &val);
        sum += 300 - val;
        if (sum < 0) {
            printf("-%d\n", i);
            return 0;
        }
        bank += 100 * (sum / 100);
        sum %= 100;
    }
    printf("%d\n", sum + bank * 120 / 100);
}
