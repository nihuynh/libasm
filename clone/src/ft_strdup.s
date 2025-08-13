; File: ft_strdup.s
; File Created: 05/02/2025 23:12
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Copyright 2025 NH

%include "os_support.s"
extern OS_FN_PREFIX(malloc)
extern OS_FN_PREFIX(ft_strlen)
extern OS_FN_PREFIX(ft_strcpy)
global OS_FN_PREFIX(ft_strdup)

OS_FN_PREFIX(ft_strdup):    ; rdi = *str duplicate
    call    OS_FN_PREFIX(ft_strlen)
    push    rdi
    inc     rax             ; Add 1 for the '/0'
    mov     rdi, rax
    ; call    OS_FN_PREFIX(malloc) wrt ..plt
    call    OS_FN_PREFIX(malloc)
    pop     rsi             ; Restore the stack and load *str in rsi
    cmp     rax, 0          ; Check if malloc has failed
    je      end
    mov     rdi, rax
    call    OS_FN_PREFIX(ft_strcpy)
end:
    ret
