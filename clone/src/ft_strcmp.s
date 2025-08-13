; File: ft_strcmp.s
; File Created: 05/02/2025 23:12
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Copyright 2025 NH

%include "os_support.s"
global OS_FN_PREFIX(ft_strcmp)

OS_FN_PREFIX(ft_strcmp):            ; rdi = s1, rsi = s2
    xor     rcx, rcx                ; reset the counter
runloop:
    mov     al, byte [rdi + rcx]
    cmp     al, byte [rsi + rcx]
    jne     retdiff                 ; not equal so break
    cmp     al, 0
    je      retdiff
    inc     rcx
    jmp     runloop

retdiff:
    sub     al, byte [rsi + rcx]    ; sub the char ascii value in s1 & s2
    movsx   rax, al                 ; mov but keep the sign - or +
    ret
