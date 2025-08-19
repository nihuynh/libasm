; File: ft_write.s
; File Created: 05/02/2025 23:12
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Copyright 2025 NH

%include "os_support.s"
extern ERRNO_FN
global OS_FN_PREFIX(ft_write)

OS_FN_PREFIX(ft_write):         ; rdi = fd, rsi = buf, rdx = count
    cmp     rsi, 0
    je      end
    mov     rax, WRITE_SYSCALL  ; Prepare for write syscall
    syscall
    cmp     rax, 0
    jl      error_code          ; Jump if negative value in rax
    ret

error_code:
    neg     rax                 ; Get absolute value of syscall return
    mov     r8, rax             ; Back-up rax before calling ernno
    ; call    ERRNO_FN wrt ..plt
    call    ERRNO_FN
    mov     [rax], r8           ; Set the value of errno
end:
    mov     rax, -1
    ret
