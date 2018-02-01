;CSE 109
;Badjessa Bahoumda
;bbb219
;Program Descripion:
;Homework 2



	extern printf  		;C function to be called

SECTION .data
  
str:	db 'Learning Assembly code', 0x0 


fmt:	db '%s', 10, 0	        ;printf format

SECTION .bss
	temp resb 30
	
SECTION .text
	global main

main:
	mov ecx, str
	mov edx, 30
	call scan
	
print:	
	push rbp

	mov rax, temp
	mov rdi, fmt
	mov rsi, rax
	mov rax, 0
		call printf

	pop rbp

	mov rax, 0
	ret
	
	 
strbrk:
        add [temp],byte 0
	push rbp

	mov rax, temp
	mov rdi, fmt
	mov rsi, rax
	mov rax, 0
		call printf

	pop rbp
	mov rax, 0
scan:
	cmp byte[ecx], 0x0
	jz print
	cmp byte [ecx], 0x32
	jz strbrk
	add [temp], ecx
	inc ecx
	jmp scan


	
	
	