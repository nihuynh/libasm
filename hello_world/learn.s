; ?>nasm -f elf64 -o test.o hello_world/learn.s
; ?>ld -m elf_x86_64 -o learn.out test.o



section .data

section .text
global _start

_start:
		MOV eax,1
		MOV ebx,1
		INT 80h			;exit code