; File: ft_strdup.s
; File Created: 05/02/2025 23:12
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Copyright 2025 NH

%ifidn __OUTPUT_FORMAT__, macho64
    %define OS_FN_PREFIX(fn_call) _%+ fn_call
%elifidn __OUTPUT_FORMAT__, elf64
    %define OS_FN_PREFIX(fn_call) fn_call
%endif

extern OS_FN_PREFIX(malloc)
extern OS_FN_PREFIX(ft_strlen)
extern OS_FN_PREFIX(ft_strcpy)

global OS_FN_PREFIX(ft_strdup)
OS_FN_PREFIX(ft_strdup):       ; rdi = *str duplicate
    call    OS_FN_PREFIX(ft_strlen)
    push    rdi
    inc     rax
    mov     rdi, rax
    call    OS_FN_PREFIX(malloc) wrt ..plt
    ; call    OS_FN_PREFIX(malloc)
    pop     rsi         ; restore the stack and the *str to rsi
    cmp     rax, 0      ; check if malloc has failed
    je      error_code
    mov     rdi, rax
    call    OS_FN_PREFIX(ft_strcpy)

error_code:
    ret
