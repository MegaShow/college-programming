/*
 *	Name: [047] Substring
 *	Author: Mega Show
 *	Date: 2016.12.31
 */

int getNumOfSubstring(char a[], char b[]){
    int counter = 0;
    for(int i = 0; a[i] != 0; i++){
        counter++;
        for(int j = i; b[j-i] != 0; j++){
            if(a[j] != b[j-i]){
                counter--;
                break;
            }
        }
    }
    return counter;
}
