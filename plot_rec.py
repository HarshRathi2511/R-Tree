import matplotlib.pyplot as plt
import pandas as pd

# Read data from CSV into a DataFrame
df = pd.read_csv("rect_data.csv", header=None, names=['anchor_x', 'anchor_y', 'width', 'height'])

# Separate rectangles and point rectangles into separate DataFrames
rect_df = df.loc[(df['width'] != 0) | (df['height'] != 0)]
point_df = df.loc[(df['width'] == 0) & (df['height'] == 0)]

# Plot rectangles using matplotlib's Rectangle patches
fig, ax = plt.subplots(dpi=1200)
for _, row in rect_df.iterrows():
    ax.add_patch(plt.Rectangle((row['anchor_x'], row['anchor_y']), row['width'], row['height'], edgecolor='black', facecolor='none', linewidth=0.4))

# Plot point rectangles using matplotlib's scatter function
ax.scatter(point_df['anchor_x'], point_df['anchor_y'], s=.05, color='red')

# Set axis limits and aspect ratio
min_x = df['anchor_x'].min()
max_x = df['anchor_x'].max() + df['width'].max()
min_y = df['anchor_y'].min()
max_y = df['anchor_y'].max() + df['height'].max()
ax.set_xlim([min_x, max_x])
ax.set_ylim([min_y, max_y])
ax.set_aspect('equal')
plt.axis("scaled")
plt.show()
plt.savefig('mbr.png')