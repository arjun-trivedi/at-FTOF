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

from multiprocessing import Process, Queue


#! Set up TOF calibrations constant
TOF_CLB=sqrt(2/3)*25

NMTHDS=3
MTHDS=['CSQ','CSQ-WW','MLE']

def get_simulation_data(mthd,mu,sg,n,binw,hist_range,gen_hist_mthd,gen_data_rsltn,ntrials):
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
		elif mthd=='CSQ-WW': fit_opt="WWQ"
		elif mthd=='MLE': fit_opt="LQ"
		h.Fit("gaus",fit_opt)

		#! Get fit results
		f=h.GetFunction("gaus")
		mu_l.append(f.GetParameter(1))
		muerr_l.append(f.GetParError(1))
		sg_l.append(f.GetParameter(2))
		sgerr_l.append(f.GetParError(2))
	
	#! Now compute averages	
	#! Set 1.
	mu_av=np.mean(mu_l)*TOF_CLB 
	mu_err_av=np.mean(muerr_l)*TOF_CLB
	#! NOTE the difference between mu_err_av and mu_av_err!
	mu_av_err=sqrt(sum([i**2 for i in muerr_l]))/len(muerr_l)*TOF_CLB

	sg_av=np.mean(sg_l)*TOF_CLB 
	sg_err_av=np.mean(sgerr_l)*TOF_CLB
	#! NOTE the difference between sg_err_av and sg_av_err!
	sg_av_err=sqrt(sum([i**2 for i in sgerr_l]))/len(sgerr_l)*TOF_CLB
	#! Set 2.
	sg_rms_err=np.std(sg_l)*TOF_CLB

	return [mu_av,mu_err_av,mu_av_err,sg_av,sg_err_av,sg_av_err,sg_rms_err]

class CompROOTFits:
	def __init__(self,mu,sg,N,binw,hist_range,gen_hist_mthd,gen_data_rsltn="",ntrials=500):
		"""
		+ This class is used to compare various fitting methods in ROOT. The following is the general procedure:

		1. The user inputs the true paramaters for a Gaussian distribution, mu_true,sg_true, and a range of N values 
		   which are the number of entries in this distribution.

		2. This class then simulates a fixed number (ntrials=500) of Gaussian-histogram data for each N value in the range.
		   2.i.  Histrograms from each of these trials are fitted using the different methods in ROOT and for each method the estimated
		         parameters and their errors are noted.
		   2.ii. "Various averages" of these estimated parameters are computed and saved to a file. 

		3. These "various averages" are then plotted as a function of mu_true,sg_true and {N} for every ROOT method.

		The following is a technical description:
		For a given mu_true,sg_true,{N} obtain for each of the fit methods in ROOT:
		1. {mu,sg,sg_mu,sg_sg}: estimated parameters and the estimated error on them from the fits

		2. 'data[mthd][N]': "Various averages" of the above data, where the "various averages" are:
			+ Set 1 (i.e. those that I determined to be useful):
				i.   mu_av     = <mu>
				ii.  mu_err_av = <sg_mu>
				iii. mu_av_err = Error in calculating <mu> using 'sg_mu' in the standard error propagation formula
				iv.  sg_av     = <sg>
				v.   sg_err_av = <sg_sg>
				vi.  sg_av_err = Error in calculating <sg> using 'sg_sg' in the standard error propagation formula
			+ Set 2 (i.e. those that were later requested):
				vii. sg_rms_err = Arithmetically determined RMS-error on 'sg'.
				+ Needed by Gary to verify if the fit estimated error on the estimated sigma is "true". 
				+ If "true", then this equation should be true: 'sg_err_av' (v) = 'sg_rms_err' (vii)


		3. Write 'data[mthd][N]' to file
		4. Obtain 'data[mthd][N]' from and plot

		Input:
		+ mu = mean of T histogram (uncalibrated i.e. in raw TDC units)
		+ sg = RMS of T histogram (uncalibrated i.e. in raw TDC units)
		+ N = List of number of entries to simulate; the comparison is done for each N in the list
		+ binw = 1 or 0.25
		+ hist_range= exp(=[-820,1180], based on res_1_2_3_pointX_cont) or dflt=[MU-8*SG,MU+8*SG]
		+ gen_hist_mthd= ROOTic i.e. using ROOT or Pythonic i.e. using python
		+ gen_data_rsltn: not implemented
		+ ntrials: Number of times a T histogram is generated and fit 
		"""
		print "In CompROOTFits::__init__()"

		#! Get user arguments
		self.MU=mu
		self.SG=sg
		self.N=N
		self.BINW=binw
		self.HIST_RANGE=hist_range
		self.GEN_HIST_MTHD=gen_hist_mthd
		self.GEN_DATA_RSLTN=gen_data_rsltn
		self.NTRIALS=ntrials

		#! Check to make sure that all input arguments are sound
		if self.BINW!=1 and self.BINW!=0.25:
			sys.exit("binw=1 or 0.25 only. Exiting.")

		if self.HIST_RANGE!="exp" and self.HIST_RANGE!="dflt":
			sys.exit("hist_range=exp or dflt only. Exiting.")
	
		if self.GEN_HIST_MTHD!="ROOTic" and self.GEN_HIST_MTHD!="Pythonic":
			sys.exit("gen_hist_mthd=ROOTic or Pythonic only. Exiting.")

		print "*** Comparing ROOT fits for MU,SG,BINW,HIST_RANGE,GEN_HIST_MTHD=",self.MU,self.SG,self.BINW,self.HIST_RANGE,self.GEN_HIST_MTHD,"***"
		#! set up mu and sg after calibration
		self.MU_TRUE=self.MU*TOF_CLB
		self.SG_TRUE=self.SG*TOF_CLB
		print "self.MU_TRUE,self.SG_TRUE=",self.MU_TRUE,self.SG_TRUE

		#! Create OUTDIR
		self.OUTDIR=("%s/at-FTOF/ana-time-res-err/pub_note_FTOF_err_ana/data_comp_ROOT_fits"%os.environ['WORKSPACE'])
		if not os.path.exists(self.OUTDIR):
			os.makedirs(self.OUTDIR)	
		#! Declare name of output file where data is saved
		#! Don't tag data_file name with 'hist_range'(=exp/dflt) and 'gen_hist_mthd'(=ROOTic/Pythonic) anymore since
		#! those options make no difference (even though they are still passed in arguments, for just-in-case) 
		#! self.FOUT_DATA_NAME="mu-%d_sg-%.2f_binw-%.2f_hist_range-%s_gen_hist_mthd-%s.txt"%(mu,sg,binw,hist_range,gen_hist_mthd)
		self.FOUT_DATA_NAME="mu-%d_sg-%.2f_binw-%.2f.txt"%(self.MU,self.SG,self.BINW)
		
		print "Done CompROOTFits::__init__()"



	def save_data_ROOT_fits(self):#,que=None):

		print "In CompROOTFits::save_data_ROOT_fits()"

		self.FOUT_DATA=open("%s/%s"%(self.OUTDIR,self.FOUT_DATA_NAME),"w")

		#! Dictionary to get data from data[mthd][n]
		MU_AV,MU_ERR_AV,MU_AV_ERR,SG_AV,SG_ERR_AV,SG_AV_ERR,SG_RMS_ERR=range(7)
 	
		#! data[MTHD,N]=mu_av,mu_err_av, mu_av_err,sg_av,sg_err_av, sg_av_err
		#! + The averages are calculated using data collected from ntrials
		#! + The data is TOF calibrated
		data=OrderedDict()
		#!For each (MTHD,N), get comparison data
		for mthd in MTHDS:
			data[mthd]=OrderedDict()
			for n in self.N:
				print "Getting simulation data for (%s,N=%d)"%(mthd,n)
				data[mthd][n]=get_simulation_data(mthd,self.MU,self.SG,n,self.BINW,self.HIST_RANGE,self.GEN_HIST_MTHD,self.GEN_DATA_RSLTN,self.NTRIALS)
				#print "data=",data[mthd][n] 

		#! Write this comparison data
		for mthd in data.keys():
			for n in data[mthd].keys():
				#! Set 1.
				mu_av    =data[mthd][n][MU_AV]
				mu_err_av=data[mthd][n][MU_ERR_AV]
				mu_av_err=data[mthd][n][MU_AV_ERR]
				sg_av    =data[mthd][n][SG_AV]
				sg_err_av=data[mthd][n][SG_ERR_AV]
				sg_av_err=data[mthd][n][SG_AV_ERR]
				#! Set 2.
				sg_rms_err=data[mthd][n][SG_RMS_ERR]
				#! Write to file
				self.FOUT_DATA.write("%s %d %f %f %f %f %f %f %f\n"%(mthd,n,mu_av,mu_err_av,mu_av_err,sg_av,sg_err_av,sg_av_err,sg_rms_err))

		#! Close this file
		self.FOUT_DATA.close()
		print "In CompROOTFits::save_data_ROOT_fits()"
		return 0
		

	def get_data_from_file(self):
	
		print "In CompROOTFits::get_data_from_file()"

		#! Get data[MTHD,N] from file
		#! data[MTHD,N]=mu_av,mu_err_av, mu_av_err,sg_av,sg_err_av, sg_av_err
		#! + The averages are calculated using data collected from ntrials
		#! + The data is TOF calibrated
		data=OrderedDict()
		#!For each (MTHD,N), get comparison data
		for mthd in MTHDS:
			data[mthd]=OrderedDict()

		#! Dictionary to get data from file
		MTHD,N,MU_AV,MU_ERR_AV,MU_AV_ERR,SG_AV,SG_ERR_AV,SG_AV_ERR,SG_RMS_ERR=range(9)

		file_data=self.FOUT_DATA.readlines()
		print "file_data=",file_data
		for line in file_data:
			words=line.split()
			print "words=",words
			mthd=     words[MTHD]
			n=        int(words[N])
			#! Set 1.
			mu_av=    float(words[MU_AV])
			mu_err_av=float(words[MU_ERR_AV])
			mu_av_err=float(words[MU_AV_ERR])
			sg_av=    float(words[SG_AV])
			sg_err_av=float(words[SG_ERR_AV])
			sg_av_err=float(words[SG_AV_ERR])
			#! Set 2.
			sg_rms_err=float(words[SG_RMS_ERR])
			print "mthd,n,mu_av,mu_err_av,mu_av_err,sg_av,sg_err_av,sg_av_err,sg_rms_err=",mthd,n,mu_av,mu_err_av,mu_av_err,sg_av,sg_err_av,sg_av_err,sg_rms_err
			data[mthd][n]=[mu_av,mu_err_av,mu_av_err,sg_av,sg_err_av,sg_av_err,sg_rms_err]
	
		print "Done CompROOTFits::get_data_from_file()"
		return data
		

	def plot_data_ROOT_fits(self):#,que=None):
		
		print "In CompROOTFits::plot_data_ROOT_fits()"

		#! Open file to read data
		self.FOUT_DATA=open("%s/%s"%(self.OUTDIR,self.FOUT_DATA_NAME),"r")
		print "FOUT_DATA=",self.FOUT_DATA.name

		#! Get data[MTHD,N] from file
		data=self.get_data_from_file()
		#! Close file
		self.FOUT_DATA.close()
			
		#! Dictionary to get data from data[mthd][n]
		MU_AV,MU_ERR_AV,MU_AV_ERR,SG_AV,SG_ERR_AV,SG_AV_ERR=range(6)

		#! Set up some plotting-aesthetic related constants
		#! Set dimensions of the figure
		if self.SG==1.25: #! Give more size since it being the "left most" plot in the pub contains the title on the side
			fig_size_x=12
			fig_size_y=20
		else:
			fig_size_x=8
			fig_size_y=20
		#! Aesthetics for the plots on this figure
		#! Set location of each plot's title
		plot_title_loc_x=-0.14
		plot_title_loc_y=0.68


		#!fig,axs = plt.subplots(figsize=(20,8),nrows=2, ncols=2,sharex=True)
		fig,axs = plt.subplots(figsize=(fig_size_x,fig_size_y),nrows=4, ncols=1,sharex=True)
		fig.suptitle(r'$\mu_{true}=%.2f ps \ \sigma_{true}=%.2f ps$'%(self.MU_TRUE,self.SG_TRUE),fontsize='xx-large')	
		x=range(len(data['CSQ']))
		#print x

		#! Plot mu/mu_T versus N
		#! new layout
		#! ax=axs[0][0]
		ax=axs[0]#![0]
		# ax.set_title(r'$\frac{\Delta\mu}{\mu_{true}}$'
		# 			 r' versus N',fontsize='xx-large')
		if self.SG==1.25: #! Draw title only for "left most column" of fig in nim-pub
			ax.set_title(r'$\Delta\mu/\mu_{true}$'
						 r' versus N',fontsize='xx-large',x=plot_title_loc_x,y=plot_title_loc_y,rotation='vertical')
		y_csq=  [((data['CSQ'][n][MU_AV]-self.MU_TRUE)/self.MU_TRUE)*100 for n in data['CSQ']]
		y_csqww=[((data['CSQ-WW'][n][MU_AV]-self.MU_TRUE)/self.MU_TRUE)*100 for n in data['CSQ-WW']]
		y_mle=  [((data['MLE'][n][MU_AV]-self.MU_TRUE)/self.MU_TRUE)*100 for n in data['MLE']]
		yerr_csq=  [(data['CSQ'][n][MU_AV_ERR]/self.MU_TRUE)*100 for n in data['CSQ']]
		yerr_csqww=[(data['CSQ-WW'][n][MU_AV_ERR]/self.MU_TRUE)*100 for n in data['CSQ-WW']]
		yerr_mle=  [(data['MLE'][n][MU_AV_ERR]/self.MU_TRUE)*100 for n in data['MLE']]
		ax.errorbar(x,y_csq,c='r',label='fopt=CSQ',yerr=yerr_csq,fmt='o')
		ax.errorbar(x,y_csqww,c='b',label='fopt=CSQ-WW',yerr=yerr_csqww,fmt='o')
		ax.errorbar(x,y_mle,c='g',label='fopt=MLE',yerr=yerr_mle,fmt='o')
		#! Set xlabel only for the "bottom most" plot since the xaxis is shared
		#ax.set_xlabel('N',fontsize='x-large')
		#ax.set_ylabel(r'$\frac{\Delta\mu}{\mu_{true}}\%$',fontsize='xx-large')
		ax.set_ylabel(r'$\Delta\mu/\mu_{true}\%$',fontsize='x-large')
		ax.set_ylim(-0.05,0.05)
		ax.set_xticks(x)
		ax.set_xticklabels(self.N,rotation='vertical')
		ax.hlines(0,ax.get_xlim()[0],ax.get_xlim()[1])
		if self.SG==5.30: #! Draw legend only for "right most column" of fig in nim-pub
			ax.legend(loc='upper right')
		#! Fix x axis
		# shift half a step to the left
		xmin=(3*x[0]-x[1])/2.
		# shift half a step to the right
		xmax=(3*x[-1]-x[-2])/2.
		ax.set_xlim(xmin,xmax)
		ax.hlines(0,ax.get_xlim()[0],ax.get_xlim()[1])

		#! Plot sg/sg_T versus N
		#! new layout
		#! ax=axs[0][1]
		ax=axs[1]#![0]
		# ax.set_title(r'$\frac{\Delta\sigma}{\sigma_{true}}$'
		# 			 r' versus N',fontsize='xx-large')
		if self.SG==1.25: #! Draw title only for "left most column" of fig in nim-pub
			ax.set_title(r'$\Delta\sigma/\sigma_{true}$'
						 r' versus N',fontsize='xx-large',x=plot_title_loc_x,y=plot_title_loc_y,rotation='vertical')
		y_csq=  [((data['CSQ'][n][SG_AV]-self.SG_TRUE)/self.SG_TRUE)*100 for n in data['CSQ']]
		y_csqww=[((data['CSQ-WW'][n][SG_AV]-self.SG_TRUE)/self.SG_TRUE)*100 for n in data['CSQ-WW']]
		y_mle=  [((data['MLE'][n][SG_AV]-self.SG_TRUE)/self.SG_TRUE)*100 for n in data['MLE']]
		yerr_csq=  [(data['CSQ'][n][SG_AV_ERR]/self.SG_TRUE)*100 for n in data['CSQ']]
		yerr_csqww=[(data['CSQ-WW'][n][SG_AV_ERR]/self.SG_TRUE)*100 for n in data['CSQ-WW']]
		yerr_mle=  [(data['MLE'][n][SG_AV_ERR]/self.SG_TRUE)*100 for n in data['MLE']]
		ax.errorbar(x,y_csq,c='r',label='fopt=CSQ',yerr=yerr_csq,fmt='o')
		ax.errorbar(x,y_csqww,c='b',label='fopt=CSQ-WW',yerr=yerr_csqww,fmt='o')
		ax.errorbar(x,y_mle,c='g',label='fopt=MLE',yerr=yerr_mle,fmt='o')
		ax.set_ylim(-5,5)
		#! Set xlabel only for the "bottom most" plot since the xaxis is shared
		#ax.set_xlabel('N',fontsize='x-large')
		#ax.set_ylabel(r'$\frac{\Delta\sigma}{\sigma_{true}}\%$',fontsize='xx-large')  
		ax.set_ylabel(r'$\Delta\sigma/\sigma_{true}\%$',fontsize='x-large')        
		ax.set_xticks(x)
		ax.set_xticklabels(self.N,rotation='vertical')
		ax.hlines(0,ax.get_xlim()[0],ax.get_xlim()[1])
		if self.SG==5.30: #! Draw legend only for "right most column" of fig in nim-pub
			ax.legend(loc='upper right')
		#! Fix x axis
		# shift half a step to the left
		xmin=(3*x[0]-x[1])/2.
		# shift half a step to the right
		xmax=(3*x[-1]-x[-2])/2.
		ax.set_xlim(xmin,xmax)

		#! Plot error on estimated mu
		#! new layout
		#! ax=axs[1][0]
		ax=axs[2]#![0]
		# ax.set_title(r'$\frac{\sigma_{\mu}}{\mu}$'
		# 			 r' versus N',fontsize='xx-large')
		if self.SG==1.25: #! Draw title only for "left most column" of fig in nim-pub
			ax.set_title(r'$\sigma_{\mu}/\mu$'
						 r' versus N',fontsize='xx-large',x=plot_title_loc_x,y=plot_title_loc_y,rotation='vertical')
		y_csq=  [(data['CSQ'][n][MU_ERR_AV]/data['CSQ'][n][MU_AV])*100 for n in data['CSQ']]
		y_csqww=[(data['CSQ-WW'][n][MU_ERR_AV]/data['CSQ-WW'][n][MU_AV])*100 for n in data['CSQ-WW']]
		y_mle=  [(data['MLE'][n][MU_ERR_AV]/data['MLE'][n][MU_AV])*100 for n in data['MLE']]
		ax.scatter(x,y_csq,c='r',label='fopt=CSQ',s=50)
		ax.scatter(x,y_csqww,c='b',label='fopt=CSQ-WW',s=50)
		ax.scatter(x,y_mle,c='g',label='fopt=MLE',s=50)
		#! Set xlabel only for the "bottom most" plot since the xaxis is shared
		#ax.set_xlabel('N',fontsize='x-large')
		#ax.set_ylabel(r'$\frac{\sigma_{\mu}}{\mu}\%$',fontsize='xx-large')
		ax.set_ylabel(r'$\sigma_{\mu}/{\mu}\%$',fontsize='x-large')
		ax.set_xticks(x)
		ax.set_xticklabels(self.N,rotation='vertical')
		if self.SG==5.30: #! Draw legend only for "right most column" of fig in nim-pub
			ax.legend(loc='upper right')
		#! Fix x axis
		# shift half a step to the left
		xmin=(3*x[0]-x[1])/2.
		# shift half a step to the right
		xmax=(3*x[-1]-x[-2])/2.
		ax.set_xlim(xmin,xmax)

		#! Plot error on estimated sigma
		#! new layout
		#! ax=axs[1][1]
		ax=axs[3]#![0]
		# ax.set_title(r'$\frac{\sigma_{\sigma}}{\sigma}$'
		# 			 r' versus N',fontsize='xx-large')
		if self.SG==1.25: #! Draw title only for "left most column" of fig in nim-pub	
			ax.set_title(r'$\sigma_{\sigma}/\sigma$'
						 r' versus N',fontsize='x-large',x=plot_title_loc_x,y=plot_title_loc_y,rotation='vertical')
		y_csq=  [(data['CSQ'][n][SG_ERR_AV]/data['CSQ'][n][SG_AV])*100 for n in data['CSQ']]
		y_csqww=[(data['CSQ-WW'][n][SG_ERR_AV]/data['CSQ-WW'][n][SG_AV])*100 for n in data['CSQ-WW']]
		y_mle=  [(data['MLE'][n][SG_ERR_AV]/data['MLE'][n][SG_AV])*100 for n in data['MLE']]
		ax.scatter(x,y_csq,c='r',label='fopt=CSQ',s=50)
		ax.scatter(x,y_csqww,c='b',label='fopt=CSQ-WW',s=50)
		ax.scatter(x,y_mle,c='g',label='fopt=MLE',s=50)
		ax.set_xlabel('N',fontsize='x-large')
		#ax.set_ylabel(r'$\frac{\sigma_{\sigma}}{\sigma}\%$',fontsize='xx-large')
		ax.set_ylabel(r'$\sigma_{\sigma}/\sigma\%$',fontsize='x-large')
		ax.set_xticks(x)
		ax.set_xticklabels(self.N,rotation='vertical')
		if self.SG==5.30: #! Draw legend only for "right most column" of fig in nim-pub
			ax.legend(loc='upper right')
		#! Fix x axis
		# shift half a step to the left
		xmin=(3*x[0]-x[1])/2.
		# shift half a step to the right
		xmax=(3*x[-1]-x[-2])/2.
		ax.set_xlim(xmin,xmax)

		#! Don't tag file name with 'hist_range'(=exp/dflt) and 'gen_hist_mthd'(=ROOTic/Pythonic) anymore since
		#! those options make no difference (even though they are still passed in arguments, for just-in-case)
		#fig_name="mu-%d_sg-%.2f_binw-%.2f_hist_range-%s_gen_hist_mthd-%s"%(self.MU,self.SG,self.BINW,self.HIST_RANGE,self.GEN_HIST_MTHD)
		fig_name="mu-%d_sg-%.2f_binw-%.2f"%(self.MU,self.SG,self.BINW)
 		fig.savefig("/%s/%s.png"%(self.OUTDIR,fig_name))
		fig.savefig("/%s/%s.pdf"%(self.OUTDIR,fig_name))	
		
		print "Done CompROOTFits::plot_data_ROOT_fits()"
		return 0
		


	
