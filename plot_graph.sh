rm *.o
rm r_tree_exe

gcc -c DSA_assignment_group_43.c
gcc -o r_tree_exe DSA_assignment_group_43.o -lm 
./r_tree_exe

# run python code here after virtual env for graph 
python3 -m venv myenv
source myenv/bin/activate
# Install required packages
pip install matplotlib
pip install pandas
python3 plot_rec.py
# Deactivate the virtual environment
deactivate

# Display the image 
image_path="mbr.png"
if [[ "$OSTYPE" == "darwin"* ]]; then
    # macOS
    open "$image_path"
elif [[ "$OSTYPE" == "msys" ]]; then
    # Windows
    cmd.exe /C start "$image_path"
elif [[ "$OSTYPE" == "linux-gnu" ]]; then
    # Linux
    xdg-open "$image_path"
else
    # Unsupported OS
    echo "Unsupported operating system."
fi




