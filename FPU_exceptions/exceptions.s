.text
.global generate_divide_by_zero
.type generate_divide_by_zero, @function

generate_divide_by_zero:
# Create a new frame and store the frame pointer.
pushl %ebp
movl %esp, %ebp

# Push a zero to the FPU stack, then a one.
# Divide the one by the zero.

fldz
fld1
fdiv %st,%st(1)

# Restore the old frame
movl %ebp, %esp
popl %ebp
ret


.global generate_precision_exception
.type generate_precision_exception, @function

generate_precision_exception:
# Create a new frame and store the frame pointer
pushl %ebp
movl %esp, %ebp

# Divide 3/7- arbitrarily chosen numbers, declared in C file.
# These numbers don't divide evenly, thus the number can't be
# precisely saved: we have to round it. This action generates a 
# precision exception.

fldl arbit_number1
fldl arbit_number2
fdiv %st,%st(1)


# Restore the old frame
movl %ebp, %esp
popl %ebp
ret
