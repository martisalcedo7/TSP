import numpy as np
import math

ciutats = 7

veinatge = []
# Create List of list
for i in range(ciutats):
    veinatge.append([])
    for j in range(ciutats):
        veinatge[i].append(0)


for idx, x in enumerate(veinatge):
    for idy, y in enumerate(veinatge[idx]):
        dist = abs(idx-idy)
        if dist == 0:
            veinatge[idx][idy] = 1
        elif dist > ciutats/2:
            veinatge[idx][idy] = math.exp(-(ciutats - dist)**2)
        else:
            veinatge[idx][idy] = math.exp(-(dist)**2)

    print(veinatge[idx])
