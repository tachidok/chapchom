from mpl_toolkits import mplot3d

import numpy as np
import matplotlib.pyplot as plt

def z_function(x, y):
    return np.sin(np.sqrt(x ** 2 + y ** 2))

x = np.linspace(-6, 6, 30)
y = np.linspace(-6, 6, 30)

X, Y = np.meshgrid(x, y)
Z = z_function(X, Y)

fig = plt.figure()
ax = plt.axes(projection="3d")
ax.plot_wireframe(X, Y, Z, color='green')
ax.set_xlabel('x')
ax.set_ylabel('y')
ax.set_zlabel('z')

print("x")
print(x)
print("y")
print(y)

print("X")
print(X)
print("Y")
print(Y)
print("Z")
print(Z)

plt.show()
