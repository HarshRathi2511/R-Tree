rm *.o
rm r_tree_exe

gcc -c main.c
gcc -o r_tree_exe main.o -lm 
./r_tree_exe

# run python code here after virtual env for graph 
python3 -m venv myenv
source myenv/bin/activate
# Install required packages
pip install matplotlib
python3 plot_rec.py
# Deactivate the virtual environment
deactivate


#view the image 

# for mac (img cat to display the created image in the terminal)
# brew install --cask iterm2
# brew install imgcat

# Check if catimg is installed for ubuntu 
if ! command -v catimg &> /dev/null; then
    echo "catimg not found. Installing..."
    sudo apt-get update
    sudo apt-get install catimg
fi

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




