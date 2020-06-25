The operations test whether the x86 coprocessor (the FPU) is superscalar, thus it should try to paralelise some operations.

The two functions prepared in the ASM code try to test that functionality, but performing different operations, sometimes having to wait for the result
of the previous operation and sometimes not.

Later times of these functionalities are measured.

compile: gcc -O c_code.c calculations.s rdtsc.s -o zadanie4_5
use: ./zadanie4_5
