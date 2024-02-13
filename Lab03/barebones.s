# Build an executable using the following:
#
# clang barebones.s -o barebones  # This command compiles the assembly file 'barebones.s' using the 'clang' compiler to produce an executable named 'barebones'.

.text
_barebones:

.data
	
.globl main

main:
				# (1) What are we setting up here?
				# Ans: This section is setting up the function's stack frame. It's a common practice at the beginning of a function to prepare a new stack frame by pushing the current base pointer onto the stack and then setting the base pointer equal to the stack pointer. This allows the function to manage its local variables and function calls.

	pushq %rbp		# Saves the current base pointer to the stack to preserve the caller's stack frame.
	movq  %rsp, %rbp	# Sets the base pointer equal to the stack pointer, establishing a new stack frame for the current function.

				# (2) What is going on here
				# Ans: These instructions prepare for a system call to write text to standard output. Specifically, they load the necessary arguments into registers according to the calling convention for system calls on x86-64 architecture. The 'movq' instructions set up the syscall number and its parameters, while 'leaq' loads the address of the string to be printed.

	movq $1, %rax		# Loads the syscall number for 'write' into %rax.
	movq $1, %rdi		# Sets the file descriptor parameter to 1 (stdout).
	leaq .hello.str,%rsi	# Loads the memory address of the string label '.hello.str' into %rsi, the buffer parameter for the 'write' syscall.

			# (3) What is syscall? We did not talk about this in class.
			# Ans: A 'syscall' is an instruction that triggers a system call, allowing a program to request services from the kernel, such as file I/O, process control, or network operations. It acts as a bridge for programs to access kernel functions while maintaining system security and stability.

	syscall			# Which syscall is being run?
				# Ans: This executes the 'write' syscall, which writes the content pointed by %rsi (our "Hello World!\n" string) to the file descriptor specified in %rdi (stdout).

				# (4) What would another option be instead of 
				# using a syscall to achieve this?
				# Ans: Instead of directly invoking a syscall, one could use a high-level library function like 'printf' from the C Standard Library. These functions provide a more user-friendly interface for output and handle the details of interacting with the system kernel internally.

	movq	$60, %rax	# (5) We are again setting up another syscall
	movq	$0, %rdi	# What command is it?
				# Ans: These instructions prepare for the 'exit' syscall, which terminates the process. The syscall number for 'exit' is loaded into %rax, and the exit status is set to 0 in %rdi, indicating successful completion.

	syscall

	popq %rbp		# Restores the previous base pointer by popping the top value off the stack. This is part of cleaning up the stack frame before exiting the function, even though it's technically not required here since the program is about to exit.

.hello.str:
	.string "Hello World!\n"
	.size	.hello.str,13		# (6) Why is there a 13 here?
					# Ans: The number 13 specifies the size of the string "Hello World!\n", including the newline character and the null terminator. It's necessary for correctly defining the data segment containing the string, allowing the assembly program to accurately reference the string's length.


