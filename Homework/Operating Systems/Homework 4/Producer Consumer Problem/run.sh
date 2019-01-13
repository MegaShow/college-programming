gcc main.c buffer.c -pthread -std=c11 -Wall
if [ $? == 0 ]; then
    ./a.out 60 3 3 < in.txt
fi
