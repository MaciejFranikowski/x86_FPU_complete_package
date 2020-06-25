.text
.global rdtsc
.type rdtsc, @function

rdtsc:
# Create a new frame and store the frame pointer
pushl %ebp
movl %esp, %ebp
# Save register value according to ABI.
# %ebx has to be saved, because cpuid alters it.
pushl %ebx

xorl %eax, %eax
cpuid
rdtsc
# Rdtsc puts a value in %ecx:%eax, which is then returned by the function

# Restore registers according to ABI regulation
popl %ebx
# Restore the old frame
movl %ebp, %esp
popl %ebp
ret

