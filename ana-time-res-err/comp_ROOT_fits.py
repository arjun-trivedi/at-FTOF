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
NTRIALS -- Number of times the Gaussian histogram is to be Simulated and then Fit
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

import os


def get_comp_data(MU,SG,N,NTRIALS,fit_opt,binw):
	OPT,CSQ=range(2)
	mu,sg,csq=[[],[]],[[],[]],[[],[]]
	muerr,sgerr=[[],[]],[[],[]]
	for i in range(NTRIALS):
		d=np.random.normal(MU,SG,N)
		h=[[],[]]
		xmin=int(MU-8*SG)
		xmax=int(MU+8*SG)
		bins=int(round((xmax-xmin)/binw))
		#print "DEBUG bins=",bins
		#OPT fit
		h[OPT]=Hist(bins,xmin,xmax)
		h[OPT].fill_array(d)
		h[OPT].Fit("gaus","%s"%fit_opt)
		f=h[OPT].GetFunction("gaus")
		mu[OPT].append(f.GetParameter(1))
		sg[OPT].append(f.GetParameter(2))
		muerr[OPT].append(f.GetParError(1))
		sgerr[OPT].append(f.GetParError(2))
		csq[OPT].append(f.GetChisquare())
		#CSQ fit
		h[CSQ]=Hist(bins,xmin,xmax)
		h[CSQ].fill_array(d)
		h[CSQ].Fit("gaus")
		f=h[CSQ].GetFunction("gaus")
		mu[CSQ].append(f.GetParameter(1))
		sg[CSQ].append(f.GetParameter(2))
		muerr[CSQ].append(f.GetParError(1))
		sgerr[CSQ].append(f.GetParError(2))
		csq[CSQ].append(f.GetChisquare())
	return mu[OPT],muerr[OPT],mu[CSQ],muerr[CSQ],sg[OPT],sgerr[OPT],sg[CSQ],sgerr[CSQ]


def run(MU,SG,N,NTRIALS,fit_opt="",tof_calib=True,binw=1):
	#! Set up TOF calibrations constant
	TOF_CLB=1 # Calibration constant
	if tof_calib:
		TOF_CLB=sqrt(2/3)*25

	#! set up mu and sg after calibration
	MU_TRUE=MU*TOF_CLB
	SG_TRUE=SG*TOF_CLB

	data=OrderedDict()
	#!For each N, get comparison data
	for n in N:
		#print i
		data['N=%d'%n]=get_comp_data(MU,SG,n,NTRIALS,fit_opt,binw)  

	#! From data, extract and plot comparison data
	#! First define index to obtain data (as per return value of get_comp_data())
	MU_OPT,MUERR_OPT,MU_CSQ,MUERR_CSQ,SG_OPT,SGERR_OPT,SG_CSQ,SGERR_CSQ=range(8)
	OPT,CSQ=range(2)
	mu_av=[[],[]]
	sg_av=[[],[]]
	mu_av_err=[[],[]]
	sg_av_err=[[],[]]
	#! NOTE the difference between xx_av_err vs. xx_err_av!
	mu_err_av=[[],[]]
	sg_err_av=[[],[]]
	N=[]
	for k in data.keys():
		#print k
		mu_av[OPT].append( np.mean(data[k][MU_OPT])*TOF_CLB )
		mu_av[CSQ].append( np.mean(data[k][MU_CSQ])*TOF_CLB )
		mu_av_err[OPT].append( sqrt(sum([i**2 for i in data[k][MUERR_OPT]]))/len(data[k][MUERR_OPT])*TOF_CLB )
		mu_av_err[CSQ].append( sqrt(sum([i**2 for i in data[k][MUERR_CSQ]]))/len(data[k][MUERR_CSQ])*TOF_CLB )
		#! NOTE the difference between xx_av_err vs. xx_err_av!
		mu_err_av[OPT].append( np.mean(data[k][MUERR_OPT])*TOF_CLB )
		mu_err_av[CSQ].append( np.mean(data[k][MUERR_CSQ])*TOF_CLB )

		sg_av[OPT].append(np.mean(data[k][SG_OPT])*TOF_CLB)
		sg_av[CSQ].append(np.mean(data[k][SG_CSQ])*TOF_CLB)
		sg_av_err[OPT].append( (sqrt(sum([i**2 for i in data[k][SGERR_OPT]]))/len(data[k][SGERR_OPT]))*TOF_CLB )
		sg_av_err[CSQ].append( (sqrt(sum([i**2 for i in data[k][SGERR_CSQ]]))/len(data[k][SGERR_CSQ]))*TOF_CLB )
		#! NOTE the difference between xx_av_err vs. xx_err_av!
		sg_err_av[OPT].append( np.mean(data[k][SGERR_OPT])*TOF_CLB)
		sg_err_av[CSQ].append( np.mean(data[k][SGERR_CSQ])*TOF_CLB)
		N.append(k)

	fig,axs = plt.subplots(figsize=(20,8),nrows=2, ncols=2,sharex=True)
	#plt.rc('text', usetex=True)

	fig.suptitle(r'$\mu_{T}=%.2f(%d),\sigma_{T}=%.2f(%d)$'%(MU_TRUE,MU,SG_TRUE,SG),fontsize='xx-large')	
	x=range(len(mu_av[OPT]))

	#! Plot mu/mu_T vs. N
	ax=axs[0][0]
	ax.set_title(r'$\frac{\mu}{\mu_{T}}$'
				 r' vs. N',fontsize='xx-large')
	y_opt=[((z-MU_TRUE)/MU_TRUE)*100 for z in mu_av[OPT]]
	y_csq=[((z-MU_TRUE)/MU_TRUE)*100 for z in mu_av[CSQ]]
	yerr_opt=[(z/MU_TRUE)*100 for z in mu_av_err[OPT]]
	yerr_csq=[(z/MU_TRUE)*100 for z in mu_av_err[CSQ]]
	ax.errorbar(x,y_opt,c='r',label='fopt="%s"'%fit_opt,yerr=yerr_opt,fmt='o')
	ax.errorbar(x,y_csq,c='b',label='fopt=""',          yerr=yerr_csq,fmt='o')
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

	#! Plot sg/sg_T vs. N
	ax=axs[0][1]
	ax.set_title(r'$\frac{\sigma}{\sigma_{T}}$'
				 r' vs. N',fontsize='xx-large')
	y_opt=[((z-SG_TRUE)/SG_TRUE)*100 for z in sg_av[OPT]]
	y_csq=[((z-SG_TRUE)/SG_TRUE)*100 for z in sg_av[CSQ]]
	yerr_opt=[(z/SG_TRUE)*100 for z in sg_av_err[OPT]]
	yerr_csq=[(z/SG_TRUE)*100 for z in sg_av_err[CSQ]]
	ax.errorbar(x,y_opt,c='r',label='fopt="%s"'%fit_opt,yerr=yerr_opt,fmt='o')
	ax.errorbar(x,y_csq,c='b',label='fopt=""',          yerr=yerr_csq,fmt='o')
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
	y_opt=[(z[0]/z[1])*100 for z in zip(mu_err_av[OPT],mu_av[OPT])]
	y_csq=[(z[0]/z[1])*100 for z in zip(mu_err_av[CSQ],mu_av[CSQ])]
	ax.scatter(x,y_opt,c='r',label='fopt="%s"'%fit_opt,s=50)
	ax.scatter(x,y_csq,c='b',label='fopt=""',s=50)
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
	y_opt=[(z[0]/z[1])*100 for z in zip(sg_err_av[OPT],sg_av[OPT])]
	y_csq=[(z[0]/z[1])*100 for z in zip(sg_err_av[CSQ],sg_av[CSQ])]
	ax.scatter(x,y_opt,c='r',label='fopt="%s"'%fit_opt,s=50)
	ax.scatter(x,y_csq,c='b',label='fopt=""',s=50)
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
	
	fig.savefig("fit-comp_MU-%d_SG-%d_fit-opt-%s_binw-%.2f.png"%(MU,SG,fit_opt,binw))
	fig.savefig("fit-comp_MU-%d_SG-%d_fit-opt-%s_binw-%.2f.eps"%(MU,SG,fit_opt,binw))
