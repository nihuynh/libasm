; File: ft_write.s
; File Created: 05/02/2025 23:12
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Copyright 2025 NH

%ifidn __OUTPUT_FORMAT__, macho64
    %define OS_FN_PREFIX(fn_call) _%+ fn_call
    %define ERRNO_FN        ___error
    %define WRITE_SYSCALL   0x2000004
%elifidn __OUTPUT_FORMAT__, elf64
    %define OS_FN_PREFIX(fn_call) fn_call
    %define ERRNO_FN        __errno_location
    %define WRITE_SYSCALL   1
%endif

extern ERRNO_FN

global OS_FN_PREFIX(ft_write)
OS_FN_PREFIX(ft_write):         ; rdi = fd, rsi = buf, rdx = count
    mov     rax, WRITE_SYSCALL  ; system call number for sys_write
    syscall
    cmp     rax, 0
    jl      error_code          ; jump if negative value in rax
    ret

error_code:
    neg     rax         ; get absolute value of syscall return
    mov     r8, rax    ; back-up rax before calling ernno
    call    ERRNO_FN wrt ..plt
    ; call    ERRNO_FN
    mov     [rax], r8  ; set the value of errno
    mov     rax, -1
    ret
