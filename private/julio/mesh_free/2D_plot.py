from mpl_toolkits import mplot3d

import matplotlib.pyplot as plt
import numpy as np

# ---------------------------------
# Filename
filename = 'RESLT/output.dat'

fig1 = plt.figure(1)
ax1 = plt.axes(projection="3d")
x1, x2, fx1x2 = np.loadtxt(filename, delimiter=' ', unpack=True)
#ax1.plot(x, fx, label='$f(x)$', color='red', linestyle='solid', linewidth=Linewidth)
#ax1.plot3D(x1, x2, fx1x2, label='$f(x)$', color='red')
#ax1.scatter3D(x1, x2, fx1x2, label='$f(x)$', color='red')
#ax1.plot_wireframe(x1, x2, fx1x2, label='$f(x)$', color='red')
#ax1.plot_surface(x1, x2, fx1x2, label='$f(x)$', color='red')
ax1.plot_trisurf(x1, x2, fx1x2, label='$f(x)$', color='red')

ax1.grid()
#plt.xticks(np.arange(0,10,step=1))
#plt.yticks(np.arange(0,1.1,step=0.1))
#ax1.axis([0,1,0,1])
ax1.set_xlabel('$x_1$')
ax1.set_ylabel('$x_2$')
ax1.set_zlabel('$f(x_1, x_2)$')
#ax1.legend()
plt.show()

# ---------------------------------
# Filename
filename = 'RESLT/error.dat'

fig2 = plt.figure(2)
ax2 = plt.axes(projection="3d")
x1, x2, e = np.loadtxt(filename, delimiter=' ', unpack=True)
#ax2.plot(x, e, label='error', color='red', linestyle='solid', linewidth=Linewidth)
#ax2.plot3D(x1, x2, e, label='$f(x)$', color='red')
#ax2.scatter3D(x1, x2, e, label='$f(x)$', color='red')
#ax2.plot_wireframe(x1, x2, e, label='$f(x)$', color='red')
#ax2.plot_surface(x1, x2, e, label='$f(x)$', color='red')
ax2.plot_trisurf(x1, x2, e, label='$f(x)$', color='red')

ax2.grid()
#plt.xticks(np.arange(0,10,step=1))
#plt.yticks(np.arange(0,1.1,step=0.1))
#ax2.axis([0,1,0,1,-1,1])
ax2.set_xlabel('$x_1$')
ax2.set_ylabel('$x_2$')
ax2.set_zlabel('$error(x_1, x_2)$')
#ax2.legend()
plt.show()

