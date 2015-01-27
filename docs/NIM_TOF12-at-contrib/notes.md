### Notes on at_contrib.tex

## [10-12-14]
* Address the matter of Fig. 1 and Fig. 2: see if they exist already, else re-draw them.
* "(...) the anode signal of the PMT was digitized and processed by a DAQ system (...)" -> May be irrelevant if the final measurements are going to be directly off the oscillosope.
* Confirm that at 10G-L and 20G-T with only Mu-metal shielding the reduction of signal amplitude is indeed 10% for this are the reduction levels at which RS found no affect on the time resolution.
* The scintillators used for the time resolution tests mentioned in RS's thesis were 6cmX6cmX120cm Bicron BC-404 and the PMTs were Hamamatsu R9779
* When quoting that at 10% reduction levels in the T and L orientations, the measured time resolution was 41 ps and 38 ps respectively, compared to 38 ps with no magnetic fields, how do we give an estimate of the errors?
* Measure thickness of mu-metal coating using a broken PMT
* Establish if we are going to use 25G or 30G as the limit for which the final shielding was designed
* Quantify "few" mms that the "two edges" of the scintillators were shaved off by
* Confirm if 4cm(1.5in) is indeed the final overhang


### Measurements 

Taken from [FTOF12 Publication outline](https://docs.google.com/document/d/1lmUzZyPiJII3UrA2D973143--wMJR4UFZqvusMk9174/edit#heading=h.vk6d5uhn2rz8)'s section III: Prototyping and design -- equipment selection, calibration, and method choices

#### C. Electronics
1. TDC testing
2. QDC testing
	* [https://clasweb.jlab.org/wiki/index.php/TOF12:CAEN_V792N_QDC](https://clasweb.jlab.org/wiki/index.php/TOF12:CAEN_V792N_QDC)
3. Discriminator testing
	* [https://clasweb.jlab.org/wiki/index.php/TOF12:Discriminator_Testing](https://clasweb.jlab.org/wiki/index.php/TOF12:Discriminator_Testing)

#### D. Time-Walk Corrections

* The first two methods were ruled out: Look at publication
* Look into work aready done to justify these methods: Lewis thesis, Haiyun's work etc.

#### E. PMTs
1. Different PMTs time resolutions
	* [https://clasweb.jlab.org/wiki/index.php/TOF12:Time_Resolution_with_Electron_Tubes_PMTs](https://clasweb.jlab.org/wiki/index.php/TOF12:Time_Resolution_with_Electron_Tubes_PMTs)
2. … threshold dependence
	* [https://clasweb.jlab.org/wiki/index.php/TOF12:Effect_of_Threshold_Levels_on_Time_Resolution_for_Hamamatsu_PMTs](https://clasweb.jlab.org/wiki/index.php/TOF12:Effect_of_Threshold_Levels_on_Time_Resolution_for_Hamamatsu_PMTs)


#### F. Magnetic Shielding
5. time resolution
	* [https://clasweb.jlab.org/wiki/index.php/TOF12:PMT_and_Mu-metal_in_Magnetic_Fields#Three_Bar_Time_Resolution_Measurements_in_the_Presence_of_Magnetic_Field](https://clasweb.jlab.org/wiki/index.php/TOF12:PMT_and_Mu-metal_in_Magnetic_Fields#Three_Bar_Time_Resolution_Measurements_in_the_Presence_of_Magnetic_Field)

#### G. Geometry and lightguides
* [https://clasweb.jlab.org/wiki/index.php/TOF12:Light_Guides](https://clasweb.jlab.org/wiki/index.php/TOF12:Light_Guides)

#### H. Scintillators
1. Scintillator comparing (BC408, long bars; BC404 short bars; EJ equivalents)
	* [https://clasweb.jlab.org/wiki/index.php/TOF12:Scintillator_Comparisons](https://clasweb.jlab.org/wiki/index.php/TOF12:Scintillator_Comparisons)
2. Attenuation length measuring and results(Attenuation length results of two point method for all the scintillators and 
the 2 dimensional histogram(ADC_VS_TDCDiff) comparison)
	* [https://clasweb.jlab.org/wiki/index.php/TOF12:Scintillator_Attenuation_Measurements](https://clasweb.jlab.org/wiki/index.php/TOF12:Scintillator_Attenuation_Measurements)

#### I. Reflective wrap (diffuse and reflective)
* [https://clasweb.jlab.org/wiki/index.php/TOF12:VM2000_vs._Aluminized_Mylar](https://clasweb.jlab.org/wiki/index.php/TOF12:VM2000_vs._Aluminized_Mylar)

#### J. Cables
1. Individual cable attenuation length testing (RG58)
	* [https://clasweb.jlab.org/wiki/index.php/Test_Cable_Attenuation_Effects:](https://clasweb.jlab.org/wiki/index.php/Test_Cable_Attenuation_Effects:)
2. 50ft,75ft,100ft cable length time resolution results

