/*
 *	Name: [045] 守望者的逃离
 *	Author: Mega Show
 *	Date: 2016.11.26 11:56
 */

/* judge()
 * return + means successful escaping 
 * return - means failed escaping
 * the value means the using time or the opposite num of the left distance
 */ 
#define METHOD 1

#include <stdio.h>

/* method 1*/
#if METHOD == 1

int judge(int sp, int distance, int time){
	while(time){
		if(sp >= 10){
			distance -= 60;
			sp -= 10;
			time--;
		}
		else{
			int sp_counter = (10 - sp + 3) / 4 + 1;
			if(sp >= 2 && time >= sp_counter && distance > 17 * sp_counter){
				distance -= 60;
				sp = sp + 4 * (sp_counter - 1) - 10;
				time -= sp_counter;
			}
			else{
				distance -= 17;
				time--;
			}
		}
		if(distance <= 0)
			break;
	}
	return (distance <= 0 ? time : -distance);
}

/* method 2 */
#elif METHOD == 2

int judge(int sp, int distance, int time){
	while(time){
		if(sp >= 10){
			distance -= 60;
			sp -= 10;
			time--;
		}
		else if(sp >= 6 && time >= 2 && distance > 34){
			distance -= 60;
			sp -= 6;
			time -= 2;
		}
		else if(sp >= 2 && time >= 3 && distance > 51){
			distance -= 60;
			sp -= 2;
			time -= 3;
		}
		else{
			distance -= 17;
			time--;
		}
		if(distance <= 0)
			break;
	}
	return (distance <= 0 ? time : -distance);
}

#endif

/* main function */

int main(){
	int sp, distance, time;
	while(scanf("%d%d%d", &sp, &distance, &time) != EOF){
		int result = judge(sp, distance, time);
		if(result >= 0)
			printf("Yes\n%d\n", time - result);
		else
			printf("No\n%d\n", distance + result);
	}
	return 0;
}