; File: ft_read.s
; File Created: 05/02/2025 23:12
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Copyright 2025 NH

%include "os_support.s"
extern ERRNO_FN

global OS_FN_PREFIX(ft_read)
OS_FN_PREFIX(ft_read):          ; rdi = fd, rsi = buf, rdx = count
    mov     rax, READ_SYSCALL   ; system call number for sys_read
    syscall
    cmp     rax, 0
    jl      error_code          ; jump if negative value in rax
    ret

error_code:
    neg     rax         ; get absolute value of syscall return
    mov     r8, rax    ; back-up rax before calling ernno
    ; call    ERRNO_FN wrt ..plt
    call    ERRNO_FN
    mov     [rax], r8  ; set the value of errno
    mov     rax, -1
    ret
