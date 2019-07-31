import matplotlib.pyplot as plt
import numpy as np

def u(x):
    fx = []
    for xs in x:
        fx.append(1/(1+xs))
    return fx

# Evaluate function
t = np.arange(0,20,0.1)
ut = u(t)
#print(ut)

# Plot function and approximations
filename1 = 'RESLT/rk45f.dat'
filename2 = 'RESLT/rk45dp.dat'
fig1 = plt.figure(1)

xrk45f, yrk45f = np.loadtxt(filename1, delimiter='\t', unpack=True)
xrk45dp, yrk45dp = np.loadtxt(filename2, delimiter='\t', unpack=True)

plt.plot(t,ut, label='u(t)', color='blue', linestyle='solid', linewidth=2)
plt.plot(xrk45f,yrk45f, label='rk45f', color='red', linestyle='dotted', linewidth=2, marker='o', markersize=5)
plt.plot(xrk45dp,yrk45dp, label='rk45dp', color='green', linestyle='dashed', linewidth=2, marker='x', markersize=5)
plt.grid()
plt.xticks(np.arange(0,21,step=1))
plt.yticks(np.arange(0,1.1,step=0.1))
plt.xlim([0,20])
plt.ylim([0,1])
plt.xlabel('t')
plt.ylabel('u(t)')
plt.title("Runge-Kutta Adaptive Time Stepper")
plt.legend()
plt.show()

# Plot errors
filename3 = 'RESLT/rk45f_error.dat'
filename4 = 'RESLT/rk45dp_error.dat'
fig2 = plt.figure(2)

xrk45f_error, yrk45f_error = np.loadtxt(filename3, delimiter='\t', unpack=True)
xrk45dp_error, yrk45dp_error = np.loadtxt(filename4, delimiter='\t', unpack=True)

plt.plot(xrk45f_error,yrk45f_error, label='rk45f_error', color='red', linestyle='dashed', linewidth=2, marker='o', markersize=5)
plt.plot(xrk45dp_error,yrk45dp_error, label='rk45dp_error', color='green', linestyle='dashed', linewidth=2, marker='x', markersize=5)
plt.grid()
plt.xticks(np.arange(0,21,step=1))
#plt.yticks(np.arange(0,1.1,step=0.1))
plt.xlim([0,20])
#plt.ylim([0,1])
plt.xlabel('t')
plt.ylabel('error')
plt.title("Runge-Kutta Adaptive Time Stepper Error")
plt.legend()
plt.show()


