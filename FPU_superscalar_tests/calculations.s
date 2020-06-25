.data

number1:
.double 15

number2:
.double 14

number3:
.double 2

number4:
.double 1.5

number5:
.double 3.5

number6:
.double 21

number7:
.double 100

number8:
.double 200



.text
.global prepare_data
.type prepare_data, @function

prepare_data:
# Create a new frame and store the frame pointer
pushl %ebp
movl %esp, %ebp

# Allocate the chosen numbers on the FPU stack.

fldl number1
fldl number2
fldl number3
fldl number4
fldl number5
fldl number6
fldl number7
fldl number8

movl %ebp, %esp
popl %ebp
ret


.global connected_arithmetic
.type connected_artihmetic, @function

connected_arithmetic:
# Create a new frame and store the frame pointer
pushl %ebp
movl %esp, %ebp
pushl %edi


movl $50, %edi

start:
cmpl $0, %edi
je end
fadd %st(2),%st
fmul %st(3),%st
fadd %st(4),%st
fmul %st(5),%st
fadd %st(6),%st
fmul %st(7),%st

decl %edi
jmp start
end:

popl %edi
# Restore the old frame
movl %ebp, %esp
popl %ebp
ret


.global not_connected_arithmetic
.type not_connected_arithmetic, @function
not_connected_arithmetic:

# Create a new frame and store the frame pointer
pushl %ebp
movl %esp, %ebp
pushl %edi
movl $50,%edi

start1:
cmpl $0, %edi
je end1
fadd %st,%st(2)
fmul %st(3),%st
fadd %st,%st(1)
fmul %st(6),%st
fadd %st,%st(4)
fmul %st(6),%st

decl %edi
jmp start1
end1:

popl %edi
movl %ebp, %esp
popl %ebp
ret
