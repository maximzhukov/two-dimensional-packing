import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import numpy.random as np
import os

fig = plt.figure()
ax = fig.add_subplot(111)

ax.set_axisbelow(True)
(total_height, total_width) = tuple(map(int, input().split(' ')))
count = int(input())
for data in range(count):
    (x, y, width, height) = tuple(map(int, input().split(' ')))
    random_color = (np.random(), np.random(), np.random())
    rect2 = mpatches.Rectangle((x, y), width, height, linewidth=0.5, edgecolor='black', facecolor=random_color, label='Label')
    patch = ax.add_patch(rect2)
plt.xticks([0, total_width])
plt.yticks([0, total_height])

plt.xlabel("width")
plt.ylabel("height")

plt.show()
