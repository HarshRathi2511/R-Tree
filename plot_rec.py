import csv
from matplotlib import pyplot as plt, patches

# For csv
# row[0] -> anchor_x (bottom left corner)
# row[1] -> anchor_y (bottom left corner)
# row[2] -> width
# row[3] -> height

with open("./rect_data.csv", "r") as file:
    csv_reader = csv.reader(file)
    ax = plt.gca()

    # Limits for the axes
    # ax.set(xlim=(0,30), ylim=(0,30))
    
    for row in csv_reader:
        print(row)

        ax.add_patch(patches.Rectangle((int(row[0]), int(row[1])), width=int(row[2]), height=int(row[3]), edgecolor='blue', facecolor='none', linewidth=2))
    
    # for auto scaling
    plt.axis("scaled") # remove line in case of manually setting axis limits
    plt.show()