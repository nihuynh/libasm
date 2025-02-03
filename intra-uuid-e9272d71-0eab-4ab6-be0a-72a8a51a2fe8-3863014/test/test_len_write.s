; Hello World Program (External file include)
; Run with: nasm -f elf64 test_len_write.s -i ../src && ld -m elf_x86_64 test_len_write.o -o test_len_write && ./test_len_write

%include        '_ft_write.s'

SECTION .data
msg1    db      'Hello, brave new world!', 0Ah, 0h          ; our first message string
msg2    db      'This is how we recycle in NASM.', 0Ah, 0h  ; our second message string
 
SECTION .text
global  _start
 
_start:
 
    mov     eax, msg1   ; move the address of our first message string into EAX
    call    _ft_write    ; call our string printing function
 
    mov     eax, msg2   ; move the address of our second message string into EAX
    call    _ft_write    ; call our string printing function

    mov     ebx, 0      ; Exit syscall
    mov     eax, 1
    int     80h
    ret