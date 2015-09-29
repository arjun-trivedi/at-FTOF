#!/usr/bin/python
import comp_ROOT_fits_v2 as tool
import sys

#! N range estimated conservatively from N_stats/all
Nlow=range(50,500,20)
Nhigh=range(600,15000,500)
N=Nlow
N.extend(Nhigh)

#! N range for debugging
#Nlow=range(100,500,300)
#N=Nlow

mu=int(sys.argv[1])
sg=float(sys.argv[2])
binw=float(sys.argv[3])
hist_range=sys.argv[4]
gen_hist_mthd=sys.argv[5]

print "mem_hack_comp_ROOT_fits received: mu,sg,binw,hist_range,gen_hist_mthd=",mu,sg,binw,hist_range,gen_hist_mthd
tool.comp_ROOT_fits(mu,sg,N,binw,hist_range,gen_hist_mthd)
