#!/usr/bin/python
from __future__ import division
import re
from collections import OrderedDict
import os
from math import *

#! matplotlib imports
import matplotlib.gridspec as gridspec

#! rootpy imports
import rootpy
from rootpy.io import root_open, DoesNotExist
import ROOT

'''
+ This program re-obtains time resolution and its error using 'res_X_Y_Z_cont_pointP_cont' histogrms  already contained in 'ftof_offical' data for every: {set}x{order}x{cmbn}x{mthd}, where:
 + set = FTOF set number, ordered by length
 + order = norm or comp
 + cmbn = the 6 combinations: 1_2_3,2_3_4,3_4_5,4_5_6,1_3_5,2_4_6
 + method = arthmtc,CSQ,CSQWW,MLE

+ The output is contained in histograms labelled by {set}x{order}x{cmbn}x{mthd} in $FTOF_DATADIR/ftof_official_time_rsltn_all_mthds/time_res.root
'''
#! Input data=FTOF offical data 
#DATADIR='/home/trivedia/Downloads/ftof_official'
DATADIR=os.path.join(os.environ['FTOF_DATADIR'],'ftof_official')

TOF_CLB=sqrt(2/3)*25 #calibration to get values from raw TDC values

#! **** Prepare ouput data structures: ****
#! + rsltn[set,order,cmbn,mthd][p]
#! + rsltn_err[set,order,cmbn,mthd][p] 
#! + h[set,order,cmbn,mthd] (histogram with rsltn and rsltn_err)
#! 	+ Note h[] is created and filled in the end once rsltn and rsltn_err have been obtained
#!	+ h[] stored in $FTOF_DATADIR/ftof_official_time_rsltn_all_mthds/time_res.root
#! where: 
#! + set = FTOF set number, ordered by length
#! + order = norm or comp
#! + cmbn = the 6 combinations
#! + method = arthmtc,CSQ,CSQWW,MLEa
#! + p = point along bar
ORDERL=['norm','comp']
CMBNL=['1_2_3','2_3_4','3_4_5','4_5_6','1_3_5','2_4_6']
MTHDL=['arthmtc','CSQ','CSQWW','MLE']
rsltn,rsltn_err=OrderedDict(),OrderedDict()

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
				for mthd in MTHDL:
					rsltn[il+1,order,cmbn,mthd]=OrderedDict()
					rsltn_err[il+1,order,cmbn,mthd]=OrderedDict()
#print "rsltn data structure=",rsltn
#print "rsltn_err data structure=",rsltn_err
#! ****************************************** 
			

#! ***Now fill output data structure***
for il,l in enumerate(barl):
	#print "bar set number:barl=%d:%d"%(il+1,l)
	#if l!=17:continue#: and l!=401: continue
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
						#print "h=",h.GetName();
						for mthd in MTHDL:
							#print "method=",mthd
							print "cmbn:mthd:point=(%s:%s:%d)"%(cmbn,mthd,p)
							if mthd=="arthmtc":
								rsltn[il+1,order,cmbn,mthd][p]=round(h.GetRMS()*TOF_CLB,2)
								rsltn_err[il+1,order,cmbn,mthd][p]=round(h.GetRMSError()*TOF_CLB,2)
							else: #! i.e. if CSQ or CSQWW or MLE
								if mthd=="CSQ":
									h.Fit("gaus","Q")
								elif mthd=="CSQWW":
									h.Fit("gaus","QWW")
								elif mthd=="MLE":
									h.Fit("gaus","QL")
								fit=h.GetFunction("gaus")
								rsltn[il+1,order,cmbn,mthd][p]=round(fit.GetParameter(2)*TOF_CLB,2)
								rsltn_err[il+1,order,cmbn,mthd][p]=round(fit.GetParError(2)*TOF_CLB,2)
print "Done making rsltn and rsltn_err output data structures"
#! *************************************

print "***Going to make h output data structure***"
OUTDIR="%s/ftof_official_time_rsltn_all_mthds"%os.environ['FTOF_DATADIR']
h=OrderedDict()
fout=ROOT.TFile("%s/time_res.root"%OUTDIR,"RECREATE")
for k in rsltn.keys():
	print "making h for:",k
	num_points=len(rsltn[k])
	#print "num_points=",num_points
        hname="h_%d_%s_%s_%s"%(k[0],k[1],k[2],k[3])
	#print "hname=",hname
	h[k]=ROOT.TH1F(hname,hname,num_points,0.5,num_points+0.5)
	for ip in range(num_points):
		h[k].SetBinContent(ip+1,rsltn[k][ip+1])
		h[k].SetBinError(ip+1,rsltn_err[k][ip+1])
fout.Write()
print "***Done making h output data structure***"
#! ************************************

print "If the program is not exiting gracefully then wait since Python is probably doing Garbage Collection and that takes a while for this program."

