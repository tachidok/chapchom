import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm

# Create a 3D array
# meshgrid produces all combinations of given x and y
x=np.linspace(-3,3,256) # x goes from -3 to 3, with 256 steps
y=np.linspace(-3,3,256) # y goes from -3 to 3, with 256 steps
X,Y=np.meshgrid(x,y) # combine all x with all y
print(X)
print(Y)


# A function of x and y for demo purposes
Z=np.sinc(np.sqrt(X**2 + Y**2))
print(Z)

fig=plt.figure()
ax=fig.gca(projection='3d')

# rstride: Array row stride (step size), defaults to 1
# cstride: Array column stride (step size), defaults to 1
# rcount: Use at most this many rows, defaults to 50
# ccount: Use at most this many columns, defaults to 50

#ax.plot_wireframe(X,Y,Z,color='k',rcount=25,ccount=25)
#ax.contour3D(X,Y,Z,50,cmap='binary')
ax.plot_surface(X,Y,Z,rstride=1,cstride=1,cmap='viridis', edgecolor='none')

plt.show()
