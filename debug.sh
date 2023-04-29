rm *.o
rm *.exe

gcc -c main.c
gcc -o r_tree_exe main.o -lm 
gdb r_tree_exe