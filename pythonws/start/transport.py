# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt

# left border
x_lb = -1
# right border
x_rb = 1
# points count
points_c = 1000
# step
dx = float(x_rb - x_lb)/points_c


# TIME
t_0 = 0
# end time
t_e = 1
# count of time points
points_t = 1000
# step
dt = float(t_e - t_0)/points_t


# TASK
x_0 = -.8
d = .2
C = .4
#def start_func(_x):
#    yield np.exp((-(x - x_0)**2)/(d**2))


# create zeros array
#x = np.zeros(points_c + 1)
#x[0] = x_lb
#for i in range(points_c):
#    x[i + 1] = x[i] + dx


## or u can use
x = np.linspace(x_lb, x_rb, points_c)
#print x

y = np.array([.0] * points_c * points_t).reshape(points_t,points_c)


y[0] = np.exp(-((x - x_0) ** 2)/(d ** 2))

#yt2[i] = (1 - C)*yt1[i] + C*yt1[i-1];

for k in range(points_t - 1):
    for i in range(points_c - 1):
        y[k + 1][i + 1] = (1.0 - C)*y[k][i + 1] + C*y[k][i]

plt.plot(x, y[0])
plt.plot(x, y[50])
plt.plot(x, y[900])

plt.show()

