; File: ft_strlen.s
; File Created: 05/02/2025 23:12
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Copyright 2025 NH

%include "os_support.s"
global OS_FN_PREFIX(ft_strlen)

OS_FN_PREFIX(ft_strlen):    ; rdi = *str to check
    mov     rax, rdi
runloop:
    cmp     byte [rax], 0
    je      end
    inc     rax
    jmp     runloop

end:
    sub rax, rdi
    ret
