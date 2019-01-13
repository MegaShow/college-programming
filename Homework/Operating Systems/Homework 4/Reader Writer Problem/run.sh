echo "Reader First:"
gcc reader_first.c -pthread -std=c11 -Wall
if [ $? == 0 ]; then
    ./a.out 5 < in.txt
fi

echo

echo "Writer First:"
gcc writer_first.c -pthread -std=c11 -Wall
if [ $? == 0 ]; then
    ./a.out 5 < in.txt
fi
