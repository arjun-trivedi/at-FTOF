I've changed the model for using the analysis tools; now there's only
one executable: 6barmethod.  It supports a long option and a short
option for every argument flag.  To compile, just run

make

and to cleanup, run

make clean

For a quick list of options and how to use 6barmethod, just run

6barmethod

with no arguments or you can include the help flag -h or --help.  The
argument flags are the following (not including the help flag):

-n, --normal: Enter the name of an output file from Gleb's analysis
    	      program after -n for each "normal ordering" analysis
    	      file you want to analyze.

-c, --complementary: This flag is for analysis files from
    		     "complementary ordering" analysis files.

-p, --permutation: Use this flag to give a custom bar ordering for an
    		   input file.  You must give the permutation as a
    		   string of integers 1-6 without spaces, followed by
    		   a space and then the name of the input file.  This
    		   is to support the analysis of data runs before the
    		   normal-complementary convention was established.

-o, --outputfile: Use this flag to specify the prefix for the two
    		  output files.  If the prefix is PRE, then the output
    		  files will be saved as PREmeans.dat and
    		  PREmaster.root.  The .root file is the master output
    		  file with all results stored inside; the .dat file
    		  is a text file with 12 lines, the first 6 being the
    		  mean resolution for each individual bar via the
    		  matrix method, the last 6 being the mean resolution
    		  for each bar via the mean method.

The results stored in the master output file are all histograms; its
structure should be straightforward.

The means.dat output file has the following format:

    The first 6 lines are the matrix method results for all 6 bars.

    The next 6 lines are the mean method results for all 6 bars.

    The next line is the mean of all six matrix method results.

    The next line is the mean of the normal order 3 bar combination
    resolutions if and only if there were any normal order input files.

    The next line is the mean of the complementary order 3 bar combination
    resolutions if and only if there were any complementary order input
    files.

    The last line is the mean over all 3 bar combination resolutions.

So, for analyses of only one type of bar ordering there are 15 lines,
and for analyses of both normal and complementary data there are 16
lines.
