#!/usr/bin/python
import comp_ROOT_fits_v2 as tool

from multiprocessing import Process, Queue
from subprocess import call
import os

#Nlow=range(100,500,20)
#Nhigh=range(600,15000,500)
#N=Nlow
#N.extend(Nhigh)

#Nlow=range(100,500,300)
#N=Nlow

#queue=Queue()
mu=190
for sg in [1.30,1.35,1.50,4.70,5.00]:#[1,2,3,4]:
	for binw in [1,0.25]:
		for hist_range in ['exp','dflt']:
			for gen_hist_mthd in ['ROOTic','Pythonic']:
				print "procesing comp_ROOT_fits for mu,sg,binw,hist_range,gen_hist_mthd=",mu,sg,binw,hist_range,gen_hist_mthd
				
				#p=Process(target=tool.comp_ROOT_fits, args=(mu,sg,N,binw,hist_range,gen_hist_mthd))#,queue))
				#p.start()
				#p.join() # this blocks until the process terminates
				#res=queue.get()
				#print "Result from tool.comp_ROOT_fits=",res

				#tool.comp_ROOT_fits(mu,sg,N,binw,hist_range,gen_hist_mthd)

				os.system("./hack.py %d %.2f %.2f %s %s"%(mu,sg,binw,hist_range,gen_hist_mthd))

#mu,sg=190,2
#tool.comp_ROOT_fits(mu,sg,N,binw=1,hist_range="exp",gen_hist_mthd="ROOTic")
