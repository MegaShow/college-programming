// UVA227 MegaShow 2017.2.5

#include <cstdio>
//#include <cstdlib>


char map[5][10];
int x;
int y;
int counter;

int main(){
    fgets(map[0], 10, stdin);
    while(map[0][0] != 'Z'){
        for(int i = 1; i < 5; i++)
            fgets(map[i], 10, stdin);
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < 5; j++){
                if(map[i][j] == ' ' || map[i][j] == '\n'){
                    x = j;
                    y = i;
                }
            }
        }
        map[y][x] = ' ';
        int c;
        bool flag = false;
        while((c = getchar()) != '0'){
            switch(c){
                case 'A': if(y - 1 < 0 || flag) flag = true; else{ map[y][x] = map[y-1][x]; y--; } break;
                case 'B': if(y + 1 > 4 || flag) flag = true; else{ map[y][x] = map[y+1][x]; y++; } break;
                case 'L': if(x - 1 < 0 || flag) flag = true; else{ map[y][x] = map[y][x-1]; x--; } break;
                case 'R': if(x + 1 > 4 || flag) flag = true; else{ map[y][x] = map[y][x+1]; x++; } break;
                case '\n': break;
                default: flag = true;

            }
            map[y][x] = ' ';
        }
        getchar();
        if(counter++)
            printf("\n");
        printf("Puzzle #%d:\n", counter);
        if(flag)
            printf("This puzzle has no final configuration.\n");
        else{
            for(int i = 0; i < 5; i++){
                for(int j = 0; j < 4; j++)
                    printf("%c ", map[i][j]);
                printf("%c\n", map[i][4]);
            }
        }
        fgets(map[0], 10, stdin);
    }
}
