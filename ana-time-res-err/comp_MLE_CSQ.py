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


def get_comp_data(MU,SG,n_hist_entries,n_trials,fit_opt_CSQ,binw):
	CSQ,MLE=range(2)
	mu,sg,csq=[[],[]],[[],[]],[[],[]]
	muerr,sgerr=[[],[]],[[],[]]
	for i in range(n_trials):
		d=np.random.normal(MU,SG,n_hist_entries)
		h=[[],[]]
		xmin=int(MU-8*SG)
		xmax=int(MU+8*SG)
		bins=int(round((xmax-xmin)/binw))
		#print "DEBUG bins=",bins
		#chsq fit
		h[CSQ]=Hist(bins,xmin,xmax)
		h[CSQ].fill_array(d)
		h[CSQ].Fit("gaus","%s"%fit_opt_CSQ)
		f=h[CSQ].GetFunction("gaus")
		mu[CSQ].append(f.GetParameter(1))
		sg[CSQ].append(f.GetParameter(2))
		muerr[CSQ].append(f.GetParError(1))
		sgerr[CSQ].append(f.GetParError(2))
		csq[CSQ].append(f.GetChisquare())
		#MLE fit
		h[MLE]=Hist(bins,xmin,xmax)
		h[MLE].fill_array(d)
		h[MLE].Fit("gaus","L")
		f=h[MLE].GetFunction("gaus")
		mu[MLE].append(f.GetParameter(1))
		sg[MLE].append(f.GetParameter(2))
		muerr[MLE].append(f.GetParError(1))
		sgerr[MLE].append(f.GetParError(2))
		csq[MLE].append(f.GetChisquare())
	# fig=plt.figure(figsize=(15,5))
	# plt.subplot(131)
	# xmin=round(MU-6*(SG/(sqrt(n_hist_entries))))
	# xmax=round(MU+6*(SG/(sqrt(n_hist_entries))))
	# bins=30
	# plt.hist(mu[CSQ],label="CSQ-fit",alpha=0.5,bins=bins,range=[xmin,xmax])
	# plt.hist(mu[MLE],label="MLE-fit",alpha=0.5,bins=bins,range=[xmin,xmax])
	# plt.legend()
	# plt.subplot(132)
	# xmin=round(SG-6*(SG/(sqrt(n_hist_entries))))
	# xmax=round(SG+6*(SG/(sqrt(n_hist_entries))))
	# bins=30
	# plt.hist(sg[CSQ],label="CSQ-fit",alpha=0.5,bins=bins,range=[xmin,xmax])
	# plt.hist(sg[MLE],label="MLE-fit",alpha=0.5,bins=bins,range=[xmin,xmax])
	# plt.legend()
	return mu[CSQ],muerr[CSQ],mu[MLE],muerr[MLE],sg[CSQ],sgerr[CSQ],sg[MLE],sgerr[MLE]


def run(MU,SG,N,NTRIALS,fit_opt_CSQ="",tof_calib=True,binw=1):
	MU_CSQ,MUERR_CSQ,MU_MLE,MUERR_MLE,SG_CSQ,SGERR_CSQ,SG_MLE,SGERR_MLE=range(8)
	data=OrderedDict()
	#For each N, get comparison data
	for i in N:
		#print i
		data['n=%d'%i]=get_comp_data(MU,SG,i,NTRIALS,fit_opt_CSQ,binw)  

	#! From data, extract and plot comparison data
	CSQ,MLE=range(2)
	mu_av=[[],[]]
	sg_av=[[],[]]
	mu_av_err=[[],[]]
	sg_av_err=[[],[]]
	#! NOTE the difference between xx_av_err vs. xx_err_av!
	mu_err_av=[[],[]]
	sg_err_av=[[],[]]
	n=[]
	clb=1 # Calibration constant
	if tof_calib:
		clb=sqrt(2/3)*25
	for k in data.keys():
		#print k
		mu_av[CSQ].append( np.mean(data[k][MU_CSQ])*clb )
		mu_av[MLE].append( np.mean(data[k][MU_MLE])*clb )
		mu_av_err[CSQ].append( sqrt(sum([i**2 for i in data[k][MUERR_CSQ]]))/len(data[k][MUERR_CSQ])*clb )
		mu_av_err[MLE].append( sqrt(sum([i**2 for i in data[k][MUERR_MLE]]))/len(data[k][MUERR_MLE])*clb )
		#! NOTE the difference between xx_av_err vs. xx_err_av!
		mu_err_av[CSQ].append( np.mean(data[k][MUERR_CSQ])*clb )
		mu_err_av[MLE].append( np.mean(data[k][MUERR_MLE])*clb )

		sg_av[CSQ].append(np.mean(data[k][SG_CSQ])*clb)
		sg_av[MLE].append(np.mean(data[k][SG_MLE])*clb)
		sg_av_err[CSQ].append( (sqrt(sum([i**2 for i in data[k][SGERR_CSQ]]))/len(data[k][SGERR_CSQ]))*clb )
		sg_av_err[MLE].append( (sqrt(sum([i**2 for i in data[k][SGERR_MLE]]))/len(data[k][SGERR_MLE]))*clb )
		#! NOTE the difference between xx_av_err vs. xx_err_av!
		sg_err_av[CSQ].append( np.mean(data[k][SGERR_CSQ])*clb)
		sg_err_av[MLE].append( np.mean(data[k][SGERR_MLE])*clb)
		n.append(k)

	fig,axs = plt.subplots(figsize=(20,8),nrows=2, ncols=2,sharex=True)
	x=range(len(mu_av[CSQ]))

	ax=axs[0][0]
	ax.set_title("<#mu> vs. n")
	#ax=plt.scatter(x,mu_av[CSQ],c='r',label='CSQ-fit')
	#ax=plt.scatter(x,mu_av[MLE],c='b',label='MLE-fit')
	ax.errorbar(x,mu_av[CSQ],c='r',label='CSQ-fit',yerr=mu_av_err[CSQ],fmt='o')
	ax.errorbar(x,mu_av[MLE],c='b',label='MLE-fit',yerr=mu_av_err[MLE],fmt='o')
	if tof_calib:ax.set_ylabel("<#mu> [ps]")
	else:ax.set_ylabel("<#mu>")
	ax.set_xticks(x)
	ax.set_xticklabels(n,rotation='vertical')
	ax.hlines(MU*clb,ax.get_xlim()[0],ax.get_xlim()[1])
	ax.legend(loc='upper right')

	ax=axs[0][1]
	ax.set_title("<#sg> vs. n")
	# ax=plt.scatter(x,sg_av[CSQ],c='r',label='CSQ-fit')
	# ax=plt.scatter(x,sg_av[MLE],c='b',label='MLE-fit')
	ax.errorbar(x,sg_av[CSQ],c='r',label='CSQ-fit',yerr=sg_av_err[CSQ],fmt='o')
	ax.errorbar(x,sg_av[MLE],c='b',label='MLE-fit',yerr=sg_av_err[MLE],fmt='o')
	if tof_calib:ax.set_ylabel("<#sg> [ps]")
	else:ax.set_ylabel("<#sg>")          
	ax.set_xticks(x)
	ax.set_xticklabels(n,rotation='vertical')
	ax.hlines(SG*clb,ax.get_xlim()[0],ax.get_xlim()[1])
	ax.legend(loc='lower right')

	ax=axs[1][0]
	ax.set_title("<#mu-err> vs. n")
	ax.scatter(x,mu_err_av[CSQ],c='r',label='CSQ-fit')
	ax.scatter(x,mu_err_av[MLE],c='b',label='MLE-fit')
	if tof_calib:ax.set_ylabel("<#mu-err> [ps]")
	else:ax.set_ylabel("<#mu-err>")
	ax.set_xticks(x)
	ax.set_xticklabels(n,rotation='vertical')
	ax.legend(loc='upper right')

	ax=axs[1][1]
	ax.set_title("<#sg-err> vs. n")
	ax.scatter(x,sg_err_av[CSQ],c='r',label='CSQ-fit')
	ax.scatter(x,sg_err_av[MLE],c='b',label='MLE-fit')
	if tof_calib:ax.set_ylabel("<#sg-err> [ps]")
	else:ax.set_ylabel("<#sg-err>")
	ax.set_xticks(x)
	ax.set_xticklabels(n,rotation='vertical')
	ax.legend(loc='upper right')