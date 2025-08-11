; File: ft_strcpy.s
; File Created: 05/02/2025 23:12
; Author: Nicolas Huynh at (nico.huynh@gmail.com)
; -----
; Copyright 2025 NH

%ifidn __OUTPUT_FORMAT__, macho64
    %define OS_FN_PREFIX(fn_call) _%+ fn_call
%elifidn __OUTPUT_FORMAT__, elf64
    %define OS_FN_PREFIX(fn_call) fn_call
%endif

global OS_FN_PREFIX(ft_strcpy)
OS_FN_PREFIX(ft_strcpy):      ; rdi = dst, rsi = src
    xor     rcx, rcx    ; reset the counter

runloop:
    mov     al, byte [rsi + rcx]    ; store byte of src
    mov     byte [rdi + rcx], al    ; write the byte to dest
    cmp     al, 0                   ; check if the last char was a null-char
    je      end
    inc     rcx
    jmp     runloop

end:
    mov     rax, rdi
    ret
