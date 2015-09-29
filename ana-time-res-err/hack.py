#!/usr/bin/python
import comp_ROOT_fits_v2 as tool
import sys

Nlow=range(100,500,20)
Nhigh=range(600,15000,500)
N=Nlow
N.extend(Nhigh)

#Nlow=range(100,500,300)
#N=Nlow

mu=int(sys.argv[1])
sg=float(sys.argv[2])
binw=float(sys.argv[3])
hist_range=sys.argv[4]
gen_hist_mthd=sys.argv[5]

print "hack received: mu,sg,binw,hist_range,gen_hist_mthd=",mu,sg,binw,hist_range,gen_hist_mthd
#sys.exit()
tool.comp_ROOT_fits(mu,sg,N,binw,hist_range,gen_hist_mthd)
