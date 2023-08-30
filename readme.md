# R-Tree using STR

This directory contains 2 script files which runs independently of each other:
1. `run_with_gcc.sh` (runs the C code and gives the output in the terminal)
2. `plot_graph.sh` (plots graphs in Python)

The code is contained in a single file `main.c`.

The code reads data from `data.txt` file, which is passed as a parameter in the main function.
By default `b or M =4` for the dataset of 21 points 
For larger datasets you can set the value of `M` (we tested with M=128) by changing the declaration of M in line 23

### To execute the code, follow these steps:
1. Run the below script/instructions for getting the C code output using the command:

```bash
bash run_with_gcc.sh
```
 The above script file compiles the code using gcc and then stores the mbrs contained in `rect_data.csv` file.

2. To view the plotting results, run the below script using the command:	

```bash
bash plot_graph.sh
```
Note: The `plot_graph.sh` script runs the C code and then sets up a Python virtual environment, runs the Python code, and saves the plot in `mbr.png`.

# Plot of the graph (using python script)

![mbr](https://github.com/HarshRathi2511/R-Tree/assets/75066364/794d7940-4cfc-45ad-b65a-d712425a7db5)

