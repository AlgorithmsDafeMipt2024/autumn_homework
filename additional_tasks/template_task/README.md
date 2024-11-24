# Reforestation simulation

There was a large rectangular forest consisting of M * N chunks. But unfortunately there was a forest fire and some of the chunks were burned to the ground, some were partially burned, and the rest were completely salvaged.

The forest after the fire is represented as a matrix M * N where each cell contains a value 0, 1 or 2 which has the following value:  

    0: Burned to the ground

    1: Partially burned

    2: Completely preserved

The goal is find the time nedeed to recover all partially burned chunks. A salvaged chunk with index (i, j) can recover partially burned neighboring chunks (up, down, left and right). If it is not possible to recover all partially burned chunks, just return -1 and the list of indecies of the chunks that can't be recovered.

P.S. This problem does not use the graph classes from lib, but a kind of BFS graph traversal.