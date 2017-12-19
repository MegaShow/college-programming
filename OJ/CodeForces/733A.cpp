/*
 *	Name: [733A] Grasshopper And the String
 *	Author: Mega Show
 *	Date: 2017.1.6
 */

#include <cstdio>

int main(){
    int skill = 0, step;
    char s = 0;
    while(s != '\n'){
        s = getchar();
        step = 1;
        while(s != 'A' && s != 'E' && s != 'I' && s != 'O' && s != 'U' && s != 'Y'){
            if(s == '\n')
                break;
            step++;
            s = getchar();
        }
        if(skill < step)
            skill = step;
    }
    printf("%d\n", skill);
    return 0;
}
