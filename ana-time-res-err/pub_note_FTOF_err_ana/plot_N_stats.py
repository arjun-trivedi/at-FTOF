#!/usr/bin/python
from __future__ import division
import re
from collections import OrderedDict
import os,sys
from math import *

#! matplotlib imports
import matplotlib.gridspec as gridspec
import matplotlib.pyplot as plt

#! numpy
import numpy as np

#! rootpy imports
import rootpy
from rootpy.io import root_open, DoesNotExist
from rootpy.plotting import Hist2D, Hist
import ROOT

#! to get bar_length[]
from bar_length import bar_length

'''
+ This program obtains N_vs_p plot using 'res_X_Y_Z_cont_pointP_cont' histograms  already contained in 'ftof_offical' data for every: {set}x{order}x{cmbn}, where:
 + set = FTOF set number, ordered by length
 + order = norm or comp
 + cmbn = the 6 combinations: 1_2_3,2_3_4,3_4_5,4_5_6,1_3_5,2_4_6

+ The output is contained in histograms labelled by {set}x{order}x{cmbn}
'''

#! Check if user wants to run in debug mode i.e. use only a few barsets to make data (see where debug used in code)
debug=False
if len(sys.argv)==2:
	debug=True #! For now anythink junk is interpreted as debug
print "debug=",debug

#! Input data=FTOF offical data 
#DATADIR='/home/trivedia/Downloads/ftof_official'
DATADIR=os.path.join(os.environ['FTOF_DATADIR'],'ftof_official')

TOF_CLB=sqrt(2/3)*25 #calibration to get values from raw TDC values

#! **** Ouput data structures: ****
#! + N[set,order,cmbn][p]
#! + h[set,order,cmbn] #! This basically histograms N data structure
#! where: 
#! + set = FTOF set number, ordered by length
#! + order = norm or comp
#! + cmbn = the 6 combinations
#! + p = point along bar
ORDERL=['norm','comp']
CMBNL=['1_2_3','2_3_4','3_4_5','4_5_6','1_3_5','2_4_6']
N=OrderedDict()

#! Get all the set numbers and order them by length 
barl=[]
for f in os.listdir(DATADIR):
    if f=="6barmethod-results-with-errors": continue #! Ignore this dir, probably made by Gary
    if os.path.isdir(os.path.join(DATADIR,f)):
        barl.append(f)
barl=map(int,barl)
#print setl
barl.sort()
#print "bar list=",barl

for il,l in enumerate(barl):
	for order in ORDERL:
			for cmbn in CMBNL:
				N[il+1,order,cmbn]=OrderedDict()
#print "N data structure=",N
#! ****************************************** 
			

#! ***Now fill N output data structure***
for il,l in enumerate(barl):
	#print "bar set number:barl=%d:%d"%(il+1,l)
	if debug and l!=17:continue#: and l!=401: continue
	for order in ORDERL:
		#print "order=",order
		for f in os.listdir(os.path.join(DATADIR,"%d"%l)):
			if (order=='norm' and (re.search("123456.+root",f) or "30cm_norm_result.root" in f)) or (order=='comp' and (re.search("321654.+root",f) or "30cm_compl_result.root" in f)): 
				#print "f=",f
				print "setn:barl:order:f=(%d:%d:%s:%s)"%(il+1,l,order,f)
				rf=rootpy.io.File("%s"%os.path.join(DATADIR,"%d"%l,f))
				pl=[]# make list of points and order later
				for dirpath,dirnames,filesnames in rf.walk():
					if "point_" in dirpath:
						#print dirpath
						pl.append(int(dirpath.strip("point_")))
				pl.sort()
				#print "point list=",pl
				print "number of points=",len(pl)
				#! Now for each point get rsltn and rsltn_err for {cmbn}x{mthd}
				for p in pl:
					for cmbn in CMBNL:
						#print "cmbn=",cmbn
						h=rf.Get("point_%d/res_%s_point%d_cont"%(p,cmbn,p))
						N[il+1,order,cmbn][p]=int(round(h.GetEntries(),0))
						#print "h=",h.GetName();
print "Done making N output data structures"
#! *************************************

#! Now make plots and save them
#! + Set up general-histogram aesthetics as per Gleb's code (macro.cxx) 
#!   to maintain consistency with other ROOT-hists in pub
#! + Any code that I modified is noted and/or commented out
ROOT.gStyle.Reset() #! Reset aesthetics which may have been set by some other plot functio
ROOT.gStyle.SetOptStat(0)
ROOT.gStyle.SetFrameLineWidth(3)
ROOT.gStyle.SetLineWidth(3)
#!ROOT.gStyle.SetHistLineWidth(3)
#!ROOT.gStyle.SetTitleH(0.09)
#!ROOT.gStyle.SetTitleW(0.65)

#OUTDIR=("%s/at_pub_figs/N_stats"%os.environ['FTOF_DATADIR'])
OUTDIR=("%s/at-FTOF/ana-time-res-err/pub_note_FTOF_err_ana/N_stats"%os.environ['WORKSPACE'])
if not os.path.exists(OUTDIR):
	os.makedirs(OUTDIR)

#! Make a histogram for all N
outdir=("%s/all"%OUTDIR)
if not os.path.exists(outdir):
        os.makedirs(outdir)
N_all=[]
for k in N.keys():
	num_points=len(N[k])
	for ip in range(num_points):
		N_all.append(N[k][ip+1])
#! Now plot N_all[]
#! Following lines were making a Pythonic histogram,
#! but since the other plots (N_vs_p; directly from 'ftof_offical' data)
#! made by this script are ROOTic, I am making this plot ROOTic too.
fig,ax = plt.subplots(figsize=(20,8))
ax.set_title("Range of N for all production data",fontsize='xx-large')
ax.set_xlabel("N",fontsize='xx-large')
plt.hist(N_all,100,(0,600))
fig.savefig("%s/N_range_Pythonic.png"%outdir)
fig.savefig("%s/N_range_Pythonic.pdf"%outdir)
#! ROOTic plot
h=Hist(60,0,600)
h.SetTitle("Range of N for all production data")
h.SetXTitle("N")
#! Fill with N_all
h.fill_array(N_all)
#! Set error bars on all bins to 0
err=np.zeros(100,'d')
h.SetError(err)
#! Set up particular-histogram aesthetics (also inspired by GF)
h.GetXaxis().SetTitleSize(0.05)
h.GetXaxis().SetTitleOffset(0.9)
h.GetYaxis().SetTitleSize(0.05)
h.GetYaxis().SetTitleOffset(0.9)
# h.GetXaxis().SetNdivisions(5) #! Not using this option for this hist
h.SetLineWidth(3)
#! Draw and save hist
c=ROOT.TCanvas()
h.Draw("B")
c.SaveAs("%s/N_range.png"%outdir)
c.SaveAs("%s/N_range.pdf"%outdir)

#! Make plots for N vs p for {set}*{order}*'1_2_3'
outdir=("%s/N_vs_p"%OUTDIR)
if not os.path.exists(outdir):
        os.makedirs(outdir)
for k in N.keys():
	setn=k[0]
	order=k[1]
	cmbn=k[2]

	#! Make plots only for cmbn '1_2_3' (the rest should be identical)
	if cmbn!='1_2_3': continue 
	print "making N_vs_p for:",setn,order,cmbn
	num_points=len(N[k])
	if num_points==0: continue #! just incase the code is run in debug mode i.e. only some sets have data

	#! I have basically reproduced Gleb's code for creating the x axis of the histogram
	#! from 'MyMainFrame.cxx' where the binning of resol_1_2_3 is '0,npoints,l_d' where
	#! + npoints=(int)bar_length/3.
	#! + l_d=bar_length
	npoints=(int)(bar_length[setn-1]/3.)
	if (npoints!=num_points):
		sys.exit("npoints (calculated using bar_length)!=num_points(obtained from N data structure). Exiting. Check what is going on.")
	#! Now create and draw hists
	c=ROOT.TCanvas()
	h=ROOT.TH1F("h","h",npoints,0,bar_length[setn-1])
	h.SetTitle("N versus point for 6 bar set of length %.2f cm"%bar_length[setn-1])
	h.SetMarkerStyle(ROOT.gROOT.ProcessLine("kFullCircle"))
	h.SetMarkerColor(ROOT.gROOT.ProcessLine("kBlack"))
	h.GetXaxis().SetTitle("Position (cm)");
	h.GetYaxis().SetTitle("N");
	#! Set up histogram aesthetics
	h.GetXaxis().SetTitleSize(0.05)
	h.GetXaxis().SetTitleOffset(0.9)
	h.GetYaxis().SetTitleSize(0.05)
	h.GetYaxis().SetTitleOffset(0.9)
	h.SetMinimum(0)
	h.SetMaximum(600)
	for ip in range(h.GetNbinsX()):
		h.SetBinContent(ip+1,N[k][ip+1])
		h.SetBinError(ip+1,0)
	h.Draw("P")
	#! Save		
	c.SaveAs("%s/%02d_%s_%s.png"%(outdir,setn,order,cmbn))
	c.SaveAs("%s/%02d_%s_%s.pdf"%(outdir,setn,order,cmbn))
	
print "***Done making plots ***"
#! ************************************

print "If the program is not exiting gracefully then wait since Python is probably doing Garbage Collection and that takes a while for this program. \n This particular program takers extra long here and using the 'killall plot_N_stats.py' is OK, it seems."

