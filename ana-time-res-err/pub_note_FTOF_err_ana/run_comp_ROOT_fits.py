#!/usr/bin/python
#import comp_ROOT_fits_v2 as tool

from multiprocessing import Process, Queue
from subprocess import call
import os

"""
+ This script calls 'mem_hack_comp_ROOT_fits.py' to run each instance of comp_ROOT_fits_v2::comp_ROOT_fits() separately
+ This was done so because calling comp_ROOT_fits_v2::comp_ROOT_fits() for all parameters in one job was exhausting the memory

+ sg range = [1.25,5.30] =([25.51ps,108.18ps]) estimated from:
 (use pub_note_FTOF_err_ana/plot_17cm_407cm_T_hist.C to see the histograms)
	#! + low limit:  17cm/17cm_123456.root:res_1_2_3_point3_cont
		#! + RMS (zoomed in to exclude outlier)=1.376+/-0.0414. Therefore, low limit = 1.376-3*0.0414=1.25
	#! + high limit: 407cm/June06_407cm_123456_auto_new.root:res_1_2_3_point1_cont
		#! + RMS=4.59+/-0.2367. Therefore high limit=4.59+3*0.2367=5.30
"""
mu=190
for sg in [1.25,2.25,3.25,4.25,5.30]:#[1,2,3,4]:
	#!if sg!=1.25: continue #! debug
	for binw in [1,0.25]:
		#!if binw!=1: continue #! debug
		for hist_range in ['exp']:#!,'dflt']:
			for gen_hist_mthd in ['ROOTic']:#!,'Pythonic']:
				print "run_comp_ROOT_fits.py: Procesing comp_ROOT_fits for mu,sg,binw,hist_range,gen_hist_mthd=",mu,sg,binw,hist_range,gen_hist_mthd
				os.system("./mem_hack_comp_ROOT_fits.py %d %.2f %.2f %s %s"%(mu,sg,binw,hist_range,gen_hist_mthd))
