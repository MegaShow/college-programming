/*
 *	Name: [051] How many 1's are there
 *	Author: Mega Show
 *	Date: 2016.12.31
 */

#include <stdio.h>

int main(){
    int n, m, counter;
    scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &m);
        counter = 0;
        while(m){
            m &= (m - 1);
            counter++;
        }
        printf("%d\n", counter);
    }
    return 0;
}
