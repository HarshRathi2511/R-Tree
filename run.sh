rm *.o
rm *.exe

gcc -c main.c
gcc -o r_tree_exe main.o -lm 
./r_tree_exe

