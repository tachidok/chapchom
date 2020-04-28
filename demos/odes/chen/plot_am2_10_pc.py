from mpl_toolkits.mplot3d import axes3d
import matplotlib.pyplot as plt
import numpy as np

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------
filename1 = 'RESLT/am2pc_10_0_200.dat'
Linewidth = 1

t, u1, u2, u3 = np.loadtxt(filename1, delimiter='\t', unpack=True)

fig1 = plt.figure(1)
plt.plot(t, u3, label='$u_3$', color='blue', linestyle='solid', linewidth=Linewidth)
plt.grid()
#plt.xticks(np.arange(0,10,step=1))
#plt.yticks(np.arange(0,1.1,step=0.1))
#plt.xlim([0,10])
#plt.ylim([0,1])
plt.xlabel('t')
plt.ylabel('u3')
plt.title("Adams-Moulton 2 PC")
plt.legend()
plt.show()

fig2 = plt.figure(2)
ax2 = fig2.add_subplot(projection='3d')

ax2.plot3D(u1, u2, u3, color='gray', linewidth=Linewidth)
#ax1.plot_wireframe(u1, u2, u3)
#ax1.scatter(u1, u2, u3, c='r', marker='o')
plt.grid()
ax2.set_xlabel('u1')
ax2.set_ylabel('u2')
ax2.set_zlabel('u3')
plt.title("Adams-Moulton 2 PC")
plt.show()

filename3 = 'RESLT/am2pc_10_49800_50000.dat'
Linewidth = 1

t, u1, u2, u3 = np.loadtxt(filename3, delimiter='\t', unpack=True)

fig3 = plt.figure(3)
plt.plot(t, u3, label='$u_3$', color='blue', linestyle='solid', linewidth=Linewidth)
plt.grid()
#plt.xticks(np.arange(0,10,step=1))
#plt.yticks(np.arange(0,1.1,step=0.1))
#plt.xlim([0,10])
#plt.ylim([0,1])
plt.xlabel('t')
plt.ylabel('u3')
plt.title("Adams-Moulton 2 PC")
plt.legend()
plt.show()

fig4 = plt.figure(4)
ax4 = fig4.add_subplot(projection='3d')

ax4.plot3D(u1, u2, u3, color='gray', linewidth=Linewidth)
#ax1.plot_wireframe(u1, u2, u3)
#ax1.scatter(u1, u2, u3, c='r', marker='o')
plt.grid()
ax4.set_xlabel('u1')
ax4.set_ylabel('u2')
ax4.set_zlabel('u3')
plt.title("Adams-Moulton 2 PC")
plt.show()
