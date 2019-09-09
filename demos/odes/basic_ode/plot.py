import matplotlib.pyplot as plt
import numpy as np

def u(x):
    fx = []
    for xs in x:
        fx.append(1/(1+xs))
    return fx

# Evaluate function
t = np.arange(0,2,0.1);
ut = u(t);

# Filename
Linewidth = 2;

# -------------------------------------------------------------------------------------
# Plot 1
# -------------------------------------------------------------------------------------
t_euler, u_euler = np.loadtxt("RESLT/euler.dat", delimiter='\t', unpack=True);
t_rk4, u_rk4 = np.loadtxt("RESLT/rk4.dat", delimiter='\t', unpack=True);
t_bepc, u_bepc = np.loadtxt("RESLT/bepc.dat", delimiter='\t', unpack=True);
t_am2pc, u_am2pc = np.loadtxt("RESLT/am2pc.dat", delimiter='\t', unpack=True);
t_bdf1, u_bdf1 = np.loadtxt("RESLT/bdf1.dat", delimiter='\t', unpack=True);
t_am2, u_am2 = np.loadtxt("RESLT/am2.dat", delimiter='\t', unpack=True);
t_bdf2, u_bdf2 = np.loadtxt("RESLT/bdf2.dat", delimiter='\t', unpack=True);

fig1 = plt.figure(1)
plt.plot(t_euler, u_euler, label='euler', color='blue', linestyle='dashed', linewidth=Linewidth)
plt.plot(t_rk4, u_rk4, label='rk4', color='red', linestyle='dashed', linewidth=Linewidth)
plt.plot(t_bepc, u_bepc, label='bepc', color='gray', linestyle='dashed', linewidth=Linewidth)
plt.plot(t_am2pc, u_am2pc, label='am2pc', color='green', linestyle='dashed', linewidth=Linewidth)
plt.plot(t_bdf1, u_bdf1, label='bdf1', color='purple', linestyle='dashed', linewidth=Linewidth)
plt.plot(t_am2, u_am2, label='am2', color='black', linestyle='dashed', linewidth=Linewidth)
plt.plot(t_bdf2, u_bdf2, label='bdf2', color='yellow', linestyle='dashed', linewidth=Linewidth)
plt.plot(t, ut, label='u', color='cyan', linestyle='solid', linewidth=Linewidth)
plt.grid()
#plt.xticks(np.arange(0,10,step=1))
#plt.yticks(np.arange(0,1.1,step=0.1))
#plt.xlim([0,10])
#plt.ylim([0,1])
plt.xlabel('t')
plt.ylabel('u(t)')
plt.title("Time-Steppers")
plt.legend()
plt.show()

# -------------------------------------------------------------------------------------
# Plot 2
# -------------------------------------------------------------------------------------
t_euler, e_euler = np.loadtxt("RESLT/euler_error.dat", delimiter='\t', unpack=True);
t_rk4, e_rk4 = np.loadtxt("RESLT/rk4_error.dat", delimiter='\t', unpack=True);
t_bepc, e_bepc = np.loadtxt("RESLT/bepc_error.dat", delimiter='\t', unpack=True);
t_am2pc, e_am2pc = np.loadtxt("RESLT/am2pc_error.dat", delimiter='\t', unpack=True);
t_bdf1, e_bdf1 = np.loadtxt("RESLT/bdf1_error.dat", delimiter='\t', unpack=True);
t_am2, e_am2 = np.loadtxt("RESLT/am2_error.dat", delimiter='\t', unpack=True);
t_bdf2, e_bdf2 = np.loadtxt("RESLT/bdf2_error.dat", delimiter='\t', unpack=True);

fig2 = plt.figure(2)
plt.plot(t_euler, e_euler, label='euler', color='blue', linestyle='solid', linewidth=Linewidth)
plt.plot(t_rk4, e_rk4, label='rk4', color='red', linestyle='solid', linewidth=Linewidth)
plt.plot(t_bepc, e_bepc, label='bepc', color='gray', linestyle='solid', linewidth=Linewidth)
plt.plot(t_am2pc, e_am2pc, label='am2pc', color='green', linestyle='solid', linewidth=Linewidth)
plt.plot(t_bdf1, e_bdf1, label='bdf1', color='purple', linestyle='solid', linewidth=Linewidth)
plt.plot(t_am2, e_am2, label='am2', color='black', linestyle='solid', linewidth=Linewidth)
plt.plot(t_bdf2, e_bdf2, label='bdf2', color='yellow', linestyle='solid', linewidth=Linewidth)
plt.grid()
#plt.xticks(np.arange(0,10,step=1))
#plt.yticks(np.arange(0,1.1,step=0.1))
#plt.xlim([0,10])
#plt.ylim([0,1])
plt.xlabel('t')
plt.ylabel('error')
plt.title("Approximation Error")
plt.legend()
plt.show()

