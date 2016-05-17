#!/usr/bin/python
from comp_ROOT_fits_v2 import CompROOTFits
import sys

#! N range estimated conservatively from N_stats/all
# Nlow=range(50,500,20)
# Nhigh=range(600,15000,500)
#! [05-17-16]
#! + This change for the N-range was prompter by the meeting feedback of [02-15-16] according to 
#!   which the two scales to be plotted on the xaxis are to be [50,500] and [1000,15000]
#! + Note that to accomodate [50,500], the number of points had to be reduced, which I hope does
#!   make any significant difference to the effect of the plots in communicating the message
Nlow=range(50,530,30)
Nhigh=range(1000,15500,500)
# Nlow=[10]#!range(50,100,20) #! debug
# Nhigh=[100]#!range(100,1000,500) #! debug
N=Nlow
N.extend(Nhigh)

mu=int(sys.argv[1])
sg=float(sys.argv[2])
binw=float(sys.argv[3])
hist_range=sys.argv[4]
gen_hist_mthd=sys.argv[5]

print "mem_hack_comp_ROOT_fits: Received: mu,sg,binw,hist_range,gen_hist_mthd=",mu,sg,binw,hist_range,gen_hist_mthd
tool=CompROOTFits(mu,sg,N,binw,hist_range,gen_hist_mthd)
tool.save_data_ROOT_fits() #! debug, in the sense, when only the plots needs to be refined using existing data
tool.plot_data_ROOT_fits()
