rm *.o
rm rect_data.csv

gcc -c main.c
gcc -o r_tree_exe main.o -lm 
./r_tree_exe

# run python code here after virtual env