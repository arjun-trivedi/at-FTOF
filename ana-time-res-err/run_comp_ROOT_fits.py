#!/usr/bin/python
import comp_ROOT_fits_v2 as tool

Nlow=range(100,500,20)
Nhigh=range(600,15000,500)
N=Nlow
N.extend(Nhigh)

#Nlow=range(100,500,300)
#N=Nlow

mu=190
for sg in [1,2,3,4]:
	for binw in [1,0.25]:
		for hist_range in ['exp','dflt']:
			for gen_hist_mthd in ['ROOTic','Pythonic']:
				tool.comp_ROOT_fits(mu,sg,N,binw,hist_range,gen_hist_mthd)

#mu,sg=190,2
#tool.comp_ROOT_fits(mu,sg,N,binw=1,hist_range="exp",gen_hist_mthd="ROOTic")
