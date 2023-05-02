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




