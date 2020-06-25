In the exceptions.s code located are functions that generate exceptions. These exceptions are masked tho, so they can only be seen in the status word of 
the FPU, which is done using control_status.s

These functionalites are showcased in the C code.

compile: gcc -O control_status.s c_code.c exceptions.s -o zadanie4_2
use: ./zadanie4_2
