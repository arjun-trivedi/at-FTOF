This is an example for stack mode read-out of CAEN V792 charge ADC module with the VM-USB.
The stack files for the VME read-out are configured for a base address of 0x11110000. 
Any change of the base address on the module requires a corresponding change in the stack.

Before running the program set the V792 base address to 1111 (or change settings / stack) and 
set the correct VM-USB serial number.

The following stack can be used:

1) Dynamic BLT read according to number of words in event header
//VM-USB VME Stack Generated on 9/20/2007 at 1:42:22 PM
//Stack #0 (Main/IRQ)
0x000D
0x0000
0x0109
0x0004
0x0000
0x1111
0x010B
0x3200
0x0000
0x1111
0x0109
0x0000
0x0000
0x1111

2) fixed read of 34 x 32 bit words for header, 32 data and EOB:
//VM-USB VME Stack Generated on 1/16/2008 at 9:30:01 PM
//Stack #0 (Main/IRQ)
0x0005
0x0000
0x010B
0x3400
0x0000
0x1111

Any comments, problems or improvement please report to the WIENER VM-USB forum or to

WIENER, Plein & Baus, Ltd.
www.wiener-us.com

a.ruben@wiener-us.com


