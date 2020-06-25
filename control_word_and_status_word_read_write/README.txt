In .s file there are functions that allow for reading the status word and the control word of the FPU.
Also there is a function that allows the writing of the control word.
These functions are used and showcased in the C code.

compile: gcc -O c_code.c control_status.s -o zadanie4_1
use: ./zadanie4_1
