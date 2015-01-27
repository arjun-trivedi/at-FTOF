# -*- coding: utf-8 -*-
# <nbformat>3.0</nbformat>

# <markdowncell>

# ### Toy code to see how determination of $\mu$ and $\sigma$ of a Gaussian Distribution is determined by:
# 
# * Number of samples
# * $\mu$ and $\sigma$ of the distribution
#     * The wider the distribution, the more the samples need to better approximate the mean

# <codecell>

import numpy as np

mean=[]
std=[]
percerr_mean=[]
percerr_std=[]
tv=[]

mu=10
sigma=1000
for x in range(1,3000):
    nsamples = x*10
    a = np.random.normal(loc = mu, scale = sigma, size = nsamples) 
    mean.append(np.mean(a))
    std.append(np.std(a))
    percerr_mean.append(((np.mean(a)-mu)/mu)*100)
    percerr_std.append(((np.std(a)-sigma)/sigma)*100)
    #print np.mean(a)
    #print np.std(a)
    #print x
    tv.append(x);
#print tv


plt.figure(figsize=(20,5))
plt.scatter(tv,mean)

plt.figure(figsize=(20,5))
plt.scatter(tv,std)

plt.figure(figsize=(20,5))
plt.scatter(tv,percerr_mean)
plt.ylim(-20,20)

plt.figure(figsize=(20,5))
plt.scatter(tv,percerr_std)
plt.ylim(-20,20)

# <markdowncell>

# ### Cross section measurement errors
# #### N = $\sigma$L, therefore $\sigma$ = N/L
# * assume $\sigma$ = 2 b $(1*10^{-28} m^{2})$
#     + We directly measure N, L
#         - $\delta N = \sqrt N$
#         - $\delta L = 0$
#         - $\therefore \delta\sigma = \frac{\delta N}{L} = \frac{\sqrt N}{L}$

# <codecell>

import math
from __future__ import division

L = arange(100,10000,1000)
N = 2*L
s = N/L
err_N = sqrt(N)
err_s = err_N/L
f, axarr = plt.subplots(3, sharex=True, figsize=(10,10))
axarr[0].plot(L,err_N,axes=axes,color='red')
axarr[0].set_ylabel('$\delta N$')
axarr[1].plot(L,err_s,axes=axes,color='red')
axarr[1].set_ylabel('$\delta\sigma$')
axarr[2].scatter(L,s,axes=axes,color='blue')
axarr[2].set_ylabel('$\sigma$')
axarr[2].set_xlabel('Luminosity')



# <markdowncell>

# ### Binomial Distrubtion: $\sigma$ vs. p
# #### p = parameter that parametrizes Binomial Distribution p.d.f [p.d.f = f(x;N,p)]

# <codecell>

N = 100000; #number of independent trials
p = arange(0,0.5,0.01) #different probabilities for a trial to be successful
print p
err = sqrt(N*p*(1-p))
relerr = err/(N*p)
#print err
#plot(p,err)
plot(p,relerr)

# <codecell>

import ROOT
import numpy as np
import rootpy
rootpy.log.basic_config_colorized()
from rootpy.plotting import Hist, HistStack, Legend, Canvas
from rootpy.plotting.style import get_style, set_style
from rootpy.interactive import wait
import rootpy.plotting.root2matplotlib as rplt
import matplotlib.pyplot as plt
from matplotlib.ticker import AutoMinorLocator, MultipleLocator

# set the random seed
ROOT.gRandom.SetSeed(42)
np.random.seed(42)

# signal distribution
signal = 126 + 10 * np.random.randn(100)
signal_obs = 126 + 10 * np.random.randn(100)

# create histograms
h1 = Hist(30, 40, 200, title='Background', markersize=0)
h2 = h1.Clone(title='Signal')
h3 = h1.Clone(title='Data')
h3.markersize = 1.2

# fill the histograms with our distributions
h1.FillRandom('landau', 1000)
map(h2.Fill, signal)
h3.FillRandom('landau', 1000)
map(h3.Fill, signal_obs)

# set visual attributes
h1.fillstyle = 'solid'
h1.fillcolor = 'green'
h1.linecolor = 'green'
h1.linewidth = 0

h2.fillstyle = 'solid'
h2.fillcolor = 'red'
h2.linecolor = 'red'
h2.linewidth = 0

stack = HistStack()
stack.Add(h1)
stack.Add(h2)
plot_max = stack.GetMaximum() * 1.2
# hack to change y-axis range in ROOT
stack.SetMaximum(plot_max)

# plot with matplotlib
fig = plt.figure(figsize=(7, 5), dpi=100, facecolor='white')
axes = plt.axes([0.15, 0.15, 0.8, 0.8])
axes.xaxis.set_minor_locator(AutoMinorLocator())
axes.yaxis.set_minor_locator(AutoMinorLocator())
axes.yaxis.set_major_locator(MultipleLocator(20))
axes.tick_params(which='major', labelsize=15, length=8)
axes.tick_params(which='minor', length=4)
rplt.bar(stack, stacked=True, axes=axes)
rplt.errorbar(h3, xerr=False, emptybins=False, axes=axes)
plt.xlabel('Mass', position=(1., 0.), ha='right', size=16)
plt.ylabel('Events', position=(0., 1.), va='top', size=16)
axes.xaxis.set_label_coords(1., -0.12)
axes.yaxis.set_label_coords(-0.12, 1.)
axes.set_ylim(0, plot_max)
leg = plt.legend(numpoints=1)
frame = leg.get_frame()
frame.set_fill(False)
frame.set_linewidth(0)
axes.text(0.3, 0.8, 'matplotlib',
        verticalalignment='center', horizontalalignment='center',
        transform=axes.transAxes, fontsize=20)
if not ROOT.gROOT.IsBatch():
    plt.show()

# wait for you to close the canvas before exiting
wait(True)

# <codecell>

import rootpy.plotting.root2matplotlib as rplt
from rootpy.plotting import Hist
hn = Hist(10, 0, 10, title='test')
#hn.FillRandom('gaus',100)
hn.SetBinContent(1,4)
print hn.GetBinContent(1), hn.GetBinError(1)

figt = plt.figure(figsize=(7, 5), dpi=100, facecolor='white')
rplt.errorbar(hn)

# <codecell>


