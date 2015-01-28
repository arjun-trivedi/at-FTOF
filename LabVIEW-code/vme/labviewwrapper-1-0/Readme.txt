/*****************************************************************************/
/*                                                                           */
/*                  --- CAEN SpA - Computing Division ---                    */
/*                                                                           */
/*   Software support for Power Supply Systems                               */
/*									     */
/*   CAENHVWrapper.llb                                                       */
/*                                                                           */
/*   Rel. 1.0 - June 2002  					             */
/*                                                                           */
/*****************************************************************************/
 
 This archive contains the CAENHVWrapper.llb Labview VI library for Labview 6.1 for Windows
 
 Each directory contains the CAENHVWrapper.llb Labview VI library, the relevant
 documentation and the file containing the error codes and descriptions.

 More info concerning this utility are available on CAEN's Web Site at:
                          http://www.caen.it/computing/ 
 or via e-mail at: 
                          support.computing@caen.it              


 Content of the archive
 ----------------------

 Readme.txt              : this text file

 Win32-LV6.1/            : Labview 6.1 for Windows version 

 each one divided as follow:

 Samples_N470-N570/
   CAEN-N470-ctl.vi      : complete N470 power supply controller sample
   CAEN-N570-ctl.vi      : complete N570 power supply controller sample
   ReadBitfieldPar.vi    : Subvi used in the above samples
   ReadBoolPar.vi        : Subvi used in the above samples
   ReadSinglePar.vi      : Subvi used in the above samples

 errors/
   CAENHV-errors.txt     : the file containing the error codes and descriptions

 CAENHVWrapper.llb       : the library containing all the VIs 
 


 Installation notes
 ------------------

 1. Copy the CAENHVWrapper.llb into the %labviewdir%\user.lib directory and the 
    CAENHV-errors.txt file into the %labviewdir%\user.lib\errors directory.
    ( %labviewdir% is usually c:\program files\National Instruments\LabView X.x )

 2. Verify the installation launching Labview and opening the functions palette:
    you have to find the all Vis of the library inside the User Libraries. 
  

 Description
 -----------

 The library is intended to aid the Labview programmer who wants to control the
 CAEN power supplies using the Wrapper library. The Vis are, in fact, almost  
 merely calls to the CAENHVWrapper dynamic library, decorated with an error 
 handling good for the Labview environment. 
 The Vis implemented are those functions of the CAENHVWrapper library that 
 don't need to pass lists as parameters, due to an incompatibility issue 
 between C and Labview data types.
 In general all the Vis take the name of the system and an error cluster as 
 input parameters and also give them in output; in this manner you can link the
 VIs together in a chain to ensure a sequential series of calls to the library
 (this is mostly important for CAENET communications).
 You can refer to the CAENHVWrapper library manual for a description of the 
 functions and to the samples in this archive as a "hands-on" explanation.

 Note:
 -----
 The Vis contained in this library require the previous correct installation of
 the CAENHVWrapper and the HSCAENETLib dynamic libraries.

 Control of CAEN Power Supplies via CaeNet link requires the correct
 installation of the A303 and/or A1303 device driver. 

 