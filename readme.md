This directory contains 2 script files which runs independantly of each other :- 
1)run_with_gcc.sh (runs the c code and gives o/p in terminal)
2)plot_graph.sh (plots graphs in python)

The code is contained in a single file DSA_assignment_group_43.c

The code reads data from "data.txt" file, passed as a parameter in the main function 

To execute the code run the script/instructions for getting the C code output using the command 
"bash run_with_gcc.sh"

The above script file compiles the code using gcc and then stores the mbrs contained in rect_data.csv file 

To view the plotting results run the below script using the command 
"bash plot_graph.sh" 

This file sets up python virtual environment and runs the python code and saves the plot in "mbr.png" 


