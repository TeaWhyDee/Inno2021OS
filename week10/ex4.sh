mkdir tmp
touch tmp/file1 tmp/file2
ln tmp/file1 tmp/link1
gcc ex4.c -o ./a.out
./a.out > ex4.txt
