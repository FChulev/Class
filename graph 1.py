import numpy as np
import matplotlib.pyplot as plt
x = []
y1 = [0] * 25
y2 = [0] * 25
st = open("data1.txt", mode = 'r')
stre = st.read()
stre = stre.split('\n')
for i in range(5):
    y1[5 * i], y2[5 * i], y1[5 * i + 1], y2[5 * i + 1], y1[5 * i + 2], y2[5 * i + 2], y1[5 * i + 3], y2[5 * i + 3], y1[5 * i + 4], y2[5 * i + 4] = map(float, (stre[i]).split())
for a in [100, 1000, 10000, 100000, 1000000]:
    for i in range(5):
        x.append(a)
x = np.array(x)
y1 = np.array(y1)
y2 = np.array(y2)
plt.scatter(x, y1)
plt.show()
plt.scatter(x, y2)
plt.show()
st.close()
