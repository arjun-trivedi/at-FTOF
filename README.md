[02-02-15] General information on at-FTOF repository
====================================================
In this repository I have consolidated all aspects of FTOF related work in a single directory(which were earlier scattered across in different locations):

+ ana6bar:Gleb's and Gary's analysis programs
+ ana-time-res-err: My analysis on the error on the time resolution extracted
+ docs:All relevant documents
+ PMT-tests:Code and data from when I was testing PMTs 

Branch information
==================

+ master: This is the branch that was first created when I consolidated all FTOF work in at-FTOF, therefore, in this branch should simply be a copy of all the work that was located at different locations.
	+ setup.tcshrc
		+ Used to set up aliases, environment variables and anything else needed to work in this directory
	+ ana6bar
		+ 6barmethod-2012-04-11
		+ data_converter_09_02_11
		+ nogui_analysis_06_26_12
		+ nogui_analysis_06_26_12_CSQ
		+ nogui_analysis_06_26_12_MLE
		+ res_tof12
	+ ana-time-res-err
		+ This basically contains code that I copied over from $WORKSPACE/at-stats, where I had been working before I created at-FTOF repository.
	+ docs
		+ Contains all relevant documents
	+ PMT-tests
		+ Code and data from when I was testing PMTs

	+ gary-ana-add-errbars [02-16-15]: Made this branch to perform analysis now that Gary implemented error bars for the extraction of time resolution.
		+ Removed notebooks in ana-time-res-err that compared ROOT fits using comp_MLE_CSQ.py after it was replaced by the more comprehensive comp_ROOT_fits.py.
