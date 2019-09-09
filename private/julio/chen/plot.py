import matplotlib.pyplot as plt
import numpy as np

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------
# Filename
filename13 = 'RESLT/euler_0_200.dat'
Linewidth = 1;

t, u1, u2, u3 = np.loadtxt(filename13, delimiter='\t', unpack=True)

fig13 = plt.figure(13)
plt.plot(t, u3, label='$u_3$', color='blue', linestyle='solid', linewidth=Linewidth)
plt.grid()
#plt.xticks(np.arange(0,10,step=1))
#plt.yticks(np.arange(0,1.1,step=0.1))
#plt.xlim([0,10])
#plt.ylim([0,1])
plt.xlabel('t')
plt.ylabel('u3')
plt.title("Forward-Euler")
plt.legend()
plt.show()

filename14 = 'RESLT/euler_49800_50000.dat'
Linewidth = 1;

t, u1, u2, u3 = np.loadtxt(filename14, delimiter='\t', unpack=True)

fig14 = plt.figure(14)
plt.plot(t, u3, label='$u_3$', color='blue', linestyle='solid', linewidth=Linewidth)
plt.grid()
#plt.xticks(np.arange(0,10,step=1))
#plt.yticks(np.arange(0,1.1,step=0.1))
#plt.xlim([0,10])
#plt.ylim([0,1])
plt.xlabel('t')
plt.ylabel('u3')
plt.title("Forward-Euler")
plt.legend()
plt.show()

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------
# Filename
filename1 = 'RESLT/rk4_0_200.dat'
Linewidth = 1;

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
plt.title("Runge-Kutta 4")
plt.legend()
plt.show()

filename2 = 'RESLT/rk4_49800_50000.dat'
Linewidth = 1;

t, u1, u2, u3 = np.loadtxt(filename2, delimiter='\t', unpack=True)

fig2 = plt.figure(2)
plt.plot(t, u3, label='$u_3$', color='blue', linestyle='solid', linewidth=Linewidth)
plt.grid()
#plt.xticks(np.arange(0,10,step=1))
#plt.yticks(np.arange(0,1.1,step=0.1))
#plt.xlim([0,10])
#plt.ylim([0,1])
plt.xlabel('t')
plt.ylabel('u3')
plt.title("Runge-Kutta 4")
plt.legend()
plt.show()

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------
# Filename
filename3 = 'RESLT/bepc_0_200.dat'
Linewidth = 1;

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
plt.title("Backward-Euler $E(PC)^k E$")
plt.legend()
plt.show()

filename4 = 'RESLT/bepc_49800_50000.dat'
Linewidth = 1;

t, u1, u2, u3 = np.loadtxt(filename4, delimiter='\t', unpack=True)

fig4 = plt.figure(4)
plt.plot(t, u3, label='$u_3$', color='blue', linestyle='solid', linewidth=Linewidth)
plt.grid()
#plt.xticks(np.arange(0,10,step=1))
#plt.yticks(np.arange(0,1.1,step=0.1))
#plt.xlim([0,10])
#plt.ylim([0,1])
plt.xlabel('t')
plt.ylabel('u3')
plt.title("Backward-Euler $E(PC)^k E$")
plt.legend()
plt.show()

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------
# Filename
filename5 = 'RESLT/am2pc_0_200.dat'
Linewidth = 1;

t, u1, u2, u3 = np.loadtxt(filename5, delimiter='\t', unpack=True)

fig5 = plt.figure(5)
plt.plot(t, u3, label='$u_3$', color='blue', linestyle='solid', linewidth=Linewidth)
plt.grid()
#plt.xticks(np.arange(0,10,step=1))
#plt.yticks(np.arange(0,1.1,step=0.1))
#plt.xlim([0,10])
#plt.ylim([0,1])
plt.xlabel('t')
plt.ylabel('u3')
plt.title("Adams-Moulton 2 $E(PC)^k E$")
plt.legend()
plt.show()

filename6 = 'RESLT/am2pc_49800_50000.dat'
Linewidth = 1;

t, u1, u2, u3 = np.loadtxt(filename6, delimiter='\t', unpack=True)

fig6 = plt.figure(6)
plt.plot(t, u3, label='$u_3$', color='blue', linestyle='solid', linewidth=Linewidth)
plt.grid()
#plt.xticks(np.arange(0,10,step=1))
#plt.yticks(np.arange(0,1.1,step=0.1))
#plt.xlim([0,10])
#plt.ylim([0,1])
plt.xlabel('t')
plt.ylabel('u3')
plt.title("Adams-Moulton 2 $E(PC)^k E$")
plt.legend()
plt.show()

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------
# Filename
filename7 = 'RESLT/bdf1_0_200.dat'
Linewidth = 1;

t, u1, u2, u3 = np.loadtxt(filename7, delimiter='\t', unpack=True)

fig5 = plt.figure(5)
plt.plot(t, u3, label='$u_3$', color='blue', linestyle='solid', linewidth=Linewidth)
plt.grid()
#plt.xticks(np.arange(0,10,step=1))
#plt.yticks(np.arange(0,1.1,step=0.1))
#plt.xlim([0,10])
#plt.ylim([0,1])
plt.xlabel('t')
plt.ylabel('u3')
plt.title("Backward-Euler - Fully Implcit")
plt.legend()
plt.show()

filename8 = 'RESLT/bdf1_49800_50000.dat'
Linewidth = 1;

t, u1, u2, u3 = np.loadtxt(filename8, delimiter='\t', unpack=True)

fig8 = plt.figure(8)
plt.plot(t, u3, label='$u_3$', color='blue', linestyle='solid', linewidth=Linewidth)
plt.grid()
#plt.xticks(np.arange(0,10,step=1))
#plt.yticks(np.arange(0,1.1,step=0.1))
#plt.xlim([0,10])
#plt.ylim([0,1])
plt.xlabel('t')
plt.ylabel('u3')
plt.title("Backward-Euler - Fully Implcit")
plt.legend()
plt.show()

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------
# Filename
filename9 = 'RESLT/am_0_200.dat'
Linewidth = 1;

t, u1, u2, u3 = np.loadtxt(filename9, delimiter='\t', unpack=True)

fig9 = plt.figure(9)
plt.plot(t, u3, label='$u_3$', color='blue', linestyle='solid', linewidth=Linewidth)
plt.grid()
#plt.xticks(np.arange(0,10,step=1))
#plt.yticks(np.arange(0,1.1,step=0.1))
#plt.xlim([0,10])
#plt.ylim([0,1])
plt.xlabel('t')
plt.ylabel('u3')
plt.title("Adams Moulton 2 - Fully Implcit")
plt.legend()
plt.show()

filename10 = 'RESLT/am2_49800_50000.dat'
Linewidth = 1;

t, u1, u2, u3 = np.loadtxt(filename10, delimiter='\t', unpack=True)

fig10 = plt.figure(10)
plt.plot(t, u3, label='$u_3$', color='blue', linestyle='solid', linewidth=Linewidth)
plt.grid()
#plt.xticks(np.arange(0,10,step=1))
#plt.yticks(np.arange(0,1.1,step=0.1))
#plt.xlim([0,10])
#plt.ylim([0,1])
plt.xlabel('t')
plt.ylabel('u3')
plt.title("Adams Moulton 2 - Fully Implcit")
plt.legend()
plt.show()

# ------------------------------------------------------------------------------
# ------------------------------------------------------------------------------
# Filename
filename11 = 'RESLT/bdf2_0_200.dat'
Linewidth = 1;

t, u1, u2, u3 = np.loadtxt(filename11, delimiter='\t', unpack=True)

fig11 = plt.figure(11)
plt.plot(t, u3, label='$u_3$', color='blue', linestyle='solid', linewidth=Linewidth)
plt.grid()
#plt.xticks(np.arange(0,10,step=1))
#plt.yticks(np.arange(0,1.1,step=0.1))
#plt.xlim([0,10])
#plt.ylim([0,1])
plt.xlabel('t')
plt.ylabel('u3')
plt.title("BDF 2 - Fully Implcit")
plt.legend()
plt.show()

filename12 = 'RESLT/bdf2_49800_50000.dat'
Linewidth = 1;

t, u1, u2, u3 = np.loadtxt(filename12, delimiter='\t', unpack=True)

fig12 = plt.figure(12)
plt.plot(t, u3, label='$u_3$', color='blue', linestyle='solid', linewidth=Linewidth)
plt.grid()
#plt.xticks(np.arange(0,10,step=1))
#plt.yticks(np.arange(0,1.1,step=0.1))
#plt.xlim([0,10])
#plt.ylim([0,1])
plt.xlabel('t')
plt.ylabel('u3')
plt.title("BDF 2 - Fully Implcit")
plt.legend()
plt.show()
