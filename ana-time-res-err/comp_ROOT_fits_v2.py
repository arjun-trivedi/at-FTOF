"""[01-18-15]
+ This program is used to compare the various options in ROOT to fit a Gassian histogram with the default option(=standard Chi-square fit(CSQ)).
+ The fit comparison for a Gaussian(MU,SG specified by user) are made at various N (=number of entries per histogram)
+ The process is as follows: 
	1. For each N, generate a number of Gaussian histograms(=n_trials) 
	2. Fit each histogram to OPT and CSQ(user specied option and the default option) and obtain fit statistics for each.
	3. Compare statistics as a function of N  

Keyword arguments:
MU -- mean of the Gaussian to be simulated
SG -- signa of the Gaussian to be simulated
N -- list of number of entries in the Gaussian histogram
ntrials -- Number of times the Gaussian histogram is to be Simulated and then Fit
fit_opt -- Fit option to be compared with the default CSQ option

"""
from __future__ import division
from math import *

import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

from collections import OrderedDict

#rootpy
from root_numpy import root2array, root2rec, tree2rec
from root_numpy.testdata import get_filepath
from rootpy.plotting import Hist2D, Hist
from rootpy.plotting import root2matplotlib as rplt
from rootpy.interactive import wait
#PyROOT
import ROOT

import os,sys

#! Set up TOF calibrations constant
TOF_CLB=sqrt(2/3)*25

def get_data(mthd,mu,sg,n,binw,hist_range,gen_hist_mthd,gen_data_rsltn,ntrials):
	#! Determine binning for T histogram
	if hist_range=="exp":
		xmin=-820
		xmax=1180
		nbins=int((xmax-xmin)/binw)
		h=Hist(nbins,xmin,xmax)
	elif hist_range=="dflt":
		xmin=int(mu-8*sg)
		xmax=int(mu+8*sg)
		nbins=int(round((xmax-xmin)/binw))
	print "binning for T histogram:nbins,xmin,xmax=(%d,%d,%d)"%(nbins,xmin,xmax)

	#! Start ntrials	
	#! lists to hold data from each trial
	mu_l,muerr_l,sg_l,sgerr_l=[],[],[],[]
	for i in range(ntrials):
		#! Create T histogram for this trial
		h=Hist(nbins,xmin,xmax)
		
		#! Fill T histogram
		if gen_hist_mthd=="ROOTic":
			for i in range(n):
				ROOT.gRandom.SetSeed(0)# Reset gRadom's seed to current machine clock
				h.Fill(ROOT.gRandom.Gaus(mu,sg))
		elif gen_hist_mthd=="Pythonic":
			d=np.random.normal(mu,sg,n)
			h.fill_array(d)
			
		#! Fit T histogram
		if   mthd=='CSQ': fit_opt="Q"
		elif mthd=='CSQWW': fit_opt="WWQ"
		elif mthd=='MLE': fit_opt="LQ"
		h.Fit("gaus",fit_opt)

		#! Get fit results
		f=h.GetFunction("gaus")
		mu_l.append(f.GetParameter(1))
		muerr_l.append(f.GetParError(1))
		sg_l.append(f.GetParameter(2))
		sgerr_l.append(f.GetParError(2))
	
	#! Now compute averages	
	mu_av=np.mean(mu_l)*TOF_CLB 
	mu_err_av=np.mean(muerr_l)*TOF_CLB
	#! NOTE the difference between mu_err_av and mu_av_err!
	mu_av_err=sqrt(sum([i**2 for i in muerr_l]))/len(muerr_l)*TOF_CLB

	sg_av=np.mean(sg_l)*TOF_CLB 
	sg_err_av=np.mean(sgerr_l)*TOF_CLB
	#! NOTE the difference between sg_err_av and sg_av_err!
	sg_av_err=sqrt(sum([i**2 for i in sgerr_l]))/len(sgerr_l)*TOF_CLB

	return [mu_av,mu_err_av,mu_av_err,sg_av,sg_err_av,sg_av_err]


def comp_ROOT_fits(mu,sg,N,binw,hist_range,gen_hist_mthd,gen_data_rsltn="",ntrials=500):
	"""
	Compare ROOT fit methods: CSQ,CSQWW and MLE

	Input:
	+ mu = mean of T histogram (uncalibrated)
	+ sg = RMS of T histogram (uncalibrated)
	+ N = List of number of entries to simulate; the comparison is done for each N in the list
	+ binw = 1 or 0.25
	+ hist_range= exp(=[-820,1180], based on res_1_2_3_pointX_cont) or dflt=[MU-8*SG,MU+8*SG]
	+ gen_hist_mthd= ROOTic i.e. using ROOT or Pythonic i.e. using python
	+ gen_data_rsltn: not implemented
	+ ntrials: Number of times a T histogram is generated and fit 
	"""
	
	#! Check to make sure that all input arguments are sound
	if binw!=1 and binw!=0.25:
		sys.exit("binw=1 or 0.25 only. Exiting.")

	if hist_range!="exp" and hist_range!="dflt":
		sys.exit("hist_range=exp or dflt only. Exiting.")
	
	if gen_hist_mthd!="ROOTic" and gen_hist_mthd!="Pythonic":
		sys.exit("gen_hist_mthd=ROOTic or Pythonic only. Exiting.")

	print "*** Comparing ROOT fits for mu,sg,binw,hist_range,gen_hist_mthd=",mu,sg,binw,hist_range,gen_hist_mthd,"***"
	#! set up mu and sg after calibration
	MU_TRUE=mu*TOF_CLB
	SG_TRUE=sg*TOF_CLB
	print "MU_TRUE,SG_TRUE=",MU_TRUE,SG_TRUE

	NMTHDS=3
	MTHDS=['CSQ','CSQWW','MLE']
	#CSQ,CSQWW,MLE=range(NMTHDS)

	#! data[MTHD,N]=mu_av,mu_err_av, mu_av_err,sg_av,sg_err_av, sg_av_err
	#! + The averages are calculated using data collected from ntrials
	#! + The data is TOF calibrated
	data=OrderedDict()
	#!For each (MTHD,N), get comparison data
	for mthd in MTHDS:
		data[mthd]=OrderedDict()
		for n in N:
			print "Getting data for (%s,N=%d)"%(mthd,n)
			data[mthd][n]=get_data(mthd,mu,sg,n,binw,hist_range,gen_hist_mthd,gen_data_rsltn,ntrials)
			#print "data=",data[mthd][n] 

	#! Dictionary to get data from data[mthd][n]
	MU_AV,MU_ERR_AV,MU_AV_ERR,SG_AV,SG_ERR_AV,SG_AV_ERR=range(6)

	fig,axs = plt.subplots(figsize=(20,8),nrows=2, ncols=2,sharex=True)
	#plt.rc('text', usetex=True)
	fig.suptitle(r'$\mu_{T}=%.2f(%d),\sigma_{T}=%.2f(%d)$'%(MU_TRUE,mu,SG_TRUE,sg),fontsize='xx-large')	
	x=range(len(data['CSQ']))
	#print x

	#! Plot mu/mu_T vs. N
	ax=axs[0][0]
	ax.set_title(r'$\frac{\Delta\mu}{\mu_{T}}$'
				 r' vs. N',fontsize='xx-large')
	y_csq=  [((data['CSQ'][n][MU_AV]-MU_TRUE)/MU_TRUE)*100 for n in data['CSQ']]
	y_csqww=[((data['CSQWW'][n][MU_AV]-MU_TRUE)/MU_TRUE)*100 for n in data['CSQWW']]
	y_mle=  [((data['MLE'][n][MU_AV]-MU_TRUE)/MU_TRUE)*100 for n in data['MLE']]
	yerr_csq=  [(data['CSQ'][n][MU_AV_ERR]/MU_TRUE)*100 for n in data['CSQ']]
	yerr_csqww=[(data['CSQWW'][n][MU_AV_ERR]/MU_TRUE)*100 for n in data['CSQWW']]
	yerr_mle=  [(data['MLE'][n][MU_AV_ERR]/MU_TRUE)*100 for n in data['MLE']]
	ax.errorbar(x,y_csq,c='r',label='fopt=CSQ',yerr=yerr_csq,fmt='o')
	ax.errorbar(x,y_csqww,c='b',label='fopt=CSQWW',yerr=yerr_csqww,fmt='o')
	ax.errorbar(x,y_mle,c='g',label='fopt=MLE',yerr=yerr_mle,fmt='o')
	ax.set_ylabel(r'$\frac{\Delta\mu}{\mu_{T}}\%$',fontsize='xx-large')
	ax.set_xticks(x)
	ax.set_xticklabels(N,rotation='vertical')
	ax.hlines(0,ax.get_xlim()[0],ax.get_xlim()[1])
	ax.legend(loc='upper right')
	#! Fix x axis
	# shift half a step to the left
	xmin=(3*x[0]-x[1])/2.
	# shift half a step to the right
	xmax=(3*x[-1]-x[-2])/2.
	ax.set_xlim(xmin,xmax)
	ax.hlines(0,ax.get_xlim()[0],ax.get_xlim()[1])

	#! Plot sg/sg_T vs. N
	ax=axs[0][1]
	ax.set_title(r'$\frac{\Delta\sigma}{\sigma_{T}}$'
				 r' vs. N',fontsize='xx-large')
	y_csq=  [((data['CSQ'][n][SG_AV]-SG_TRUE)/SG_TRUE)*100 for n in data['CSQ']]
	y_csqww=[((data['CSQWW'][n][SG_AV]-SG_TRUE)/SG_TRUE)*100 for n in data['CSQWW']]
	y_mle=  [((data['MLE'][n][SG_AV]-SG_TRUE)/SG_TRUE)*100 for n in data['MLE']]
	yerr_csq=  [(data['CSQ'][n][SG_AV_ERR]/SG_TRUE)*100 for n in data['CSQ']]
	yerr_csqww=[(data['CSQWW'][n][SG_AV_ERR]/SG_TRUE)*100 for n in data['CSQWW']]
	yerr_mle=  [(data['MLE'][n][SG_AV_ERR]/SG_TRUE)*100 for n in data['MLE']]
	ax.errorbar(x,y_csq,c='r',label='fopt=CSQ',yerr=yerr_csq,fmt='o')
	ax.errorbar(x,y_csqww,c='b',label='fopt=CSQWW',yerr=yerr_csqww,fmt='o')
	ax.errorbar(x,y_mle,c='g',label='fopt=MLE',yerr=yerr_mle,fmt='o')
	ax.set_ylim(-5,5)
	ax.set_ylabel(r'$\frac{\Delta\sigma}{\sigma_{T}}\%$',fontsize='xx-large')          
	ax.set_xticks(x)
	ax.set_xticklabels(N,rotation='vertical')
	ax.hlines(0,ax.get_xlim()[0],ax.get_xlim()[1])
	ax.legend(loc='lower right')
	#! Fix x axis
	# shift half a step to the left
	xmin=(3*x[0]-x[1])/2.
	# shift half a step to the right
	xmax=(3*x[-1]-x[-2])/2.
	ax.set_xlim(xmin,xmax)

	#! Plot error on estimated mu
	ax=axs[1][0]
	ax.set_title(r'$\frac{\sigma_{\mu}}{\mu}$'
				 r' vs. N',fontsize='xx-large')
	y_csq=  [(data['CSQ'][n][MU_ERR_AV]/data['CSQ'][n][MU_AV])*100 for n in data['CSQ']]
	y_csqww=[(data['CSQWW'][n][MU_ERR_AV]/data['CSQWW'][n][MU_AV])*100 for n in data['CSQWW']]
	y_mle=  [(data['MLE'][n][MU_ERR_AV]/data['MLE'][n][MU_AV])*100 for n in data['MLE']]
	ax.scatter(x,y_csq,c='r',label='fopt=CSQ',s=50)
	ax.scatter(x,y_csqww,c='b',label='fopt=CSQWW',s=50)
	ax.scatter(x,y_mle,c='g',label='fopt=MLE',s=50)
	ax.set_ylabel(r'$\frac{\sigma_{\mu}}{\mu}\%$',fontsize='xx-large')
	ax.set_xticks(x)
	ax.set_xticklabels(N,rotation='vertical')
	ax.legend(loc='upper right')
	#! Fix x axis
	# shift half a step to the left
	xmin=(3*x[0]-x[1])/2.
	# shift half a step to the right
	xmax=(3*x[-1]-x[-2])/2.
	ax.set_xlim(xmin,xmax)

	#! Plot error on estimated sigma
	ax=axs[1][1]
	ax.set_title(r'$\frac{\sigma_{\sigma}}{\sigma}$'
				 r' vs. N',fontsize='xx-large')
	y_csq=  [(data['CSQ'][n][SG_ERR_AV]/data['CSQ'][n][SG_AV])*100 for n in data['CSQ']]
	y_csqww=[(data['CSQWW'][n][SG_ERR_AV]/data['CSQWW'][n][SG_AV])*100 for n in data['CSQWW']]
	y_mle=  [(data['MLE'][n][SG_ERR_AV]/data['MLE'][n][SG_AV])*100 for n in data['MLE']]
	ax.scatter(x,y_csq,c='r',label='fopt=CSQ',s=50)
	ax.scatter(x,y_csqww,c='b',label='fopt=CSQWW',s=50)
	ax.scatter(x,y_mle,c='g',label='fopt=MLE',s=50)
	ax.set_ylabel(r'$\frac{\sigma_{\sigma}}{\sigma}\%$',fontsize='xx-large')
	ax.set_xticks(x)
	ax.set_xticklabels(N,rotation='vertical')
	ax.legend(loc='upper right')
	#! Fix x axis
	# shift half a step to the left
	xmin=(3*x[0]-x[1])/2.
	# shift half a step to the right
	xmax=(3*x[-1]-x[-2])/2.
	ax.set_xlim(xmin,xmax)
	
	fig_name="fit-comp_mu-%d_sg-%d_binw-%.2f_hist_range-%s_gen_hist_mthd-%s"%(mu,sg,binw,hist_range,gen_hist_mthd)
	fig.savefig("/tmp/%s.png"%(fig_name))
	fig.savefig("/tmp/%s.eps"%(fig_name))

	print "******\n"

	
