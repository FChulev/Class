import numpy as np
import matplotlib.pyplot as plt

n = int(input())
x = [None] * n
y1 = [None] * n
print(len(x))
for i in range(n):
    x[i], y1[i] = map(float, input().split())
x = np.array(x)
y1 = np.array(y1)
plt.scatter(y1, x)
plt.show()
