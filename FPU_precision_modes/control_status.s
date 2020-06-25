.data

control_word_rd:
.space 2

control_word_wr:
.space 2

status_word:
.space 2

.text
.global read_control_word
.type read_control_word, @function

read_control_word:
# Create a new frame and store the frame pointer
pushl %ebp
movl %esp, %ebp
pushl %edi

xorl %edi, %edi
movl $1, %edi

# Control word register is a 16 bit register so in order to move it's value
# to %eax (in order to return it) movb is used twice.

xorl %eax, %eax
fstcw control_word_rd
fwait
movb control_word_rd, %al
movb control_word_rd(,%edi, 1), %ah


# Restore the old frame
popl %edi
movl %ebp, %esp
popl %ebp
ret


.global write_control_word
.type write_control_word, @function

write_control_word:
# Create a new frame and store the frame pointer
pushl %ebp
movl %esp, %ebp

xorl %eax, %eax

# Get the given 16 bit control word, passed as an argument and
# use fldcw to load it.

movb 8(%ebp), %al
movb 9(%ebp), %ah
movl %eax, control_word_wr
fldcw control_word_wr

# Restore the old frame
movl %ebp, %esp
popl %ebp
ret


.global read_status_word
.type read_status_word, @function
read_status_word:

# Create a new frame and store the frame pointer
pushl %ebp
movl %esp, %ebp
pushl %edi
 
 
xorl %edi, %edi
movl $1, %edi

# Status register is a 16 bit register so in order to move it's value
# to %eax (in order to return it) movb is used twice.
 
xorl %eax, %eax
fstsw status_word
fwait
movb status_word, %al
movb status_word(,%edi, 1), %ah
 

# Restore the old frame
popl %edi
movl %ebp, %esp
popl %ebp
ret

.global calculate
.type calculate, @function
calculate:
pushl %ebp
movl %esp, %ebp

fldl number2
fldl number3
fdiv %st(1),%st


movl %ebp, %esp
popl %ebp
ret

