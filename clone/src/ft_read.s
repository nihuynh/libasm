; File: ft_read.s
; File Created: 05/02/2025 23:12
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Description: <Desc of the file goal(s)>
; Copyright 2025 NH

%ifidn __OUTPUT_FORMAT__, macho64
    %define ERRNO_FN        ___error
    %define READ_SYSCALL    0x2000003
    %define READ_LABEL      _ft_read
%elifidn __OUTPUT_FORMAT__, elf64
    %define ERRNO_FN        __errno_location
    %define READ_SYSCALL    0
    %define READ_LABEL      ft_read
%endif
extern ERRNO_FN

global READ_LABEL
READ_LABEL:       ; rdi = fd, rsi = buf, rdx = count
    mov     rax, READ_SYSCALL   ; system call number for sys_read
    syscall
    cmp     rax, 0
    jl      error_code          ; jump if negative value in rax
    ret

error_code:
    neg     rax         ; get absolute value of syscall return
    mov     rbx, rax    ; back-up rax before calling ernno
    ; call    ERRNO_FN wrt ..plt
    call    ERRNO_FN
    mov     [rax], rbx  ; set the value of errno
    mov     rax, -1
    ret
