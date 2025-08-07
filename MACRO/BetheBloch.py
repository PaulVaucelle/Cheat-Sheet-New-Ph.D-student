# -*- coding: utf-8 -*-

import numpy as np
import matplotlib.pyplot as plt
import matplotlib.ticker as mticker
from scipy.stats import norm
from scipy.integrate import simps
import sys, os

# Parameters
InfunctionOf_p = False
power_exp = 7
#M = 105.6 # muon
#M = 938 # proton
#M = 139.57 # pion
M = 493.68 # kaon
oname = 'kaon'

# Exit file of (betagamma, dedx)
filename = "BettaGamma_dEdx.txt"
if filename in os.listdir("."):
  os.remove(filename)
else:
  os.system("touch " + filename)


# Silicon parameters
Z = 14
A = 28
I = 173*pow(10,-6)
rho = 2.3290
x0 = 0.2014  # ref:  doi:10.1016/0092-640x(84)90002-0     
x1 = 2.8715
a = 0.14921
delta0 = 0.14
C = 4.4351
k = 3.2546

# Global parameters, ref: pdg
K = 0.307075
z = -1
h_w = 28.816*np.sqrt(rho*Z/A)*pow(10,-6)
me = 0.511

a1 = K*z**2 * Z/A
a2 = (1+(me/M)**2)*M/(2*me)
a3 = -np.log(h_w/I) + 0.5 + 0.5*np.log(2*me/(I**2)) + 0.5*np.log(2*me) - 0.5*np.log(2*me/M)

beta = np.arange(0.1, 1-pow(10,-power_exp), pow(10,-power_exp))
beta_gamma = []
gamma = []
Tmax = []
delta = []
dedx = []
dedx2 = []
p = []



# Computations
for i in range (len(beta)):
    gamma.append(1/np.sqrt(1-beta[i]**2))
    beta_gamma.append(beta[i]*gamma[i])
    Tmax.append(2*me*beta_gamma[i]**2/(1+2*gamma[i]*me/M+(me/M)**2))

    x = np.log10(beta_gamma[i])
    if (x > x1): delta.append(2*np.log(10)*x - C)
    if (x >= x0 and x <= x1): delta.append(2*np.log(10)*x - C + a*(x1-x)**k)
    if (x < x0): delta.append(delta0 * pow(10, 2*(x-x0)))

    #dedx2.append(a1/beta[i]**2 * (np.log(beta_gamma[i]) - 0.5*np.log(a2+gamma[i]) - beta[i]**2 + a3))
    dedx.append(a1*1/beta[i]**2 * (0.5*np.log(2*me*(beta_gamma[i]**2)*Tmax[i]/(I**2)) - beta[i]**2 - 0.5*delta[i]))
    p.append(M*beta_gamma[i])






# Activate LaTeX text rendering
plt.rc('text', usetex=True)
plt.rcParams.update({
    'text.usetex': True,
    'font.family': 'serif',
})

# Plot the parametrization
fig, ax = plt.subplots()
#plt.plot(beta_gamma, dedx2, color='red', label=r'$\textrm{proton on Si}$')
if (InfunctionOf_p == False):
    minpos = beta_gamma[dedx.index(min(dedx))]

    plt.plot(beta_gamma, dedx, color='blue', label=r'$\textrm{kaon on Si}$')
    plt.plot(minpos, min(dedx),marker='o', markerfacecolor='blue', markeredgecolor='#cc0000', markeredgewidth=2, markersize=10)
    ax.text(minpos, min(dedx)+0.5, r'$($'+r'${:.2f}$'.format(minpos)+r'$,$'+r'${:.2f}$'.format(min(dedx))+r'$)$', color='black', fontsize=12, horizontalalignment='center')
    plt.title(r'$\textrm{Bethe Bloch function}$', fontsize=14)
    plt.xlabel(r'$\beta\gamma$',fontsize=12, fontweight='bold')
    plt.ylabel(r'$\displaystyle{\langle-\frac{dE}{dx}\rangle} \quad {\rm [MeV.g^{-1}.cm^{2}]}$', fontsize=12, fontweight='bold')
    ax.xaxis.set_label_coords(0.5,-0.07)
    ax.yaxis.set_label_coords(-0.07,0.5)
    ax.set_ylim(1, 110)
    plt.xscale('log')
    plt.yscale('log')
    plt.legend()

    ax.grid(which='minor', alpha=0.2)
    ax.grid(which='major', alpha=0.5)


    with open(filename, 'w') as file:
        for xi, yi in zip(beta_gamma, dedx):
            file.write("{} {}\n".format(xi, yi))

    plt.savefig("bethebloch_betagamma_"+oname+".pdf")

else:
    minpos = p[dedx.index(min(dedx))]

    plt.plot(p, dedx, color='blue', label=r'$\textrm{proton on Si}$')
    plt.plot(minpos, min(dedx),marker='o', markerfacecolor='blue', markeredgecolor='#cc0000', markeredgewidth=2, markersize=10)
    ax.text(minpos, min(dedx)+1, r'$($'+r'${:.2f}$'.format(minpos)+r'$,$'+r'${:.2f}$'.format(min(dedx))+r'$)$', color='black', fontsize=12, horizontalalignment='center')
    plt.title(r'$\textrm{Bethe Bloch function}$', fontsize=14)
    plt.xlabel(r'$p [\textrm{MeV}/c^2]$',fontsize=12, fontweight='bold')
    plt.ylabel(r'$\displaystyle{\langle-\frac{dE}{dx}\rangle} \quad {\rm [MeV.g^{-1}.cm^{2}]}$', fontsize=12, fontweight='bold')
    ax.xaxis.set_label_coords(0.5,-0.07)
    ax.yaxis.set_label_coords(-0.07,0.5)
    ax.set_ylim(1, 110)
    plt.xscale('log')
    plt.yscale('log')
    plt.legend()

    ax.grid(which='minor', alpha=0.2)
    ax.grid(which='major', alpha=0.5)


    plt.savefig("bethebloch_p_"+oname+".pdf")
